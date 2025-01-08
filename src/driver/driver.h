#pragma once
#include "llvm/Support/VirtualFileSystem.h"

namespace scl {

struct CompileOptions {
    std::string output_filename;
    llvm::SmallVector<std::string, 1> input_filenames;
};

using DriverResult = bool;
auto RunDriver(int argc, char* argv[],
               llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> fs,
               llvm::raw_pwrite_stream& output_stream,
               llvm::raw_pwrite_stream& error_stream) -> DriverResult;
}  // namespace scl