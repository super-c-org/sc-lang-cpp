#pragma once
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/SourceMgr.h"

namespace scl {

struct Diagnostic {
    explicit Diagnostic(llvm::SourceMgr& srcMgr) : srcMgr_(srcMgr) {}
    struct Message {
        llvm::SMLoc location;
        llvm::SourceMgr::DiagKind kind;
        llvm::Twine description;
    };

    template <typename... Args>
    void ShowError(llvm::SMLoc location, const char* format, Args&&... arguments) {
        auto msg = llvm::formatv(format, std::forward<Args>(arguments)...).str();
        messages_.emplace_back(Message{location, llvm::SourceMgr::DK_Error, msg});
        total_errors_++;
    }

    void PrintMessages() {
        for (auto& msg : messages_) {
            srcMgr_.PrintMessage(msg.location, msg.kind, msg.description);
        }
    }

 private:
    llvm::SourceMgr& srcMgr_;
    llvm::SmallVector<Message, 10> messages_;
    size_t total_errors_{0};
};

}  // namespace scl