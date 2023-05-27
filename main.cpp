#include <fstream>
#include <iostream>
#include <string>

#include "lexicalParser.hpp"

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

        token = parser.read_char(c);
        if (token)
            std::cout << token.value() << std::endl;
    }
}
