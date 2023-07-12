#include "parser.hpp"

class SyntaxException : public std::exception {
 private:
  const std::string msg;

 public:
  SyntaxException(const std::string& msg) : msg{msg} {}
  const std::string panic() const { return msg; }
};

/**
 * @brief
 *
 * @param exp_token
 * @param empty
 * @return true
 * @return false
 */

bool Parser::match(const std::string& exp_token, bool empty) {
  if (token.get_type() != exp_token) {
    if (empty) return true;
    flag_err = true;
    if (!flag_lex)
      throw SyntaxException("Erro Sintático na linha " +
                            std::to_string(token.get_line()) + ": esperava " +
                            exp_token + " foi recebido " + token.get_value());
  }
  output_file << token << std::endl;
  token = get_token();
  return false;
}

/**
 * @brief <programa> ::= program ident ; <corpo> .
 */
void Parser::programa() {
  try {
    match("simb_program");
    match("id");
    match("simb_semicolon");
  } catch (const SyntaxException& se) {
    output_file << se.panic() << std::endl;
    panic_mode({"simb_const", "simb_var", "simb_proc", "simb_begin"});
  }
  corpo();
  try {
    match("simb_dot");
  } catch (const SyntaxException& se) {
    output_file << se.panic() << std::endl;
  }
}

void Parser::panic_mode(const std::vector<std::string>& sync_tokens) {
  bool flag = false;
  while (!flag) {
    for (const auto& st : sync_tokens)
      if (token.get_type() == st) {
        flag = true;
        return;
      }
    token = get_token();
  }
}

/**
 * @brief <corpo> ::= <dc> begin <comandos> end
 */
void Parser::corpo() {
  dc();
  try {
    match("simb_begin");
  } catch (const SyntaxException& se) {
    output_file << se.panic() << std::endl;
    panic_mode({"simb_read", "simb_write", "simb_while", "simb_for", "simb_if",
                "simb_begin", "id"});
  }
  comandos();
  try {
    match("simb_end");
  } catch (const SyntaxException& se) {
    output_file << se.panic() << std::endl;
    panic_mode({"simb_dot"});
  }
}

/**
 * @brief <dc> ::= <dc_c> <dc_v> <dc_p>
 */
void Parser::dc() {
  dc_c();
  dc_v();
  dc_p();
}

/**
 * @brief <dc_c> ::= const ident = <numero> ; <dc_c> | λ
 */
void Parser::dc_c() {
  while (token.get_type() == "simb_const") {
    try {
      match("simb_const");
      match("id");
      match("simb_equal");
      numero();
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_semicolon"});
    }
    try {
      match("simb_semicolon");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_var", "simb_proc", "simb_begin"});
    }
  }
}

/**
 * @brief <dc_v> ::= var <variaveis> : <tipo_var> ; <dc_v> | λ
 */
void Parser::dc_v() {
  while (token.get_type() == "simb_var") {
    try {
      match("simb_var");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"id"});
    }
    variaveis();
    try {
      match("simb_colon");
      tipo_var();
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_semicolon"});
    }
    try {
      match("simb_semicolon");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_proc", "simb_begin"});
    }
  }
}

/**
 * @brief <tipo_var> ::= real | integer
 */
void Parser::tipo_var() {
  if (token.get_type() != "simb_type" && token.get_type() != "simb_real") {
    output_file << "Erro sintático na linha" +
                       std::to_string(token.get_line()) + ": "
                << token.get_value() << " não é um tipo válido." << std::endl;

    token = get_token();
    return;
  }

  output_file << token << std::endl;
  token = get_token();
}

/**
 * @brief <variaveis> ::= ident <mais_var>
 */
void Parser::variaveis() {
  try {
    match("id");
  } catch (const SyntaxException& se) {
    output_file << se.panic() << std::endl;
    panic_mode({"simb_colon", "simb_rpar"});
  }

  // <mais_var> ::= , <variaveis> | λ
  while (token.get_type() == "simb_comma") {
    // TODO: remove
    try {
      match("simb_comma");
      match("id");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_comma", "simb_colon", "simb_rpar"});
    }
  }
}

/**
 * @brief <dc_p> ::= procedure ident <parametros> ; <corpo_p> <dc_p> | λ
 */
