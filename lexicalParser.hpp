#pragma once

#include <optional>
#include "token.hpp"

class LexicalParser {
public:
    auto read_char(const char& c) -> std::optional<Token>
    {
        std::cout << "char: " << c << std::endl;


        return {};
    }
};
