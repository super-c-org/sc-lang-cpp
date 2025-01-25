#include "compile_cmd.h"

#include "llvm/Support/FormatVariadic.h"
#include "support/diagnostics.h"

namespace scl {

struct CompilationUnit {};

auto RunCompileCmd(const CommandLineOptions& options, const SystemEnv& env) -> CompileResult {
    DiagEngine diag_engine{env.error_stream};

    // TODO: step 1 - create build graph

    // step 2 - compile source code per the build graph
    auto file = env.fs->openFileForRead(options.input_filenames[0]);
    if (file.getError()) {
        env.error_stream << llvm::formatv("error opening file {0} for read",
                                          options.input_filenames[0])
                         << '\n';
        return false;
    }

    auto file_status = (*file)->status();
    if (file_status.getError()) {
        env.error_stream << llvm::formatv("error statting file: {0}", options.input_filenames[0])
                         << '\n';
        return false;
    }

    auto is_regular_file = file_status->isRegularFile();
    auto file_size = is_regular_file ? file_status->getSize() : -1;

    auto source_buffer = (*file)->getBuffer(options.input_filenames[0], file_size, is_regular_file);

    if (source_buffer.getError()) {
        env.error_stream << llvm::formatv("error creating source buffer for file: {0}",
                                          options.input_filenames[0])
                         << '\n';
        return false;
    }

    llvm::SourceMgr source_mgr;
    source_mgr.AddNewSourceBuffer(std::move(*source_buffer), llvm::SMLoc());

    source_mgr.PrintMessage(env.error_stream,llvm::SMLoc(),llvm::SourceMgr::DK_Error,"error message test \n");

    return true;
}

}  // namespace scl