void Parser::dc_p() {
  while (token.get_type() == "simb_proc") {
    try {
      match("simb_proc");
      match("id");
      parametros();
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_semicolon"});
    }
    try {
      match("simb_semicolon");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_var", "simb_begin"});
    }
    corpo_p();
  }
}

/**
 * @brief <parametros> ::= ( <lista_par> ) | λ
 */
void Parser::parametros() {
  if (match("simb_lpar", true)) return;
  lista_par();
  match("simb_rpar");
}

/**
 * @brief <lista_par> ::= <variaveis> : <tipo_var> <mais_par>
 */
void Parser::lista_par() {
  variaveis();
  match("simb_colon");
  tipo_var();

  // <mais_par> := ; <lista_par> | λ
  while (token.get_type() == "simb_semicolon") {
    match("simb_semicolon");
    variaveis();
    match("simb_colon");
    tipo_var();
  }
}

/**
 * @brief <corpo_p> ::= <dc_loc> begin <comandos> end ;
 */
void Parser::corpo_p() {
  dc_loc();
  try {
    match("simb_begin");
  } catch (const SyntaxException& se) {
    output_file << se.panic() << std::endl;
    panic_mode({"simb_read", "simb_write", "simb_while", "simb_for", "simb_if",
                "simb_begin", "id"});
  }
  comandos();
  try {
    match("simb_end");
  } catch (const SyntaxException& se) {
    output_file << se.panic() << std::endl;
    panic_mode({"simb_semicolon"});
  }
  try {
    match("simb_semicolon");
  } catch (const SyntaxException& se) {
    output_file << se.panic() << std::endl;
    panic_mode({"simb_begin"});
  }
}

/**
 * @brief <dc_loc> ::= <dc_v>
 */
void Parser::dc_loc() { dc_v(); }

/**
 * @brief <lista_arg> ::= ( <argumentos> ) | λ
 */
bool Parser::lista_arg() {
  if (match("simb_lpar", true)) return true;
  argumentos();
  match("simb_rpar");
  return false;
}

/**
 * @brief <argumentos> ::= ident <mais_ident>
 */
void Parser::argumentos() {
  try {
    match("id");
  } catch (const SyntaxException& se) {
    output_file << se.panic() << std::endl;
    panic_mode({"simb_semicolon", "simb_rpar"});
  }

  // <mais_ident> = ; <argumentos> | λ
  while (token.get_type() == "simb_semicolon") {
    try {
      match("simb_semicolon");
      match("id");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"id", "simb_semicolon", "simb_rpar"});
    }
  }
}

/**
 * @brief <pfalsa> ::= else <cmd> | λ
 */
void Parser::pfalsa() {
  if (match("simb_else", true)) return;
  cmd();
}

/**
 * @brief <comandos> ::= <cmd> ; <comandos> | λ
 */
void Parser::comandos() {
  // Possible cmd: read, write, while, if, ident, begin
  std::string cur_token = token.get_type();

  // First(<cmd>)
  while (cur_token == "simb_read" || cur_token == "simb_write" ||
         cur_token == "simb_while" || cur_token == "simb_for" ||
         cur_token == "simb_if" || cur_token == "simb_begin" ||
         cur_token == "id") {
    cmd();
    try {
      match("simb_semicolon");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_read", "simb_write", "simb_while", "simb_for",
                  "simb_if", "id", "simb_begin", "simb_end", "simb_semicolon"});
    }

    // Update current token
    cur_token = token.get_type();
  }
}

/**
 * @brief <cmd> ::= read ( <variaveis> ) |
 *                  write ( <variaveis> ) |
 *                  while ( <condicao> ) do <cmd> |
 *                  for ident := <expressão> to <expressão> do <cmd> |
 *                  if <condicao> then <cmd> <pfalsa> |
 *                  ident := <expressão> |
 *                  ident <lista_arg> |
 *                  begin <comandos> end
 */
