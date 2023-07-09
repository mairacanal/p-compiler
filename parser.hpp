#pragma once

#include <fstream>
#include <iostream>

#include "lexical_parser.hpp"
#include "token.hpp"

class Parser {
 private:
  LexicalParser lexical;
  std::ifstream file;
  Token token;
  char c;

  bool match(const std::string& exp_token, bool empty = false);

  void programa();

  void corpo();

  void dc();

  void dc_c();

  void dc_v();

  void tipo_var();

  void variaveis();

  void dc_p();

  void parametros();

  void lista_par();

  void corpo_p();

  void dc_loc();

  void lista_arg();

  void argumentos();
  
  void pfalsa();

  void cmd_ident_tail();

  void comandos();

  void cmd();

  void condicao();

  void relacao();

  void expressao();

  void op_un();

  void outros_termos();

  void op_ad();

  void mais_fatores();

  void op_mul();

  void termo();

  void fator();

  void numero();

 public:
  Parser(const std::string& filename);
  ~Parser();

  Token get_token();
  void parse();
};