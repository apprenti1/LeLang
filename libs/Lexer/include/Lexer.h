#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOCKEN_DEFINITION,
    TOCKEN_TEST,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_PARENTHESIS_OPEN,
    TOKEN_PARENTHESIS_CLOSE,
    TOKEN_COMMA,
    TOKEN_DELIMITER,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[64];
} Token;

void lex(const char *code, Token *tokens, int *token_count);

#endif
