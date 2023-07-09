#include <fstream>
#include <iostream>
#include <string>

#include "parser.hpp"

int main() {
  std::string filename{};
  std::ofstream output_file;

  std::cout << "Insert the input filename: ";
  std::cin >> filename;

  output_file.open("output.txt");

  Parser parser{filename};

  parser.parse();

  std::cout << std::endl;
  std::cout << "Output of the parser was saved on the file output.txt."
            << std::endl;
}
