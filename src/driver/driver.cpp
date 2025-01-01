
#include "llvm/Support/CommandLine.h"

namespace scl {
auto RunCompiler(int argc, char* argv[]) -> int {
    namespace cl = llvm::cl;
    cl::opt<std::string> output_filename(
        "o", cl::desc("Specify output filename"), cl::value_desc("filename"));
    cl::opt<std::string> input_filename(cl::Positional,
                                        cl::desc("<input file>"), cl::Required);

    cl::ParseCommandLineOptions(argc, argv);

    printf("%s \n", input_filename.c_str());
    printf("%s \n", output_filename.c_str());
    return 0;
}
}  // namespace scl