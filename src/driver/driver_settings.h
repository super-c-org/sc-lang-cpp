#pragma once
#include "llvm/Support/VirtualFileSystem.h"

namespace scl {

struct CommandLineOptions {
    std::string output_filename;
    llvm::SmallVector<std::string, 1> input_filenames;
};

struct DriverEnv {
    // The filesystem for source code.
    llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> fs;

    // Standard output
    llvm::raw_pwrite_stream& output_stream;
    // Error output
    llvm::raw_pwrite_stream& error_stream;
};

}  // namespace scl