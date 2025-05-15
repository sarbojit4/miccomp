#include "Parser/Parser.h"
#include "llvm/Support/raw_ostream.h"

#ifndef ERR
#define ERR false
#endif

bool Parser::parse_module(){
  if(!consume(tok::MODULE)) return ERR;
  if(!expect(tok::IDENT)) return ERR;
  //while(
  return true;
}

bool Parser::parse(){
  return parse_module();
  
  // Token t;
  // while(Lex.get_next(t)){
    
  //   llvm::outs() << t.toString()<<" ";
  // }
  // llvm::outs() << "\n";
}
