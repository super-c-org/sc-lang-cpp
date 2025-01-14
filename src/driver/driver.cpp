
#include "driver.h"

#include <string>

#include "llvm/Support/CommandLine.h"

namespace scl {
struct CompileOptions {
    std::string output_filename;
    llvm::SmallVector<std::string, 1> input_filenames;
};


namespace {

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
    llvm::cl::SetVersionPrinter([](llvm::raw_ostream& OS) {
        OS << "Super C Compiler v2025.1.alpha\n";
    });

    cl::ParseCommandLineOptions(argc, argv, "Super C Compiler");

    CompileOptions options;

    options.output_filename = output_filename;

    for (auto& input_file : input_filenames) {
        options.input_filenames.emplace_back(input_file);
    }

    return options;
}

struct DriverEnv {
    // The filesystem for source code.
    llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> fs;

    // Standard output
    llvm::raw_pwrite_stream& output_stream;
    // Error output
    llvm::raw_pwrite_stream& error_stream;
};

auto CompileFile(llvm::StringRef input_filename, const CompileOptions& options,
                 DriverEnv& driver_env) -> DriverResult {
    
    return false;
}

}  // namespace

auto RunDriver(int argc, char* argv[],
               llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> fs,
               llvm::raw_pwrite_stream& output_stream,
               llvm::raw_pwrite_stream& error_stream) -> DriverResult {
    auto driver_env = DriverEnv{
        .fs = fs, .output_stream = output_stream, .error_stream = error_stream};

    // step 1
    CompileOptions options = ParseArguments(argc, argv);

    // step 2 - create build graph

    // step 3 - compile files per the build graph
    auto result = CompileFile(options.input_filenames[0], options, driver_env);

    return true;
}
}  // namespace scl