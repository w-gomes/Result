#pragma once

namespace result {
struct Error {
  Error() = delete;
  explicit Error(std::string msg) : message(std::move(msg)) {}
  std::string operator()() { return this->message; }
  ~Error() = default;
  std::string message{};
};
}  // namespace result
