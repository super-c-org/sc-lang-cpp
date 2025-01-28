#pragma once

#include "llvm/Support/raw_ostream.h"

namespace scl {

enum class DiagLevel: int8_t {
    DK_Error,
    DK_Warning,
};

// An instance of a single error or warning
struct Diagnostic {
    // Name of the file or buffer that this diagnostic refers to.
    std::string filename;

    // 1-based line number. -1 indicates unknown; other values are unused.
    int32_t line_number{-1};

    // 1-based column number. -1 indicates unknown; other values are unused.
    int32_t column_number{-1};

    // The number of columns corresponding to the location in the line,
    // starting at column_number. Should always be at least 1.
    int32_t length{1};

    DiagLevel level{DiagLevel::DK_Error};

    // Diagnistic message, tip and note
    std::string message;

    std::string tip;

    std::string note;

    // The related source code line
    std::string line;
};

// TODO: change this to concurrent
struct DiagEngine {
    explicit DiagEngine(llvm::raw_pwrite_stream& error_stream) : error_stream_(error_stream) {}

    void ReportError(Diagnostic diag) {
        diagnostics_.emplace_back(diag);
        total_errors_++;
        if (total_errors_ > 10) {
            error_stream_ << "Too many errors ... \n";
            PrintDiagnostics();
            exit(total_errors_);
        }
    }

    void PrintDiagnostic(const Diagnostic& diag) const;
    
    void PrintDiagnostics() const {
        for (auto& diag : diagnostics_) {
            // TODO
        }
    }

 private:
    llvm::raw_pwrite_stream& error_stream_;
    size_t total_errors_{0};
    llvm::SmallVector<Diagnostic, 10> diagnostics_;
};

}  // namespace scl