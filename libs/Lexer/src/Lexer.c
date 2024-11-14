#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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
    int i = 0;
    int buffer_size = 64;
    char *buffer = malloc(buffer_size);

    if (!buffer) {
        perror("Erreur d'allocation mémoire");
        exit(1);
    }

    while (code[i] != '\0') {
        if (isspace(code[i])) {
            i++;
            continue;
        }

        int j = 0;  

        if (isalpha(code[i])) {
            // Identifiants et mots-clés
            while (isalpha(code[i]) || isdigit(code[i])) {
                if (j + 1 >= buffer_size) {
                    buffer_size *= 2; // Double la taille du buffer si nécessaire
                    char *temp = realloc(buffer, buffer_size);
                    if (!temp) {
                        free(buffer);
                        perror("Erreur de réallocation mémoire");
                        exit(1);
                    }
                    buffer = temp;
                }
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';

            if (is_keyword(buffer)) {
                add_token(tokens, token_count, TOKEN_KEYWORD, buffer);
            } else {
                add_token(tokens, token_count, TOKEN_IDENTIFIER, buffer);
            }
        } else {
            i++;
        }
    }

}
