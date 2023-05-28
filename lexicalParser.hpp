#pragma once

#include "token.hpp"
#include <map>
#include <optional>
#include <string>

class State {
public:
    State(unsigned int state)
        : state { state }
    {
    }

private:
    unsigned int state = 1;

    std::map<unsigned int, std::map<char, unsigned int>> transition_table = {
        { 1, {
                 { ' ', 1 },
                 { '\n', 1 },
                 { '\t', 1 },
                 { 'A', 20 },
                 { 'B', 20 },
                 { 'C', 20 },
                 { 'D', 20 },
                 { 'E', 20 },
                 { 'F', 20 },
                 { 'G', 20 },
                 { 'H', 20 },
                 { 'I', 20 },
                 { 'J', 20 },
                 { 'K', 20 },
                 { 'L', 20 },
                 { 'M', 20 },
                 { 'N', 20 },
                 { 'O', 20 },
                 { 'P', 20 },
                 { 'Q', 20 },
                 { 'R', 20 },
                 { 'S', 20 },
                 { 'T', 20 },
                 { 'U', 20 },
                 { 'V', 20 },
                 { 'W', 20 },
                 { 'X', 20 },
                 { 'Y', 20 },
                 { 'Z', 20 },
                 { 'a', 20 },
                 { 'b', 20 },
                 { 'c', 20 },
                 { 'd', 20 },
                 { 'e', 20 },
                 { 'f', 20 },
                 { 'g', 20 },
                 { 'h', 20 },
                 { 'i', 20 },
                 { 'j', 20 },
                 { 'k', 20 },
                 { 'l', 20 },
                 { 'm', 20 },
                 { 'n', 20 },
                 { 'o', 20 },
                 { 'p', 20 },
                 { 'q', 20 },
                 { 'r', 20 },
                 { 's', 20 },
                 { 't', 20 },
                 { 'u', 20 },
                 { 'v', 20 },
                 { 'w', 20 },
                 { 'x', 20 },
                 { 'y', 20 },
                 { 'z', 20 },
                 { '{', 8 },
             } },
        { 8, {
                 { '}', 1 },
                 { '\n', 9 },
             } },
        { 20, { { ' ', 21 } } }
    };

public:
    auto get_state() -> unsigned int
    {
        return state;
    }

    auto next_state(const char& c)
    {
        unsigned int new_state;

        new_state = transition_table[state][c];
        state = !new_state ? state : new_state;
    }

    auto is_final_state() -> bool
    {
        return state == 21;
    }
};

std::map<unsigned int, std::map<std::string, std::string>> token_class = {
    {  21 , { { "program", "simb_program" } } },
};

class LexicalParser {
private:
    State state { 1 };
    std::string stack {};

public:
    auto read_char(const char& c) -> std::optional<Token>
    {
        std::cout << "char: " << c << std::endl;
        std::cout << "current state: " << state.get_state() << std::endl;

        state.next_state(c);

        if (state.is_final_state()) {
            Token token = Token(stack, token_class[state.get_state()][stack]);

            stack.clear();
            state = 1;

            return token;
        } else {
            stack += c;
            return {};
        }
    }
};
