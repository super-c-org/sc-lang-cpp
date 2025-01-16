#include "driver/driver.h"
#include "llvm/Support/InitLLVM.h"

auto main(int argc, char* argv[]) -> int {
    llvm::InitLLVM init_llvm(argc, argv);

    auto fs = llvm::vfs::getRealFileSystem();

    auto result = scl::RunDriver(argc, argv, fs, llvm::outs(), llvm::errs());
    if (result) {
        return 0;
    } else {
        llvm::errs() << "compilation error" << '\n';
        return 1;
    }
}
