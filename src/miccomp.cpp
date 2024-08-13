#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"
//#include "llvm/Support/CommandLine.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

namespace miccomp{
  std::string getVersion(){ return "0.1"; }
};
  
int main(int argc, const char **argv){
  if(argc < 2){
    llvm::outs() << "Please specify one or more input files\n";
    return 0;
  }
  llvm::outs() << "Micro Language " << miccomp::getVersion() << "\n";
  llvm::InitLLVM X(argc, argv);
  llvm::SmallVector<const char *, 256> argvec(argv+1, argv+argc);
  for (const char *F : argvec) {
    llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>>
        FileOrErr = llvm::MemoryBuffer::getFile(F);
    if (std::error_code BufferError =
            FileOrErr.getError()) {
      llvm::errs() << "Error reading " << F << ": "
                   << BufferError.message() << "\n";
      continue;
    }
    llvm::SourceMgr SrcMgr;
    // DiagnosticsEngine Diags(SrcMgr);
    SrcMgr.AddNewSourceBuffer(std::move(*FileOrErr),
                              llvm::SMLoc());
    auto TheLexer = Lexer(SrcMgr);//, Diags);
    
    // auto TheSema = Sema(Diags);
    auto TheParser = Parser(TheLexer);
    TheParser.parse();
  }
}
