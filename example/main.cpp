#include <array>

#include "../StateMachine.hpp"

#include "First.hpp"
#include "Second.hpp"
#include "Third.hpp"
#include "Transitioner.hpp"
#include "Transitions.hpp"

auto constexpr ITERATIONS = 15;

auto main() -> int {
  auto fsm = StateMachine{Test::Transitioner{}};

  for (auto i = 0; i < ITERATIONS; ++i) {
    fsm.update();
  }

  return 0;
}
