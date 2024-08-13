#ifndef TOKEN_H
#define TOKEN_H

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"
#include "Basic/TokenKinds.h"

class Token{
  tok::TokenKind Kind;
  const char *Ptr;
  size_t Len;
 public:
  void formToken(tok::TokenKind kind,
		 const char *BufferPtr, const size_t &len) {
    Kind = kind;
    Ptr = BufferPtr;
    Len = len;
  }
  tok::TokenKind getKind() const { return Kind; }
  size_t getLength() const { return Len; }
  llvm::SMLoc getLocation() const { return llvm::SMLoc::getFromPointer(Ptr); }
  bool is(tok::TokenKind k) { return Kind == k; }
  bool isOneOf(tok::TokenKind k, ...) {
    while(k != '\0') if(Kind == k) return true;
    return false;
  }
  llvm::StringRef getIdentifier() {
    assert(is(tok::IDENT));
    return llvm::StringRef(Ptr, Len);
  }
  llvm::StringRef getLiteralData() {
    assert(isOneOf(tok::INT_LIT,tok::STR_LIT));
    return llvm::StringRef(Ptr, Len);
  }
  std::string kindToString(){
    switch (Kind) {
#define CASE(t, str)						\
      case t: return str; break
      CASE(tok::MODULE, "MODULE");
      CASE(tok::IMPORT, "IMPORT");
      CASE(tok::BEGIN, "BEGIN");
      CASE(tok::END, "END");
      CASE(tok::PROCEDURE, "PROCEDURE");
      CASE(tok::VAR, "VAR");
      CASE(tok::IF, "IF");
      CASE(tok::THEN, "THEN");
      CASE(tok::ELSE, "ELSE");
      CASE(tok::RETURN, "RETURN");
      CASE(tok::WHILE, "WHILE");
      CASE(tok::DO, "DO");
      CASE(tok::IDENT, "IDENT");
      CASE(tok::INT_LIT, "INT_LIT");
      CASE(tok::STR_LIT, "STR_LIT");
      CASE(tok::PUNC, "PUNC");
      CASE(tok::ASSIGN, "ASSIGN");
      CASE(tok::EQ, "EQ");
      CASE(tok::NEQ, "NEQ");
      CASE(tok::ADD_OP, "ADD_OP");
      CASE(tok::SUB_OP, "SUB_OP");
      CASE(tok::MULT_OP, "MULT_OP");
      CASE(tok::DIV_OP, "DIV_OP");
      CASE(tok::L_PAREN, "L_PAREN");
      CASE(tok::R_PAREN, "R_PAREN");
      CASE(tok::COLON, "COLON");
      CASE(tok::COMMA, "COMMA");
      CASE(tok::EOI, "EOI");
      CASE(tok::EOS, "EOS");
      CASE(tok::EOM, "EOM");
#undef CASE
    default:
      return "UNKNOWN";
    }

  }
  std::string toString() {
    return "("+kindToString()+","+std::string(Ptr, Len)+")";
  }
};
#endif
