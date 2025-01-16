#pragma once
#include "driver_settings.h"

namespace scl {

using CompileResult = bool;
auto RunCompileCmd(const CommandLineOptions& options, const DriverEnv& env) -> CompileResult;

}  // namespace scl