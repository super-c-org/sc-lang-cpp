#pragma once
#include "llvm/Support/VirtualFileSystem.h"

namespace scl {

using DriverResult = bool;
auto RunDriver(int argc, char* argv[], llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> fs,
               llvm::raw_pwrite_stream& output_stream, llvm::raw_pwrite_stream& error_stream)
    -> DriverResult;
}  // namespace scl