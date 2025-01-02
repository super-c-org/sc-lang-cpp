
#include <string>
#include "llvm/Support/CommandLine.h"

namespace scl {

struct CompileOptions {
    std::string output_filename;
    llvm::SmallVector<std::string, 1> input_filenames;
};

static auto ParseArguments(int argc, char* argv[]) -> CompileOptions {
    namespace cl = llvm::cl;

    cl::opt<std::string> output_filename(
        "o", cl::desc("Specify output filename"), cl::value_desc("filename"));
    cl::list<std::string> input_filenames(
        cl::Positional, cl::desc("<input files>"), cl::OneOrMore);

    cl::ParseCommandLineOptions(argc, argv);

    CompileOptions options;

    options.output_filename = output_filename;

    for (auto& input_file : input_filenames) {
        options.input_filenames.emplace_back(input_file);
    }

    return options;
}

static auto Compile() -> void;

auto RunCompiler(int argc, char* argv[]) -> int {
    CompileOptions options = ParseArguments(argc, argv);

    llvm::outs() << "first input file is " << options.input_filenames[0]
                 << "\n";
    
    llvm::outs() << "Output file is " << options.output_filename
                 << "\n";
    
    return 0;
}
}  // namespace scl