
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

auto main(int argc, char* argv[]) -> int {
    llvm::InitLLVM initLLVM(argc, argv);
    llvm::errs().tie(&llvm::outs());
    llvm::outs() << "Hello, this is super-C compiler\n";

    namespace cl = llvm::cl;
    cl::opt<std::string> OutputFilename(
        "o", cl::desc("Specify output filename"), cl::value_desc("filename"));
    cl::opt<std::string> InputFilename(cl::Positional, cl::desc("<input file>"),
                                       cl::Required);

    cl::ParseCommandLineOptions(argc, argv);

    printf("%s \n", InputFilename.c_str());
    printf("%s \n", OutputFilename.c_str());

    return 0;
}
