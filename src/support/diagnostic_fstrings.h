#pragma once

namespace scl::diag {
// diagnostic format strings conformed to https://llvm.org/doxygen/FormatVariadic_8h_source.html

constexpr auto InvalidSyntax = "Invalid Syntax";
constexpr auto UnexpectedToken = "Expected \'{0}\', found \'{1}\'.";

}  // namespace scl::diag