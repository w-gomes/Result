#include "../Result/src/result.hpp"

#include "catch.hpp"

template <typename T>
auto mul(T x) {
  if (x <= 1)
    return result::Result<T>(result::Error("value is less than 1"));
  else
    return result::Result<T>(x * x);
}

TEST_CASE("is_ok()", "[is_ok()]") {
  CHECK(mul(10).is_ok());
  CHECK(mul(100).is_ok());
  CHECK_FALSE(mul(0).is_ok());
  CHECK_FALSE(mul(1).is_ok());
  CHECK_FALSE(mul(-1).is_ok());
}

TEST_CASE("is_err()", "[is_err()]") {
  CHECK_FALSE(mul(100).is_err());
  CHECK_FALSE(mul(10).is_err());
  CHECK(mul(0).is_err());
  CHECK(mul(1).is_err());
  CHECK(mul(-1).is_err());
}

TEST_CASE("when unwrap() throws", "[unwrap()]") {
  auto num = mul(0);
  CHECK_THROWS(num.unwrap());
  CHECK_THROWS_AS(num.unwrap(), std::runtime_error);
  CHECK_THROWS_WITH(num.unwrap(), "Error! Cannot unwrap an Error type.");
}

TEST_CASE("unwrap() an Ok type.", "[unwrap()]") {
  auto num = mul(2);
  REQUIRE(num.unwrap() == 4);
  auto num2 = mul(10032);
  REQUIRE(num2.unwrap() == 100641024);
}

TEST_CASE("printing the message in Error by getting it with err()", "[err()]") {
  auto num = mul(1);
  REQUIRE(num.err()() == "value is less than 1");
}

TEST_CASE("Calling err() with no Error type throws", "[err()]") {
  auto num = mul(3);
  CHECK_THROWS(num.err());
  CHECK_THROWS_AS(num.err(), std::runtime_error);
  CHECK_THROWS_WITH(num.err(), "Error! Result doesn't hold an Error type.");
}

