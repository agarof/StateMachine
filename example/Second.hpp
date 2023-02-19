#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <string_view>

#include "Transitions.hpp"

namespace Test {
class Second {
 public:
  Second(float data) : data{data} { std::cout << "Second Init\n"; }
  ~Second() { std::cout << "Second Teardown\n"; }

  auto update() -> std::optional<Transition> {
    std::cout << "Second: " << this->data << '\n';
    return ToThird{this->data};
  }

 private:
  float data;
};
}  // namespace Test
