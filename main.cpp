#include <fstream>
#include <iostream>
#include <string>

#include "parser.hpp"

int main() {
  std::string filename{};
  std::cout << "Insert the input filename: ";
  std::cin >> filename;

  Parser parser{filename};

  parser.parse();
  std::cout << "Output of the parser was saved on the file output.txt."
            << std::endl;
}
