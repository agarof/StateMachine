#pragma once

#include <array>
#include <charconv>
#include <iostream>
#include <iterator>
#include <optional>

#include "Transitions.hpp"

namespace Test {
class Third {
 public:
  Third(float value) {
    std::cout << "Third Init\n";
    auto [end, _] = std::to_chars(std::begin(this->data), std::end(this->data), value);
    *end = '\0';
  }
  ~Third() { std::cout << "Third Teardown\n"; }

  auto update() -> std::optional<Transition> {
    std::cout << "Third: " << this->data.data() << '\n';
    return ToFirst{static_cast<int>(atof(this->data.data()))};
  }

 private:
  std::array<char, 32> data;
};
}  // namespace Test
