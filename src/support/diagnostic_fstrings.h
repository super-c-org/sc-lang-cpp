#pragma once

namespace scl::diag {
/// diagnostic format strings conformed to https://llvm.org/doxygen/FormatVariadic_8h_source.html

constexpr auto E_InvalidSyntax = "error: Invalid Syntax";
constexpr auto E_UnexpectedToken = "error: Expected \'{0}\', found \'{1}\'.";

}  // namespace scl::diag