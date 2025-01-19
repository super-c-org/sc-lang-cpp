#pragma once

namespace scl {



struct DiagnosticsEngine {
    // template <typename... Args>
    // void ShowError(llvm::SMLoc location, const char* format, Args&&... arguments) {
    //     auto msg = llvm::formatv(format, std::forward<Args>(arguments)...).str();
    //     messages_.emplace_back(Message{location, DiagKind::DK_Error, msg});
    //     total_errors_++;
    // }

    // void PrintMessages() const {
    //     for (auto& msg : messages_) {
    //         srcMgr_.PrintMessage(msg.location, msg.kind, msg.description);
    //     }
    // }
 private:
    // size_t total_errors_{0};
};

}  // namespace scl