void Parser::cmd() {
  std::string cur_token = token.get_type();

  try {
    if (cur_token == "simb_read") {
      match("simb_read");
      match("simb_lpar");
      variaveis();
      match("simb_rpar");

      return;
    }
  } catch (const SyntaxException& se) {
    output_file << se.panic() << std::endl;
    panic_mode({"simb_read", "simb_write", "simb_while", "simb_for", "simb_if",
                "id", "simb_begin", "simb_end", "simb_semicolon"});
  }
  try {
    if (cur_token == "simb_write") {
      match("simb_write");
      match("simb_lpar");
      variaveis();
      match("simb_rpar");
      return;
    }
  } catch (const SyntaxException& se) {
    output_file << se.panic() << std::endl;
    panic_mode({"simb_read", "simb_write", "simb_while", "simb_for", "simb_if",
                "id", "simb_begin", "simb_end", "simb_semicolon"});
  }

  if (cur_token == "simb_while") {
    try {
      match("simb_while");
      match("simb_lpar");
      condicao();
      match("simb_rpar");
      match("simb_do");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_read", "simb_write", "simb_while", "simb_for",
                  "simb_if", "id", "simb_begin", "simb_end", "simb_semicolon"});
    }
    cmd();

    return;
  }

  if (cur_token == "simb_for") {
    try {
      match("simb_for");
      match("id");
      match("simb_atrib");
      expressao();
      match("simb_to");
      expressao();
      match("simb_do");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_read", "simb_write", "simb_while", "simb_for",
                  "simb_if", "id", "simb_begin", "simb_end", "simb_semicolon"});
    }
    cmd();
    return;
  }

  if (cur_token == "simb_if") {
    try {
      match("simb_if");
      condicao();
      match("simb_then");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_read", "simb_write", "simb_while", "simb_for",
                  "simb_if", "id", "simb_begin", "simb_end", "simb_semicolon",
                  "simb_then"});
    }
    cmd();
    pfalsa();
    return;
  }

  if (cur_token == "id") {
    try {
      match("id");
      cmd_ident_tail();
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_read", "simb_write", "simb_while", "simb_for",
                  "simb_if", "id", "simb_begin", "simb_semicolon"});
    }
    return;
  }

  if (cur_token == "simb_begin") {
    try {
      match("simb_begin");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_read", "simb_write", "simb_while", "simb_for",
                  "simb_if", "simb_begin", "id", "simb_end", "simb_semicolon"});
    }
    comandos();
    try {
      match("simb_end");
    } catch (const SyntaxException& se) {
      output_file << se.panic() << std::endl;
      panic_mode({"simb_read", "simb_write", "simb_while", "simb_for",
                  "simb_if", "simb_begin", "id", "simb_end", "simb_semicolon"});
    }
    return;
  }
}

/**
 * @brief cmd_ident_tail ::= := <expressao> | <lista_arg>
 */
void Parser::cmd_ident_tail() {
  // Check if current_token is :=
  if (token.get_type() == "simb_atrib") {
    match("simb_atrib");
    expressao();
  } else
    lista_arg();
}

/**
 * @brief <condicao> ::= <expressao> <relacao> <expressao>
 */
void Parser::condicao() {
  expressao();
  relacao();
  expressao();
}

/**
 * @brief <relacao> ::= = | <> | >= | <= | > | <
 */
void Parser::relacao() {
  if (token.get_type() != "simb_equal" && token.get_type() != "simb_diff" &&
      token.get_type() != "simb_geq" && token.get_type() != "simb_leq" &&
      token.get_type() != "simb_lesser" && token.get_type() != "simb_greater") {
    output_file << "Erro sintático na linha " +
                       std::to_string(token.get_line()) + " : "
                << token.get_value() << " não é uma relacao valida."
                << std::endl;
    return;
  }

  output_file << token << std::endl;
  token = get_token();
}

/**
 * @brief <expressao> ::= <termo> <outros_termos>
 */
void Parser::expressao() {
  termo();
  outros_termos();
}

/**
 * @brief <op_un> ::= + | - | λ
 */
void Parser::op_un() {
  if (token.get_type() == "simb_plus" || token.get_type() == "simb_minus") {
    output_file << token << std::endl;

    token = get_token();
    return;
  }
}

/**
 * @brief <outros_termos> ::= <op_ad> <termo> <outros_termos> | λ
 */
