#pragma once

#include <map>
#include <string>

class Transition {
 private:
  unsigned int state;
  bool to_stack;

 public:
  /**
   * @brief Default constructor for Transition.
   *
   * Initializes the Transition object with default values.
   */
  Transition() : state{0}, to_stack{true} {}

  /**
   * @brief Constructor for Transition.
   *
   * Initializes the Transition object with a specified state.
   *
   * @param state The state to transition to.
   */
  Transition(unsigned int state) : state{state}, to_stack{true} {}

  /**
   * @brief Constructor for Transition.
   *
   * Initializes the Transition object with a specified state and stack
   * behavior.
   *
   * @param state The state to transition to.
   * @param to_stack Determines if the character should be added to the stack.
   */
  Transition(unsigned int state, bool to_stack)
      : state{state}, to_stack{to_stack} {}

  /**
   * @brief Retrieves the state to transition to.
   *
   * @return The state to transition to.
   */
  auto get_state() -> unsigned int { return state; }

  /**
   * @brief Checks if the character should be added to the stack.
   *
   * @return True if the character should be added to the stack, false
   * otherwise.
   */
  auto add_to_stack() -> bool { return to_stack; }
};

class State {
 private:
  bool is_final;
  bool go_back;
  std::string output;
  std::map<char, Transition> transitions;

 public:
  /**
   * @brief Default constructor for State.
   *
   * Initializes the State object with default values.
   */
  State() {
    is_final = false;
    go_back = false;
    output = "";
    transitions = std::map<char, Transition>{};
  }

  /**
   * @brief Constructor for State.
   *
   * Initializes the State object with specified values.
   *
   * @param is_final Indicates if the state is a final state.
   * @param go_back Indicates if the parser should go back to a previous state.
   * @param output The output associated with the state.
   * @param transitions The transitions from the state to other states.
   */
  State(bool is_final, bool go_back, std::string output,
        std::map<char, Transition> transitions)
      : is_final{is_final},
        go_back{go_back},
        output{output},
        transitions{transitions} {}

  /**
   * @brief Constructor for State.
   *
   * Initializes the State object with specified output and transitions.
   *
   * @param output The output associated with the state.
   * @param transitions The transitions from the state to other states.
   */
  State(std::string output, std::map<char, Transition> transitions)
      : is_final{false},
        go_back{false},
        output{output},
        transitions{transitions} {}

  /**
   * @brief Retrieves the output associated with the state.
   *
   * @return The output associated with the state.
   */
  auto get_output() -> std::string { return output; }

  /**
   * @brief Checks if the state is a final state.
   *
   * @return True if the state is a final state, false otherwise.
   */
  auto is_final_state() -> bool { return is_final; }

  /**
   * @brief Checks if the parser should go back to a previous state.
   *
   * @return True if the parser should go back, false otherwise.
   */
  auto should_go_back() -> bool { return go_back; }

  /**
   * @brief Determines if the character should be added to the stack based on
   * the current state.
   *
   * @param c The character to check for a transition.
   * @return True if the character should be added to the stack, false
   * otherwise.
   */
  auto add_to_stack(const char &c) -> bool {
    return transitions.count(c) ? transitions[c].add_to_stack()
                                : transitions['\0'].add_to_stack();
  }

  /**
   * @brief Retrieves the state to transition to based on the current state and
   * input character.
   *
   * @param c The input character to check for a transition.
   * @return The state to transition to.
   */
  auto operator[](const char &c) -> unsigned int {
    return transitions.count(c) ? transitions[c].get_state()
                                : transitions['\0'].get_state();
  }
};
