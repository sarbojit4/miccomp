#ifndef AST_H
#define AST_H

#include "llvm/ADT/APSInt.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"


// class AST;
// class Expr;
// class Factor;
// class BinaryOp;
// class WithDecl;
// class ASTVisitor {
// public:
//   virtual void visit(AST &){};
//   virtual void visit(Expr &){};
//   virtual void visit(Factor &) = 0;
//   virtual void visit(BinaryOp &) = 0;
//   virtual void visit(WithDecl &) = 0;
// };

class AST {
public:
  virtual ~AST() {}
  /* virtual void accept(ASTVisitor &V) = 0; */
};

class Expr {
};

class Lit : public Expr {
private:
  enum {INT, STR} Type;
  union {
    llvm::APSInt IntVal;
    llvm::StringRef StrVal;
  };
public:
  void formIntLit(const llvm::APSInt &intVal) { Type = INT; IntVal = intVal; }
  void formStrLit(const llvm::StringRef &strVal) { Type = STR; StrVal = strVal; }
  bool isIntLit() { return (Type == INT); }
  bool isStrLit() { return (Type == STR); }
};

class Operator {
};

class VarDecl;

class VarExpr : public Expr {
private:
  VarDecl *Var;
};

class RelExpr : public Expr {
private:
  Expr Left;
  Expr Right;
  Operator Op;
public:
  void formRelExpr() {}
};

class VarDecl {
private:
  const VarExpr Var;
  const Expr Val;
public:
  VarDecl(const VarExpr &var, const Expr &val) : Var(var), Val(val) {}
};
  
class Stmt {
};

typedef std::vector<Stmt *> StmtList;

class AssignStmt : public Stmt {
private:
  const VarExpr Var;
  const Expr Val;
public:
  AssignStmt(const VarExpr &var, const Expr &val) : Var(var), Val(val) {}
};

class IfStmt : public Stmt {
private:
  const RelExpr Cond;
  StmtList IfStmts;
  StmtList ElseStmts;
public:
  IfStmt(const RelExpr cond, StmtList ifStmts, StmtList elseStmts) :
    Cond(cond), IfStmts(ifStmts), ElseStmts(elseStmts) {}
};

class WhileStmt : public Stmt {
private:
  const RelExpr Cond;
  StmtList Stmts;
public:
  WhileStmt(const RelExpr cond, StmtList stmts) :
    Cond(cond), Stmts(stmts) {}
};

class ModDecl {
private:
  llvm::StringRef Name;
  llvm::SmallVector<VarDecl, 16> VarDecls;
  //TODO: add import statement
  StmtList Stmts;
public:
  ModDecl(llvm::StringRef name) : Name(name) {}
};



#endif
