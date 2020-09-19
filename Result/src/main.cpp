#include <iostream>
#include <type_traits>

#include "result.hpp"

template <typename... T>
auto mean(T... args) {
  std::size_t len = sizeof...(args);

  using Type = std::common_type_t<T...>;
  Type r     = ((args + ...) / len);
  if (r < 30) {
    return result::Result<Type>(result::Error("Mean is too low."));
  }
  return result::Result<Type>(r);
}

int main() {
  auto r = mean(3, 7, 5, 13, 20, 23, 39, 23, 40, 23, 14, 12, 56, 23, 29);
  if (r.is_ok()) {
    std::cout << r.unwrap() << '\n';
  } else {
    std::cout << r.err()() << '\n';
  }

  auto r2 = mean(3, 7, 5, 13, 20, 23, 39, 23, 40, 23, 14);
  if (r2.is_ok()) {
    std::cout << r2.unwrap() << '\n';
  } else {
    std::cout << r2.err()() << '\n';
  }

  auto r3 = mean(3.f, -7.f, 5.f, 13.f, -2.f);
  std::cout << r3.err()() << '\n';

  auto r4 = mean(65, 56, 69, 44);
  std::cout << r4.unwrap() << '\n';

  return 0;
}
