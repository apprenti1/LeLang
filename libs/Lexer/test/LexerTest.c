//!  gcc -o build/test/LexerTest libs/Lexer/test/LexerTest.c libs/Lexer/src/Lexer.c -Ilibs/Lexer/include && ./build/test/LexerTest

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "Lexer.h"

void test_lex() {
    char *code = "int a = 33+2; printf('%i|%f', 6*8, a);a==7";
    Token tokens[64];
    int token_count = 0;
    lex(code, tokens, &token_count);

    assert(token_count == 21);

    assert(tokens[0].type == TOKEN_KEYWORD);
    assert(strcmp(tokens[0].value, "int") == 0);

    assert(tokens[1].type == TOKEN_IDENTIFIER);
    assert(strcmp(tokens[1].value, "a") == 0);

    assert(tokens[2].type == TOCKEN_DEFINITION);
    assert(strcmp(tokens[2].value, "=") == 0);

    assert(tokens[3].type == TOKEN_NUMBER);
    assert(strcmp(tokens[3].value, "33") == 0);

    assert(tokens[4].type == TOKEN_OPERATOR);
    assert(strcmp(tokens[4].value, "+") == 0);

    assert(tokens[5].type == TOKEN_NUMBER);
    assert(strcmp(tokens[5].value, "2") == 0);

    assert(tokens[6].type == TOKEN_DELIMITER);
    assert(strcmp(tokens[6].value, ";") == 0);

    assert(tokens[7].type == TOKEN_IDENTIFIER);
    assert(strcmp(tokens[7].value, "printf") == 0);

    assert(tokens[8].type == TOKEN_PARENTHESIS_OPEN);
    assert(strcmp(tokens[8].value, "(") == 0);

    assert(tokens[9].type == TOKEN_STRING);
    assert(strcmp(tokens[9].value, "'%i|%f'") == 0);

    assert(tokens[10].type == TOKEN_COMMA);
    assert(strcmp(tokens[10].value, ",") == 0);

    assert(tokens[11].type == TOKEN_NUMBER);
    assert(strcmp(tokens[11].value, "6") == 0);

    assert(tokens[12].type == TOKEN_OPERATOR);
    assert(strcmp(tokens[12].value, "*") == 0);

    assert(tokens[13].type == TOKEN_NUMBER);
    assert(strcmp(tokens[13].value, "8") == 0);

    assert(tokens[14].type == TOKEN_COMMA);
    assert(strcmp(tokens[14].value, ",") == 0);

    assert(tokens[15].type == TOKEN_IDENTIFIER);
    assert(strcmp(tokens[15].value, "a") == 0);

    assert(tokens[16].type == TOKEN_PARENTHESIS_CLOSE);
    assert(strcmp(tokens[16].value, ")") == 0);

    assert(tokens[17].type == TOKEN_DELIMITER);
    assert(strcmp(tokens[17].value, ";") == 0);

    assert(tokens[18].type == TOKEN_IDENTIFIER);
    assert(strcmp(tokens[18].value, "a") == 0);

    assert(tokens[19].type == TOCKEN_TEST);
    assert(strcmp(tokens[19].value, "==") == 0);

    assert(tokens[20].type == TOKEN_NUMBER);
    assert(strcmp(tokens[20].value, "7") == 0);

    printf("\033[32mOK\033[0m | test_lex\n");
}

int main() {
    test_lex();
    return 0;
}