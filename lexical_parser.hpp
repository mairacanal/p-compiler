#pragma once

#include <optional>

#include "state.hpp"
#include "token.hpp"
#include "transition_table.hpp"

class LexicalParser {
private:
    unsigned int state;
    std::string stack {};

public:
    auto next(const char& c) -> std::optional<Token>
    {
        std::cout << "char: " << c << std::endl;
        std::cout << "current state: " << state << std::endl;

        state = states[state][c];

        if (states[state].is_final_state()) {
            Token token { states[state].get_output(), stack };

            stack = "";
            state = 0;

            return token;
        }

        stack += c;
        return {};
    }
};
