#pragma once

#include "llvm/Support/MemoryBuffer.h"

namespace scl {

struct SourceBuffer {
    explicit SourceBuffer(std::unique_ptr<llvm::MemoryBuffer> buffer)
        : buffer_(std::move(buffer)) {}

 private:
    std::unique_ptr<llvm::MemoryBuffer> buffer_;
};

}  // namespace scl