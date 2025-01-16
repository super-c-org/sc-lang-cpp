
#include "driver.h"

#include "compile_cmd.h"
#include "diagnostics/diagnostic.h"
#include "driver_settings.h"
#include "llvm/Support/CommandLine.h"

namespace scl {

namespace {

auto ParseArguments(int argc, char* argv[]) -> CommandLineOptions {
    namespace cl = llvm::cl;

    cl::opt<std::string> output_filename("o", cl::desc("Specify output filename"),
                                         cl::value_desc("filename"));
    cl::list<std::string> input_filenames(cl::Positional, cl::desc("<input files>"), cl::OneOrMore);

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

    CommandLineOptions options;

    options.output_filename = output_filename;

    for (auto& input_file : input_filenames) {
        options.input_filenames.emplace_back(input_file);
    }

    return options;
}

}  // namespace

auto RunDriver(int argc, char* argv[], llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> fs,
               llvm::raw_pwrite_stream& output_stream, llvm::raw_pwrite_stream& error_stream)
    -> DriverResult {
    auto options = ParseArguments(argc, argv);

    auto env = SystemEnv{.fs = fs, .output_stream = output_stream, .error_stream = error_stream};

    auto compile_result = RunCompileCmd(options, env);

    return true;
}
}  // namespace scl