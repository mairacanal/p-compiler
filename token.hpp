#pragma once

#include <istream>
#include <string>

class Token {
 private:
  std::string value;
  std::string type;

 public:
  Token(std::string value, std::string type) : value{value}, type{type} {}

  /**
 * @brief Overloaded insertion operator for printing a Token object to an output stream.
 * 
 * This function allows a Token object to be printed to an output stream (std::ostream) in a customized way.
 *
 * @param os The output stream where the Token object will be inserted.
 * @param token The Token object that will be inserted into the output stream.
 * @return A reference to the output stream after the Token object has been inserted.
 */
 
  friend auto operator<<(std::ostream &os, const Token &token)
      -> std::ostream & {
    os << token.value << ", " << token.type;
    return os;
  }
};
