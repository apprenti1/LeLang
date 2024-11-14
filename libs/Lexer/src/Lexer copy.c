#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include<stdlib.h>


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

const char *keywords[] = {"int", "float", "char", "void", NULL};

int is_keyword(const char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


void add_token(Token *tokens, int *count, TokenType type, const char *value) {
    tokens[*count].type = type;
    strncpy(tokens[*count].value, value, sizeof(tokens[*count].value) - 1);
    tokens[*count].value[sizeof(tokens[*count].value) - 1] = '\0';
    (*count)++;
}

void lex(const char *code, Token *tokens, int *token_count) {
    printf("test1\n");
    int i = 0;
    while (code[i] != '\0') {
        if (isspace(code[i])) {
            i++;
            continue;
        }
        
        if (isalpha(code[i])) {
                printf("test1\n");

            
            int j = 0;
            char buffer[64];
            while (isalpha(code[i]) || isdigit(code[i])) {
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';
            if (is_keyword(buffer)) {

                add_token(tokens, token_count, TOKEN_KEYWORD, buffer);
            } else {
                add_token(tokens, token_count, TOKEN_IDENTIFIER, buffer);
            }
            continue;
        }        
        if (isdigit(code[i])) {
            char buffer[64];
            int j = 0;
            while (isdigit(code[i])) {
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';
            add_token(tokens, token_count, TOKEN_NUMBER, buffer);
            continue;
        }
        
        switch (code[i]) {
            case '=':
                if (code[i+1] == '=') {
                    add_token(tokens, token_count, TOCKEN_TEST, "==");
                    i += 2;
                } else {
                    add_token(tokens, token_count, TOCKEN_DEFINITION, "=");
                    i++;
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                {
                    char op[2] = {code[i], '\0'};
                    add_token(tokens, token_count, TOKEN_OPERATOR, op);
                    i++;
                }
                break;
            case ';':
                add_token(tokens, token_count, TOKEN_DELIMITER, ";");
                i++;
                break;
            case ',':
                add_token(tokens, token_count, TOKEN_COMMA, ",");
                i++;
                break;
            case '(':
                add_token(tokens, token_count, TOKEN_PARENTHESIS_OPEN, "(");
                i++;
                break;
            case ')':
                add_token(tokens, token_count, TOKEN_PARENTHESIS_CLOSE, ")");
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
                    add_token(tokens, token_count, TOKEN_STRING, buffer);
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
                    add_token(tokens, token_count, TOKEN_STRING, buffer);
                }
                break;
            default:
                i++;
                break;
        }
    }
    printf("test1\n");

}
