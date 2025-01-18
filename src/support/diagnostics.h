#pragma once

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/Twine.h"
#include "llvm/Support/SMLoc.h"

namespace scl {

enum class DiagKind : int8_t {
    DK_Error,
    DK_Warning,
    DK_Note,
};

struct DiagFixIt {
    DiagFixIt(llvm::SMRange range, const llvm::Twine& replacement)
        : range_(range), text_(replacement.str()) {
        assert(range.isValid());
    }

    DiagFixIt(llvm::SMLoc loc, const llvm::Twine& replacement)
        : DiagFixIt(llvm::SMRange(loc, loc), replacement) {}

    llvm::StringRef getText() const { return text_; }
    llvm::SMRange getRange() const { return range_; }

    bool operator<(const DiagFixIt& other) const {
        if (range_.Start.getPointer() != other.range_.Start.getPointer()) {
            return range_.Start.getPointer() < other.range_.Start.getPointer();
        }
        if (range_.End.getPointer() != other.range_.End.getPointer()) {
            return range_.End.getPointer() < other.range_.End.getPointer();
        }
        return text_ < other.text_;
    }

 private:
    std::string text_;
    llvm::SMRange range_;
};

struct Diagnostic {
    Diagnostic() = default;
    // Diagnostic with no location (e.g. file not found, command line arg error).
    Diagnostic(llvm::StringRef filename, DiagKind Knd, llvm::StringRef Msg)
        : Filename(filename), line_num(-1), column_num(-1), Kind(Knd), Message(Msg) {}

    // Diagnostic with a location.
    Diagnostic(llvm::SMLoc L, llvm::StringRef FN, int Line, int Col, DiagKind Kind,
               llvm::StringRef Msg, llvm::StringRef LineStr,
               llvm::ArrayRef<std::pair<unsigned, unsigned>> ranges,
               llvm::ArrayRef<DiagFixIt> fixIts);

    llvm::SMLoc getLoc() const { return Loc; }
    llvm::StringRef getFilename() const { return Filename; }
    int getLineNo() const { return line_num; }
    int getColumnNo() const { return column_num; }
    DiagKind getKind() const { return Kind; }
    llvm::StringRef getMessage() const { return Message; }
    llvm::StringRef getLineContents() const { return LineContents; }
    llvm::ArrayRef<std::pair<unsigned, unsigned>> getRanges() const { return Ranges; }

    void addFixIt(const DiagFixIt& Hint) { FixIts.push_back(Hint); }

    llvm::ArrayRef<DiagFixIt> getFixIts() const { return FixIts; }

    void print(const char* ProgName, llvm::raw_ostream& S, bool ShowColors = true,
               bool ShowKindLabel = true, bool ShowLocation = true) const;

 private:
    llvm::SMLoc Loc;
    std::string Filename;
    int32_t line_num{-1};
    int32_t column_num{-1};
    DiagKind Kind{DiagKind::DK_Error};
    std::string Message;
    std::string LineContents;
    std::vector<std::pair<unsigned, unsigned>> Ranges;
    llvm::SmallVector<DiagFixIt, 4> FixIts;
};

struct DiagnosticsEngine {
    // template <typename... Args>
    // void ShowError(llvm::SMLoc location, const char* format, Args&&... arguments) {
    //     auto msg = llvm::formatv(format, std::forward<Args>(arguments)...).str();
    //     messages_.emplace_back(Message{location, DiagKind::DK_Error, msg});
    //     total_errors_++;
    // }

    // void PrintMessages() const {
    //     for (auto& msg : messages_) {
    //         srcMgr_.PrintMessage(msg.location, msg.kind, msg.description);
    //     }
    // }
 private:
    size_t total_errors_{0};
};

}  // namespace scl