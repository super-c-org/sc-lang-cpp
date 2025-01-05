
#include <string>
#include "llvm/Support/CommandLine.h"

namespace scl {

namespace {
struct CompileOptions {
    std::string output_filename;
    llvm::SmallVector<std::string, 1> input_filenames;
};

auto ParseArguments(int argc, char* argv[]) -> CompileOptions {
    namespace cl = llvm::cl;

    cl::opt<std::string> output_filename(
        "o", cl::desc("Specify output filename"), cl::value_desc("filename"));
    cl::list<std::string> input_filenames(
        cl::Positional, cl::desc("<input files>"), cl::OneOrMore);

    auto& Map = cl::getRegisteredOptions();
    // Change --help description
    assert(Map.count("help") > 0);
    Map["help"]->setDescription(
        R"(For questions, issues, or bug reports, please use our GitHub project:
    https://github.com/super-c-org/sc-lang-cpp)");

    // Set version
    llvm::cl::SetVersionPrinter(
        [](llvm::raw_ostream& OS) { OS << "Super C Compiler v2025.1.alpha\n"; });

    cl::ParseCommandLineOptions(argc, argv, "Super C Compiler");

    CompileOptions options;

    options.output_filename = output_filename;

    for (auto& input_file : input_filenames) {
        options.input_filenames.emplace_back(input_file);
    }

    return options;
}

}  // namespace

static auto Compile() -> void;

auto RunCompiler(int argc, char* argv[]) -> int {
    CompileOptions options = ParseArguments(argc, argv);

    llvm::outs() << "first input file is " << options.input_filenames[0]
                 << "\n";

    llvm::outs() << "Output file is " << options.output_filename << "\n";

    return 0;
}
}  // namespace scl