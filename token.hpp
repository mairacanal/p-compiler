#pragma once

#include <istream>
#include <string>

class Token {
private:
    std::string value;
    std::string type;

public:
    Token(std::string value, std::string type) : value{value}, type{type} {}

    friend auto operator<<(std::ostream& os, const Token& token) -> std::ostream&
    {
        os << token.value << ", " << token.type;
        return os;
    }
};
