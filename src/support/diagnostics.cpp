
#include "diagnostics.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/ArrayRef.h"

namespace scl {

static const size_t TabStop = 8;

/// diagnostic implementation
Diagnostic::Diagnostic(llvm::SMLoc L, llvm::StringRef FN, int Line, int Col, DiagKind Kind, llvm::StringRef Msg,
           llvm::StringRef LineStr, llvm::ArrayRef<std::pair<unsigned, unsigned>> ranges,
           llvm::ArrayRef<DiagFixIt> fixIts)
    : Loc(L),
      Filename(std::string(FN)),
      LineNo(Line),
      ColumnNo(Col),
      Kind(Kind),
      Message(Msg),
      LineContents(LineStr),
      Ranges(ranges.vec()),
      FixIts(fixIts) {
    llvm::sort(FixIts);
}
static void buildFixItLine(std::string& CaretLine, std::string& FixItLine, llvm::ArrayRef<DiagFixIt> FixIts,
                           llvm::ArrayRef<char> SourceLine) {
    if (FixIts.empty()) {
        return;
    }

    const char* LineStart = SourceLine.begin();
    const char* LineEnd = SourceLine.end();

    size_t PrevHintEndCol = 0;

    for (const DiagFixIt& Fixit : FixIts) {
        // If the fixit contains a newline or tab, ignore it.
        if (Fixit.getText().find_first_of("\n\r\t") != llvm::StringRef::npos) {
            continue;
        }

        llvm::SMRange R = Fixit.getRange();

        // If the line doesn't contain any part of the range, then ignore it.
        if (R.Start.getPointer() > LineEnd || R.End.getPointer() < LineStart) {
            continue;
        }

        // Translate from SMLoc to column.
        // Ignore pieces of the range that go onto other lines.
        // FIXME: Handle multibyte characters in the source line.
        unsigned FirstCol;
        if (R.Start.getPointer() < LineStart) {
            FirstCol = 0;
        } else {
            FirstCol = R.Start.getPointer() - LineStart;
        }

        // If we inserted a long previous hint, push this one forwards, and add
        // an extra space to show that this is not part of the previous
        // completion. This is sort of the best we can do when two hints appear
        // to overlap.
        //
        // Note that if this hint is located immediately after the previous
        // hint, no space will be added, since the location is more important.
        unsigned HintCol = FirstCol;
        if (HintCol < PrevHintEndCol) {
            HintCol = PrevHintEndCol + 1;
        }

        // FIXME: This assertion is intended to catch unintended use of multibyte
        // characters in fixits. If we decide to do this, we'll have to track
        // separate byte widths for the source and fixit lines.
        // assert((size_t)llvm::sys::locale::columnWidth(Fixit.getText()) == Fixit.getText().size());

        // This relies on one byte per column in our fixit hints.
        unsigned LastColumnModified = HintCol + Fixit.getText().size();
        if (LastColumnModified > FixItLine.size()) {
            FixItLine.resize(LastColumnModified, ' ');
        }

        llvm::copy(Fixit.getText(), FixItLine.begin() + HintCol);

        PrevHintEndCol = LastColumnModified;

        // For replacements, mark the removal range with '~'.
        // FIXME: Handle multibyte characters in the source line.
        unsigned LastCol;
        if (R.End.getPointer() >= LineEnd) {
            LastCol = LineEnd - LineStart;
        } else {
            LastCol = R.End.getPointer() - LineStart;
        }

        std::fill(&CaretLine[FirstCol], &CaretLine[LastCol], '~');
    }
}

static void printSourceLine(llvm::raw_ostream& S, llvm::StringRef LineContents) {
    // Print out the source line one character at a time, so we can expand tabs.
    for (unsigned i = 0, e = LineContents.size(), OutCol = 0; i != e; ++i) {
        size_t NextTab = LineContents.find('\t', i);
        // If there were no tabs left, print the rest, we are done.
        if (NextTab == llvm::StringRef::npos) {
            S << LineContents.drop_front(i);
            break;
        }

        // Otherwise, print from i to NextTab.
        S << LineContents.slice(i, NextTab);
        OutCol += NextTab - i;
        i = NextTab;

        // If we have a tab, emit at least one space, then round up to 8 columns.
        do {
            S << " ";
            ++OutCol;
        } while ((OutCol % TabStop) != 0);
    }
    S << "\n";
}

static bool isNonASCII(char c) { return c & 0x80; }
}  // namespace scl