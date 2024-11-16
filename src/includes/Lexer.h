#ifndef LEXER_H
#define LEXER_H


#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "ChainedList.h"

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
    char *value;
} Token;

void lex(const char *code, List *tokens);

#endif
