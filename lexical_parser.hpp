#pragma once

#include <optional>

#include "state.hpp"
#include "token.hpp"
#include "transition_table.hpp"

class LexicalParser {
private:
    unsigned int state = 0;
    bool go_back = false;
    std::string stack {};

    auto get_reserved_symbol(const std::string& value, const std::string& type) -> std::string {
        std::map<std::string, std::string> symbol_table = {
            {"program", "simb_program"},
            {"var", "simb_var"},
            {"begin", "simb_begin"},
        };

        if (symbol_table.find(value) == symbol_table.end())
            return type;
        else
            return symbol_table[value];
    }

public:
    auto should_go_back() {
        return go_back;
    }

    auto next(const char& c) -> std::optional<Token>
    {
        auto to_stack = states[state].add_to_stack(c);

        std::cout << "current state: " << state << " char: " << c << std::endl;

        state = states[state][c];
        go_back = states[state].should_go_back();

        std::cout << "new state: " << state << std::endl;
        std::cout << std::endl;

        if (states[state].is_final_state()) {
            std::string value = stack;
            std::string type = states[state].get_output();

            if (value.empty())
                value = c;

            stack = "";
            state = 0;

            type = get_reserved_symbol(value, type);

            return Token { value, type };
        }

        if (to_stack)
            stack += c;

        return {};
    }
};
