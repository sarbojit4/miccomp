#ifndef TINYLANG_BASIC_TOKENKINDS_H
#define TINYLANG_BASIC_TOKENKINDS_H
namespace tok {
  enum TokenKind{
    MODULE,
    IMPORT,
    BEGIN,
    END,
    PROCEDURE,
    VAR,
    IF,
    THEN,
    ELSE,
    WHILE,
    DO,
    RETURN,
    IDENT,
    INT_LIT,
    STR_LIT,
    PUNC,
    ASSIGN,
    EQ,
    NEQ,
    ADD_OP,
    SUB_OP,
    MULT_OP,
    DIV_OP,
    L_PAREN,
    R_PAREN,
    COLON,
    COMMA,
    EOI,
    EOS,
    EOM,
    UNKNOWN
  };
  // const char *getTokenName(TokenKind Kind);
  // const char *getPunctuatorSpelling(TokenKind Kind);
  // const char *getKeywordSpelling(TokenKind Kind);
};
#endif
