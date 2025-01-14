#pragma once
#include "llvm/Support/SourceMgr.h"

namespace scl::diag {
using DiagKind = llvm::SourceMgr::DiagKind;
struct DiagMsg {
    DiagKind kind{DiagKind::DK_Error};
    llvm::StringLiteral message;
};

constexpr auto InvalidSyntax = DiagMsg{DiagKind::DK_Error, "Invalid Syntax"};


}  // namespace scl::diag