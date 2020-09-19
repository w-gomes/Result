#pragma once
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>

#include "error.hpp"

namespace result {

template <typename O, typename E = Error>
struct Result {
  std::variant<O, E> value_{};

  Result()  = delete;
  ~Result() = default;

  explicit Result(const O &value) : value_(value) {}
  explicit Result(const E &err) : value_(err) {}

  bool is_ok() const {
    return (std::holds_alternative<O>(value_)) ? true : false;
  }

  bool is_err() const {
    return (std::holds_alternative<E>(value_)) ? true : false;
  }

  O unwrap() const {
    if (std::holds_alternative<E>(value_)) {
      throw std::runtime_error("Error! Cannot unwrap an Error type.");
    } else {
      return std::get<O>(value_);
    }
  }

  E err() const {
    if (!std::holds_alternative<E>(value_)) {
      throw std::runtime_error("Error! Result doesn't hold an Error type.");
    } else {
      return std::get<E>(value_);
    }
  }
};
}  // namespace result
