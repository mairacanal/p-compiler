#include <fstream>
#include <iostream>
#include <string>

#include "lexical_parser.hpp"

int main()
{
    LexicalParser parser;
    std::string filename {};
    std::ifstream file;
    std::ofstream output_file;
    char c;

    std::cout << "Insira o nome do arquivo de entrada: ";
    std::cin >> filename;

    file.open(filename);
    output_file.open("output.txt");

    while (file >> std::noskipws >> c) {
        do {
            std::optional<Token> token{};

            token = parser.next(c);
            if (token) {
                // TODO: remove this
                std::cout << token.value() << std::endl;

                output_file << token.value() << std::endl;
            }
        } while (parser.should_go_back());
    }

    std::cout << "Output do analisador léxico salvo no arquivo output.txt" << std::endl;
}
