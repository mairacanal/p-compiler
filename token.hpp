#pragma once

#include <istream>
#include <string>

class Token {
private:
    std::string token;
    std::string type;

public:
    Token(std::string token, std::string type) : token{token}, type{type} {}

    friend auto operator<<(std::ostream& os, const Token& token) -> std::ostream&
    {
        os << token.type << "," << token.token;
        return os;
    }
};
