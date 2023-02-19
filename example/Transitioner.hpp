#pragma once

#include <variant>

#include "First.hpp"
#include "OverloadedVisitor.hpp"
#include "Second.hpp"
#include "Third.hpp"
#include "Transitions.hpp"

namespace Test {
struct Transitioner {
  using Transition = std::variant<ToFirst, ToSecond, ToThird>;
  using States = std::variant<First, Second, Third>;

  void operator()(States& state, Transition& trans) {
    std::visit(overloaded{[&](ToFirst& t) { state.emplace<First>(std::move(t.data)); },
                          [&](ToSecond& t) { state.emplace<Second>(std::move(t.data)); },
                          [&](ToThird& t) { state.emplace<Third>(std::move(t.data)); }},
               trans);
  }
};
}  // namespace Test
