#ifndef LEXER_H
#define LEXER_H

#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"

#include "Token.h"

class Lexer {
  const char *BufferStart;
  const char *BufferPtr;
  unsigned CurBufferID = 0;
public:
  Lexer(const llvm::SourceMgr &SrcMgr) {
    CurBufferID = SrcMgr.getMainFileID();
    BufferStart = SrcMgr.getMemoryBuffer(CurBufferID)->getBuffer().begin();
    BufferPtr = BufferStart;
  }
  bool get_next(Token &token);
};
#endif
