#include <fstream>
#include <iostream>
#include <string>

#include "lexical_parser.hpp"

int main() {
  LexicalParser parser;
  std::string filename{};
  std::ifstream file;
  std::ofstream output_file;
  char c;

  std::cout << "Insert the input filename: ";
  std::cin >> filename;

  file.open(filename);
  output_file.open("output.txt");

  std::cout << "The lexical analyzer result is:" << std::endl;
  std::cout << std::endl;

  while (file >> std::noskipws >> c) {
    do {
      std::optional<Token> token{};

      token = parser.next(c);
      if (token) {
        std::cout << token.value() << std::endl;
        output_file << token.value() << std::endl;
      };
    } while (parser.should_go_back());
  }

  std::cout << std::endl;
  std::cout
      << "Output of the lexical analyzer was saved on the file output.txt."
      << std::endl;
}
