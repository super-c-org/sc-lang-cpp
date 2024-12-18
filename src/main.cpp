
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

namespace scl {


} //namespace scl

auto main(int argc, char* argv[]) -> int
{
    llvm::InitLLVM init_llvm(argc, argv);
    llvm::outs() << "Hello, this is super-C compiler\n"; 
    return 0;
}
