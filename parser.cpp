#include "parser.hpp"

/**
 * @brief
 *
 * @param exp_token
 * @param empty
 * @return true
 * @return false
 */
bool Parser::match(const std::string& exp_token, bool empty) {
  std::cout << token << std::endl;

  if (token.get_type() != exp_token) {
    if (empty) return true;

    // TODO: error!
    return true;
  }

  token = get_token();
  return false;
}

/**
 * @brief <programa> ::= program ident ; <corpo> .
 */
void Parser::programa() {
  match("simb_program");
  match("id");
  match("simb_semicolon");
  corpo();
  match("simb_dot");
}

/**
 * @brief <corpo> ::= <dc> begin <comandos> end
 */
void Parser::corpo() {
  dc();
  match("simb_begin");
  comandos();
  match("simb_end");
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
    // TODO: add const to the transition table
    // match("simb_const");
    match("id");
    // TODO: add simb_equal to the transition table
    // match("simb_equal")
    numero();
    match("simb_semicolon");
  }
}

/**
 * @brief <dc_v> ::= var <variaveis> : <tipo_var> ; <dc_v> | λ
 */
void Parser::dc_v() {
  while (token.get_type() == "simb_var") {
    match("simb_var");
    variaveis();
    match("simb_colon");
    tipo_var();
    match("simb_semicolon");
  }
}

/**
 * @brief <tipo_var> ::= real | integer
 */
void Parser::tipo_var() {
  if (token.get_type() != "simb_type" && token.get_type() != "simb_real") {
    std::cout << "Erro sintático: " << token.get_value()
              << " não é um tipo válido." << std::endl;
    token = get_token();
    return;
  }

  std::cout << token << std::endl;
  token = get_token();
}

/**
 * @brief <variaveis> ::= ident <mais_var>
 */
void Parser::variaveis() {
  match("id");

  // <mais_var>
  while (token.get_type() == "simb_comma") {
    match("simb_comma");
    match("id");
  }
}

/**
 * @brief <dc_p> ::= procedure ident <parametros> ; <corpo_p> <dc_p> | λ
 */
void Parser::dc_p() {
  while (token.get_type() == "simb_proc") {
    match("simp_proc");
    match("id");
    parametros();
    match("simb_semicolon");
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

  // <mais_par>
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
  match("simb_begin");
  comandos();
  match("simb_end");
  match("simb_semicolon");
}

/**
 * @brief <dc_loc> ::= <dc_v>
 */
void Parser::dc_loc() { dc_v(); }

/**
 * @brief <lista_arg> ::= ( <argumentos> ) | λ
 */
void Parser::lista_arg() {
  if (match("simb_lpar", true)) return;
  argumentos();
  match("simp_rpar");
}

/**
 * @brief <argumentos> ::= ident <mais_ident>
 */
void Parser::argumentos() {
  match("id");

  // <mais_ident>
  while (token.get_type() == "simb_semicolon") {
    match("simb_semicolon");
    match("id");
  }
}

/**
 * @brief <pfalsa> ::= else <cmd> | λ
 *
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
    match("simb_semicolon");

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

  if (cur_token == "simb_read") {
    match("simb_read");
    match("simb_lpar");
    variaveis();
    match("simb_rpar");

    return;
  }

  if (cur_token == "simb_write") {
    match("simb_write");
    match("simb_lpar");
    variaveis();
    match("simb_rpar");

    return;
  }

  if (cur_token == "simb_while") {
    match("simb_while");
    match("simb_lpar");
    condicao();
    match("simb_rpar");
    match("simb_do");
    cmd();

    return;
  }

  if (cur_token == "simb_for") {
    match("simb_for");
    match("id");
    match("simb_atrib");
    expressao();
    match("simb_to");
    expressao();
    match("simb_do");
    cmd();

    return;
  }

  if (cur_token == "simb_if") {
    match("simb_if");
    condicao();
    match("simb_then");
    cmd();
    pfalsa();

    return;
  }

  if (cur_token == "id") {
    match("id");
    cmd_ident_tail();

    return;
  }

  if (cur_token == "simb_begin") {
    match("simb_begin");
    comandos();
    match("simb_end");

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
    std::cout << "Erro sintático: " << token.get_value()
              << " não é uma relacao valida." << std::endl;
    token = get_token();
    return;
  }

  std::cout << token << std::endl;
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
    std::cout << token << std::endl;

    token = get_token();
    return;
  }
}

/**
 * @brief <outros_termos> ::= <op_ad> <termo> <outros_termos> | λ
 */
void Parser::outros_termos() {
  while (token.get_type() == "simb_plus" || token.get_type() == "simb_minus") {
    std::cout << token << std::endl;

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
    std::cout << token << std::endl;
    token = get_token();
    return;
  } else {
    token = get_token();
    std::cout << "Erro sintático: " << token.get_value()
              << " não é uma operacao valida." << std::endl;
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
  while (token.get_type() == "simb_mul" || token.get_type() == "simb_divide") {
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
    std::cout << "Erro sintático: " << token.get_value()
              << " não é uma operação valida." << std::endl;
    token = get_token();
    return;
  }
  std::cout << token << std::endl;
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
    std::cout << "Erro sintático: " << token.get_value()
              << " não é um fato válido." << std::endl;
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
    std::cout << "Erro sintático: " << token.get_value()
              << " não é número real ou inteiro." << std::endl;
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
 * @brief
 *
 * @return Token
 */
Token Parser::get_token() {
  if (lexical.should_go_back()) {
    std::optional<Token> token{};

    token = lexical.next(c);
    if (token) {
      if (!token.value().get_type().find("Erro Léxico"))
        std::cout << token.value().get_type() << std::endl;
      else
        return token.value();
    }
  }

  while (file >> std::noskipws >> c) {
    std::optional<Token> token{};

    token = lexical.next(c);
    if (token) {
      if (!token.value().get_type().find("Erro Léxico"))
        std::cout << token.value().get_type() << std::endl;
      else
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
  token = get_token();
  programa();

  // TODO:
  // se (terminou_cadeia) SUCESSO
  // caso contrário ERRO
}
