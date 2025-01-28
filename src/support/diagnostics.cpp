#include "diagnostics.h"

#include "llvm/Support/WithColor.h"

namespace scl {

void DiagEngine::PrintDiagnostic(const Diagnostic& diag) const {
    if (diag.filename.empty()) {
        return;
    }

    // emit filename:LL::CC
    {
        llvm::WithColor es(error_stream_, llvm::raw_ostream::SAVEDCOLOR, true);

        es << diag.filename << ": ";

        if (diag.line_number != -1) {
            es << ':' << diag.line_number;
            if (diag.column_number != -1) {
                es << ':' << diag.column_number;
            }
        }
        es << '\n';
    }


}

}  // namespace scl