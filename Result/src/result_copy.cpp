#include <iostream>
#include <string>
#include <utility>
#include <variant>
#include <exception>

struct Error {
  Error() = delete;
  explicit Error(std::string msg) : message(std::move(msg)) {}
  std::string operator()() {
    return this->message;   
  }
  ~Error() = default;
  std::string message{};
};

template <typename T, typename B>
struct Result {
  using Ok = T;
  using Err = B;

  Result() = delete;
  Result(T t) : value(t) {}
  Result(B b) : value(b) {}

  ~Result() = default;

  bool is_ok() const { 
    if (std::holds_alternative<Ok>(value)) {
      return true;
    } else if (std::holds_alternative<Err>(value)) {
      return false;
    }
  }
  
  bool is_err() const {
    if (std::holds_alternative<Ok>(value)) {
      return false;
    } else if (std::holds_alternative<Err>(value)) {
      return true;
    }
  }

  Ok unwrap() const {
    if (std::holds_alternative<Err>(value)) {
      throw std::runtime_error("Error.");
    } else {
      return std::get<Ok>(value);
    }
  }

  // Doesn't test if value holds Err.
  Err err() const {
    return std::get<Err>(value);
  }

  std::variant<Ok, Err> value{};
};

Result<int, Error> print(bool ok) {
  if (ok) {
    return Result<int, Error>(10);
  } else {
    return Result<int, Error>(Error("There was an error"));
  }
}

int main() {
  std::cout << std::boolalpha << print(false).is_ok() << '\n';
  std::cout << std::boolalpha << print(true).is_ok() << '\n';

  auto r1 = print(true);
  auto value1 = r1.unwrap();
  std::cout << "Result r1 holds Ok with value" << value1 << '\n';

  auto r2 = print(false);
  // auto value2 = r2.unwrap(); unwrappíng on a Result with error throws.
  auto err = r2.is_err();
  if (err) {
    std::cout << "Result r2 holds Err with message" << r2.err()()<< '\n';
  }
}
