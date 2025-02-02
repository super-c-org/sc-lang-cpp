#include "diagnostics.h"

#include "llvm/Support/WithColor.h"

namespace scl {

// diagnostic output format
// /usr/project1/file.sc:LL:CC
// error: main error message
//    |
// LL | <code>
//    | ^^^^^^
//    |
//    = tip (optional)
//    = note (optional)

void DiagEngine::PrintDiagnostic(const Diagnostic& diag) const {
    if (diag.filename.empty()) {
        return;
    }

    // emit filename:LL::CC
    {
        llvm::WithColor es(error_stream_, llvm::raw_ostream::SAVEDCOLOR, true);

        es << diag.filename << ": ";

        if (diag.line_number > 0) {
            es << ':' << diag.line_number;
            if (diag.column_number > 0) {
                es << ':' << diag.column_number;
            }
        }
        es << '\n';
    }

    // emit level
    switch (diag.level) {
        case DiagLevel::DK_Error:
            llvm::WithColor::error(error_stream_, "");
            break;
        case DiagLevel::DK_Warning:
            llvm::WithColor::warning(error_stream_, "");
            break;
    }

    // emit message
    llvm::WithColor(error_stream_, llvm::raw_ostream::SAVEDCOLOR, true) << diag.message << '\n';

    if (diag.line_number == 0 || diag.column_number == 0) {
        return;
    }

    // emit code snippet
    // line number format:
    // " [number] | "
    // where [number] is 5 columns because max line of codes is 65,535, e.g. max of uint16_t
    // therefore, the total width is 5+4=9
    constexpr auto line_num_display_width = 5u;

    // emit caret line
    // treat tab stop as 1 to simplify
    
    
    // emit tip

    // emit note
}

}  // namespace scl