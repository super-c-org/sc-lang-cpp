#include "driver/driver.h"
#include "llvm/Support/InitLLVM.h"

auto main(int argc, const char* argv[]) -> int {
    llvm::InitLLVM init_llvm(argc, argv);

    auto fs = llvm::vfs::getRealFileSystem();

    return scl::RunDriver(argc, argv, fs, llvm::outs(), llvm::errs());

}
