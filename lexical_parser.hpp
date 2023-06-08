#pragma once

#include <optional>

#include "state.hpp"
#include "token.hpp"
#include "transition_table.hpp"

class LexicalParser {
 private:
  unsigned int state = 0;
  bool go_back = false;
  std::string stack{};

  /**
   * @brief Retrieves the reserved symbol for a given value, if it exists.
   *
   * @param value The value to check for a reserved symbol.
   * @param type The original type associated with the value.
   * @return The reserved symbol if found, otherwise the original type.
   */
  auto get_reserved_symbol(const std::string &value, const std::string &type)
      -> std::string {
    std::map<std::string, std::string> symbol_table = {
        {"program", "simb_program"}, {"var", "simb_var"},
        {"begin", "simb_begin"},     {"procedure", "simb_proc"},
        {"end", "simb_end"},         {"write", "simb_write"},
        {"read", "simb_read"},       {"while", "simb_while"},
        {"do", "simb_do"},           {"to", "simb_to"},
        {"integer", "simb_type"},    {"real", "simb_real"},
        {"for", "simb_for"},         {"if", "simb_if"},
        {"then", "simb_then"},       {"else", "simb_else"},
    };

    if (symbol_table.find(value) == symbol_table.end())
      return type;
    else
      return symbol_table[value];
  }

 public:
  /**
   * @brief Checks if the parser should go back to a previous state.
   *
   * @return True if the parser should go back, false otherwise.
   */
  auto should_go_back() { return go_back; }

  /**
   * @brief Processes the next character and returns the generated token if available.
   *
   * @param c The next character to process.
   * @return An optional Token object if a token is generated, otherwise an empty optional.
   */
  auto next(const char &c) -> std::optional<Token> {
    auto to_stack = states[state].add_to_stack(c);

    state = states[state][c];
    go_back = states[state].should_go_back();

    if (to_stack) stack += c;

    if (states[state].is_final_state()) {
      std::string value = stack;
      std::string type = states[state].get_output();

      if (value.empty()) value = c;

      stack = "";
      state = 0;

      type = get_reserved_symbol(value, type);

      return Token{value, type};
    }

    return {};
  }
};
