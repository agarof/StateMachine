#pragma once

#include <concepts>
#include <memory>
#include <optional>
#include <tuple>
#include <type_traits>
#include <variant>

template <typename T, typename Transition>
concept State = requires(T state) {
                  { state.update() } -> std::convertible_to<std::optional<Transition>>;
                };

template <typename T>
concept Transitioner =
    requires(T transitioner, typename T::Transition& transition, typename T::States& states) {
      { transitioner(states, transition) };
    };

template <Transitioner T>
class StateMachine : T {
 public:
  StateMachine(T transitioner) : T{std::move(transitioner)} {}

  void update() {
    auto transition = std::visit([](auto& state) { return state.update(); }, this->data);

    if (transition.has_value()) {
      this->T::operator()(this->data, *transition);
    }
  }

 private:
  typename T::States data;
};
