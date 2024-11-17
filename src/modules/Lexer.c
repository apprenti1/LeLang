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
    TOKEN_FLOAT,
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

const char *keywords[] = {"int", "float", "char", "void", "while", "for", NULL};

int is_keyword(const char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_token(List *tokens, TokenType type, const char *value) {
    Token *token = malloc(sizeof(Token));
    token->type = type;

    token->value = malloc(strlen(value) + 1);
    strcpy(token->value, value);
    listAdd(tokens, CUSTOM, token);
}

void lex(const char *code, List *tokens) {
    int i = 0;
    while (code[i] != '\0') {
        ChainedString *buffer = chainedStringInit();

        if (isspace(code[i])) {
            i++;
            continue;
        }

        if (isalpha(code[i])) {
            while (isalpha(code[i]) || isdigit(code[i])) {
                chainedStringAppend(buffer, code[i]);
                i++;
            }

            // add while or for
            if (is_keyword(chainedStringRender(*buffer))) {
                if (strcmp(chainedStringRender(*buffer), "while") == 0) {
                    add_token(tokens, TOKEN_KEYWORD, "while");
                } else if (strcmp(chainedStringRender(*buffer), "for") == 0) {
                    add_token(tokens, TOKEN_KEYWORD, "for");
                } else {
                    add_token(tokens, TOKEN_KEYWORD, chainedStringRender(*buffer));
                }
            } else {
                add_token(tokens, TOKEN_IDENTIFIER, chainedStringRender(*buffer));
            }
        }
        else if (isdigit(code[i])) {
            while (isdigit(code[i])) {
                chainedStringAppend(buffer, code[i]);
                i++;
            }
            add_token(tokens, TOKEN_NUMBER, chainedStringRender(*buffer));
        }
        else {
            switch (code[i]) {
                case '=':
                    if (code[i + 1] == '=') {
                        add_token(tokens, TOCKEN_TEST, "==");
                        i += 2;
                    } else {
                        add_token(tokens, TOCKEN_DEFINITION, "=");
                        i++;
                    }
                    break;
                case '+':
                case '-':
                case '*':
                case '/':
                    {
                        char op[2] = {code[i], '\0'};
                        add_token(tokens, TOKEN_OPERATOR, op);
                        i++;
                    }
                    break;
                case ';':
                    add_token(tokens, TOKEN_DELIMITER, ";");
                    i++;
                    break;
                case ',':
                    add_token(tokens, TOKEN_COMMA, ",");
                    i++;
                    break;
                case '(':
                    add_token(tokens, TOKEN_PARENTHESIS_OPEN, "(");
                    i++;
                    break;
                case ')':
                    add_token(tokens, TOKEN_PARENTHESIS_CLOSE, ")");
                    i++;
                    break;
                case '\"':
                    {
                        char buffer[64];
                        int j = 0;
                        buffer[j++] = code[i++];
                        while (code[i] != '\"' && code[i] != '\0') {
                            buffer[j++] = code[i++];
                        }
                        buffer[j++] = code[i++];
                        buffer[j] = '\0';
                        add_token(tokens, TOKEN_STRING, buffer);
                    }
                    break;
                case '\'':
                    {
                        char buffer[64];
                        int j = 0;
                        buffer[j++] = code[i++];
                        while (code[i] != '\'' && code[i] != '\0') {
                            buffer[j++] = code[i++];
                        }
                        buffer[j++] = code[i++];
                        buffer[j] = '\0';
                        add_token(tokens, TOKEN_STRING, buffer);
                    }
                    break;
                default:
                    i++;
                    break;
            }
        }
    }

}
