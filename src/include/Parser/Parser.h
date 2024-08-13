#ifndef PARSER_H
#define PARSER_H

#include "Lexer/Lexer.h"
#include "AST/AST.h"

class Parser {
 private:
  Lexer Lex;
  AST ASTree;
 public:
  Parser(Lexer lex) : Lex(lex) {}
  void parse();
};
#endif
