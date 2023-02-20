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
    requires(T transitioner, typename T::Transition& transition, typename T::State& state) {
      { transitioner(state, transition) };
    };

template <typename Transition, State<Transition>... SubStates>
struct VariantState : public std::variant<SubStates...> {
  auto update() -> std::optional<Transition> {
    return std::visit([](auto& state) { return state.update(); }, *this);
  }
};

template <Transitioner T>
class StateMachine : T {
 public:
  StateMachine(T transitioner) : T{std::move(transitioner)} {}

  void update() {
    auto transition = this->data.update();

    if (transition.has_value()) {
      this->T::operator()(this->data, *transition);
    }
  }

 private:
  typename T::State data;
};
