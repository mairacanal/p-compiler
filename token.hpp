#pragma once

#include <istream>
#include <string>

#define get_token_type(c) #c

enum TokenType
{
    simb_program,
    id,
    simb_pv,
    simb_var,
};

class Token {
private:
    std::string token;
    TokenType type;

public:
    friend auto operator<<(std::ostream& os, const Token& token) -> std::ostream&
    {
        os << token << "," << get_token_type(token.type);
        return os;
    }
};
