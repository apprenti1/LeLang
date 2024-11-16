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

const char *keywords[] = {"int", "float", "char", "void", NULL};

int is_keyword(const char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_token(List *tokens, int *count, TokenType type, const char *value) {
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = malloc(strlen(value) + 1);
    strcpy(token->value, value);
    listAdd(tokens, CUSTOM, token);
}

void lex(const char *code, List *tokens, int *token_count) {
    int i = 0;
    ChainedString *buffer = chainedStringInit();
    while (code[i] != '\0') {
        if (isspace(code[i])) {
            i++;
            continue;
        }
        int j = 0;
        if (isalpha(code[i])) {
            while (isalpha(code[i]) || isdigit(code[i])) {
                chainedStringAppend(buffer, code[i]);
                i++;
            }
            if (is_keyword(chainedStringRender(*buffer))) {
                add_token(tokens, token_count, TOKEN_KEYWORD, chainedStringRender(*buffer));
            } else {
                add_token(tokens, token_count, TOKEN_IDENTIFIER, chainedStringRender(*buffer));
            }
        } else {
            i++;
        }
    }

}
