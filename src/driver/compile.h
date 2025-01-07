#pragma once

#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/VirtualFileSystem.h"

namespace scl {
struct CompileOptions {
    std::string output_filename;
    llvm::SmallVector<std::string, 1> input_filenames;
};

auto Compile(const CompileOptions& options, const llvm::vfs::FileSystem& fs) -> bool;



}  // namespace scl
