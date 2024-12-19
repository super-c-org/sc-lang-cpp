
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

auto main(int argc, char* argv[]) -> int
{
    llvm::InitLLVM init_llvm(argc, argv);
    llvm::errs().tie(&llvm::outs());
    llvm::outs() << "Hello, this is super-C compiler\n";

    namespace cl = llvm::cl;
    cl::ParseCommandLineOptions(argc, argv);
    cl::opt<std::string> input_file_name(cl::Positional, cl::desc("<input file>"), cl::Required);

    return 0;
}
