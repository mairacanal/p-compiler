#include <fstream>
#include <iostream>
#include <string>

#include "lexical_parser.hpp"

int main()
{
    LexicalParser parser;
    std::string filename {};
    std::ifstream file;
    char c;

    std::cout << "Insira o nome do arquivo de entrada: ";
    std::cin >> filename;

    file.open(filename);

    while (file >> std::noskipws >> c) {
        std::optional<Token> token{};

        token = parser.next(c);
        if (token)
            std::cout << token.value() << std::endl;
    }
}
