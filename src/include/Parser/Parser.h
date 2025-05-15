#ifndef PARSER_H
#define PARSER_H

#include "Lexer/Lexer.h"
#include "AST/AST.h"

class Parser {
 private:
  Lexer Lex;
  AST ASTree;
  Token CurrTok;
  bool consume(tok::TokenKind expected) {
    if(CurrTok.is(expected)) {
      Lex.get_next(CurrTok);
      return true;
    }
    return false;
  }
  bool expect(tok::TokenKind expected) {
    if(CurrTok.is(expected)) {
      return true;
    }
    return false;
  }
 public:
  Parser(Lexer lex) : Lex(lex) { Lex.get_next(CurrTok); }
  bool parse();
  bool parse_module();
};
#endif
