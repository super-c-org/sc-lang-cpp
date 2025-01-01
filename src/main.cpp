
#include "driver/driver.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

auto main(int argc, char* argv[]) -> int {
    llvm::InitLLVM init_llvm(argc, argv);

    llvm::errs().tie(&llvm::outs());
    llvm::outs() << "Hello, this is super-C compiler\n";

    return scl::RunCompiler(argc, argv);
}
