#pragma once
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/SourceMgr.h"

namespace scl {

struct Diagnostic {
    explicit Diagnostic(llvm::SourceMgr& srcMgr) : srcMgr_(srcMgr) {}

 private:
    llvm::SourceMgr& srcMgr_;
};

}  // namespace scl