void Parser::outros_termos() {
  while (token.get_type() == "simb_plus" || token.get_type() == "simb_minus") {
    output_file << token << std::endl;

    token = get_token();
    termo();
  }
}

/**
 * @brief <op_ad> ::= + | -
 *
 */
void Parser::op_ad() {
  if (token.get_type() == "simb_plus" || token.get_type() == "simb_minus") {
    output_file << token << std::endl;
    token = get_token();
    return;
  } else {
    output_file << "Erro sintático na linha " +
                       std::to_string(token.get_line()) + " : "
                << token.get_value() << " não é uma operacao valida."
                << std::endl;
  }
}

/**
 * @brief <termo> ::= <op_un> <fator> <mais_fatores>
 */
void Parser::termo() {
  op_un();
  fator();
  mais_fatores();
}

/**
 * @brief <mais_fatores> ::= <op_mul> <fator> <mais_fatores> | λ
 */
void Parser::mais_fatores() {
  while (token.get_type() == "simb_multiply" ||
         token.get_type() == "simb_divide") {
    output_file << token << std::endl;
    token = get_token();
    fator();
  }
}

/**
 * @brief <op_mul> ::= * | /
 */
void Parser::op_mul() {
  if (token.get_type() != "simb_multiply" &&
      token.get_type() != "simb_divide") {
    output_file << "Erro sintático na linha " +
                       std::to_string(token.get_line()) + " : "
                << token.get_value() << " não é uma operação valida."
                << std::endl;
    token = get_token();
    return;
  }
  output_file << token << std::endl;
  token = get_token();
}

/**
 * @brief <fator> ::= ident | <numero> | ( <expressao> )
 */
void Parser::fator() {
  if (token.get_type() == "id") {
    match("id");
  } else if (token.get_type() == "integer_number") {
    match("integer_number");
  } else if (token.get_type() == "real_number") {
    match("real_number");
  } else if (token.get_type() == "simb_lpar") {
    match("simb_lpar");
    expressao();
    match("simb_rpar");
  } else {
    output_file << "Erro sintático na linha " +
                       std::to_string(token.get_line()) + " : "
                << token.get_value() << " não é um fator válido." << std::endl;
    token = get_token();
    return;
  }
}

/**
 * @brief <fator> ::= ident | <numero> | ( <expressao> )
 */
void Parser::numero() {
  if (token.get_type() != "integer_number" &&
      token.get_type() != "real_number") {
    output_file << "Erro sintático na linha " +
                       std::to_string(token.get_line()) + " : "
                << token.get_value() << " não é número real ou inteiro."
                << std::endl;
    return;
  }

  token = get_token();
}

/**
 * @brief Construct a new Parser:: Parser object
 *
 * @param Input filename
 */
Parser::Parser(const std::string& filename) { file.open(filename); }

/**
 * @brief Destroy the Parser:: Parser object
 */
Parser::~Parser() { file.close(); }

/**
 * @brief Get a token from the lexical parser
 *
 * @return Token
 */
Token Parser::get_token() {
  if (lexical.should_go_back()) {
    std::optional<Token> token{};
    token = lexical.next(c, line_number);
    if (token) {
      if (!token.value().get_type().find("Erro Léxico")) {
        output_file << "Erro na linha " << token.value().get_line() << ": "
                    << token.value().get_type() << std::endl;
        flag_lex = true;
        flag_err = true;
      } else {
        flag_lex = false;
        return token.value();
      }
    }
  }
  // TODO Remove

  while (file >> std::noskipws >> c) {
    std::optional<Token> token{};
    token = lexical.next(c, line_number);

    if (token) {
      if (!token.value().get_type().find("Erro Léxico")) {
        flag_lex = true;
        flag_err = true;
        output_file << "Erro na linha " << line_number << ": "
                    << token.value().get_type() << std::endl;
      } else
        flag_lex = false;
      return token.value();
    }
  }
  return Token{};
}

/**
 * @brief
 *
 */
void Parser::parse() {
  output_file.open("output.txt");
  line_number = 1;

  token = get_token();
  programa();
  if (flag_err)
    output_file << "Compilação apontou erros! Revise o código." << std::endl;
  else
    output_file << "Compilado com sucesso!" << std::endl;
}
