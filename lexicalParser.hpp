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
        std::map<unsigned int, std::map<char, unsigned int>> tabela = {
        {0, {{'+', 26}, {'-', 26}, {'0', 1}, {'1', 1}, {'2', 1}, {'3', 1}, {'4', 1}, {'5', 1}, {'6', 1}, {'7', 1}, {'8', 1}, {'9', 1}, {'>', 10}, {'<', 11}, {'\\', 21}, {':', 9}, {'{', 7}, {'*', 22}}},
        {1, {{'0', 1}, {'1', 1}, {'2', 1}, {'3', 1}, {'4', 1}, {'5', 1}, {'6', 1}, {'7', 1}, {'8', 1}, {'9', 1}, {'.', 4}, {' ', 24}, {'\t', 24}, {'\n', 24}}},
        {2, {{'other', 2}}},
        {3, {{'other', 3}}},
        {4, {{'0', 5}, {'1', 5}, {'2', 5}, {'3', 5}, {'4', 5}, {'5', 5}, {'6', 5}, {'7', 5}, {'8', 5}, {'9', 5}, {' ', 6}, {'\t', 6}, {'\n', 6}}},
        {5, {{'0', 5}, {'1', 5}, {'2', 5}, {'3', 5}, {'4', 5}, {'5', 5}, {'6', 5}, {'7', 5}, {'8', 5}, {'9', 5}, {' ', 6}, {'\t', 6}, {'\n', 6}}},
        {6, {{'other', 6}}},
        {7, {{'other', 7}, {'}', 0}}},
        {9, {{'=', 17}}},
        {10, {{'=', 14}}},
        {11, {{'other', 12}}},
        {12, {{'=', 16}}},
        {13, {{'other', 13}}},
        {14, {{'=', 15}}},
        {15, {{'=', 15}}},
        {16, {{'other', 16}}},
        {17, {{'a', 18}, {'A', 18}, {'z', 18}, {'Z', 18}, {'0', 18}, {'1', 18}, {'9', 18}, {'other', 20}}},
        {18, {{'other', 18}}},
        {19, {{'a', 19}, {'A', 19}, {'z', 19}, {'Z', 19}, {'0', 19}, {'1', 19}, {'9', 19}, {'other', 20}}},
        {21, {{'other', 21}}},
        {22, {{'+', 28}, {'-', 28}, {'other', 22}}},
        {24, {{'+', 28}, {'-', 28}}},
        {25, {{' ', 25}, {'\t', 25}, {'\n', 25}}},
        {27, {{'+', 28}, {'-', 28}}}
    };


public:
    auto get_state() -> unsigned int
    {
        return state;
    }

    auto next_state(const char& c)
    {
        unsigned int new_state;

        new_state = tabela[state][c];
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
