#pragma once

#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

namespace scl {

struct Diagnostic {

};

// TODO: change this to concurrent
struct DiagEngine {
    explicit DiagEngine(llvm::raw_pwrite_stream& error_stream) : error_stream_(error_stream) {}

    void ReportError(llvm::SMDiagnostic diag) {
        diagnostics_.emplace_back(diag);
        total_errors_++;
        if (total_errors_ > 10) {
            error_stream_ << "Too many errors ... \n";
            PrintDiagnostics();
            exit(total_errors_);
        }
    }

    void PrintDiagnostics() const {
        for (auto& diag : diagnostics_) {
            diag.print(nullptr, error_stream_);
        }
    }

 private:
    llvm::raw_pwrite_stream& error_stream_;
    size_t total_errors_{0};
    llvm::SmallVector<llvm::SMDiagnostic, 10> diagnostics_;
};

}  // namespace scl