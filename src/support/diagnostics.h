#pragma once

#include "llvm/Support/raw_ostream.h"

namespace scl {

enum class DiagLevel : int8_t {
    DK_Error,
    DK_Warning,
};

// An instance of a single error or warning
struct Diagnostic {
    // Name of the file or buffer that this diagnostic refers to.
    std::string filename;

    // 1-based line number. 0 indicates unknown
    uint16_t line_number{0};

    // 1-based column number. 0 indicates unknown
    uint16_t column_number{0};

    // The underlined ranges for the code snippet
    llvm::SmallVector<std::pair<uint16_t, uint16_t>> ranges;

    DiagLevel level{DiagLevel::DK_Error};

    // Diagnistic message, tip and note
    std::string message;

    std::string tip;

    std::string note;

    // The related source code line
    std::string sourceline;
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

    void PrintDiagnostics() const {
        for (auto& diag : diagnostics_) {
            // TODO
        }
    }

    void PrintDiagnostic(const Diagnostic& diag) const;

 private:
    llvm::raw_pwrite_stream& error_stream_;
    size_t total_errors_{0};
    llvm::SmallVector<Diagnostic, 10> diagnostics_;
};

}  // namespace scl