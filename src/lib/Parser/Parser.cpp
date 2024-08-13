#include "Parser/Parser.h"
#include "llvm/Support/raw_ostream.h"

void Parser::parse(){
  Token t;
  while(Lex.get_next(t)){
    llvm::outs() << t.toString()<<" ";
  }
  llvm::outs() << "\n";
}
