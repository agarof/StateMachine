# StateMachine

A basic state machine implementation which tries to minimize its memory footprint.

## Parts

### Transition

A type used by the state machine to transition to the next state.

### State

A state is an object described by the `State` concept: it has an `update()`
method which returns an optional transition.

The header includes `VariantState`, a `std::variant` of states, calling the
currently contained state's `update()` when its own is called.

### Transitioner

The transitioner is responsible for mutating the state in response to
transitions. It must have:
- A `State` type which implements the `State` concept.
- A `Transition` type, the type returned by the states and to which it will
  react.
- An `operator()(States&, Transition&)` to mutate the state machine in place.

### The state machine

`StateMachine` is a templated class over a Transitioner, from which it inherits
to allow empty base class optimisation. Its update method will call the current
state's and call the transitioner's `operator()` if a type was returned.

## Memory footprint

When using `VariantState`, because only one state is stored in the state
machine at a time, its size is that of the largest state + the variant
discriminant. The stack space required to update the space machine is the size
of its `Transition` type + the current state's `update()` method stack usage.
