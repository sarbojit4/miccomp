#include "Lexer/Lexer.h"

namespace charinfo {
  LLVM_READNONE inline bool isWhitespace(char c){
    return c == ' ' || c == '\t' || c == '\f' ||
      c == '\v' || c == '\r' || c == '\n';
  }
  LLVM_READNONE inline bool isDigit(char c){
    return c >= '0' && c <= '9';
  }
  LLVM_READNONE inline bool isLetter(char c){
    return (c >= 'a' && c <= 'z') ||
      (c >= 'A' && c <= 'Z');
  }
};

bool Lexer::get_next(Token &token){
  while(*BufferPtr && charinfo::isWhitespace(*BufferPtr)) BufferPtr++;
  if(!*BufferPtr){
    token.formToken(tok::EOI, BufferPtr, 1);
    return false;
  }
  if(charinfo::isDigit(*BufferPtr)){
    size_t len = 0;
    while(charinfo::isDigit(*(BufferPtr+len))) len++;
    token.formToken(tok::INT_LIT, BufferPtr, len);
    BufferPtr += len;
  }
  else if(charinfo::isLetter(*BufferPtr)){
    size_t len = 0;
    while(charinfo::isLetter(*(BufferPtr+len))) len++;
    llvm::StringRef str = llvm::StringRef(BufferPtr, len);
    tok::TokenKind kind;
    if(str == "MODULE") kind = tok::MODULE;
    else if(str == "IMPORT") kind = tok::IMPORT;
    else if(str == "PROCEDURE") kind = tok::PROCEDURE;
    else if(str == "BEGIN") kind = tok::BEGIN;
    else if(str == "END") kind = tok::END;
    else if(str == "VAR") kind = tok::VAR;
    else if(str == "IF") kind = tok::IF;
    else if(str == "THEN") kind = tok::THEN;
    else if(str == "ELSE") kind = tok::ELSE;
    else if(str == "WHILE") kind = tok::WHILE;
    else if(str == "DO") kind = tok::DO;
    else if(str == "RETURN") kind = tok::RETURN;
    else kind = tok::IDENT;
    token.formToken(kind, BufferPtr, len);
    BufferPtr += len;
  }
  else{
    switch (*BufferPtr) {
#define CASE(ch, tok)						\
      case ch: token.formToken(tok, BufferPtr, 1); break;
      CASE('=', tok::EQ);
      CASE('#', tok::NEQ);
      CASE('+', tok::ADD_OP);
      CASE('-', tok::SUB_OP);
      CASE('*', tok::MULT_OP);
      CASE('/', tok::DIV_OP);
      CASE('(', tok::L_PAREN);
      CASE(')', tok::R_PAREN);
      CASE(',', tok::COMMA);
      CASE(';', tok::EOS);
      CASE('.', tok::EOM);
#undef CASE
    case ':':
      if(*(BufferPtr+1) == '=') {
	token.formToken(tok::ASSIGN, BufferPtr, 2);
	BufferPtr++;
      } else token.formToken(tok::COLON, BufferPtr, 1);
      break;
    default: token.formToken(tok::UNKNOWN, BufferPtr, 1);
    }
    BufferPtr++;
  }
  return true;
}

