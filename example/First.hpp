#pragma once

#include <iostream>
#include <optional>

#include "Transitions.hpp"

namespace Test {
class First {
 public:
  First(int data = 500) : data{data} { std::cout << "First Init\n"; }
  First(First const&) = delete;
  First(First&&) = delete;
  ~First() { std::cout << "First Teardown\n"; }

  auto update() -> std::optional<Transition> {
    std::cout << "First: " << this->data << '\n';
    return ToSecond{static_cast<float>(this->data) * 3 / 2};
  }

 private:
  int data;
};
}  // namespace Test
