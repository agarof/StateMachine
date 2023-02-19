#pragma once

#include <string>
#include <variant>

namespace Test {
struct ToFirst {
  int data;
};

struct ToSecond {
  float data;
};

struct ToThird {
  float data;
};

using Transition = std::variant<ToFirst, ToSecond, ToThird>;
}  // namespace Test
