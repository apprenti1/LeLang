//!  gcc -o build/test/LexerTest libs/Lexer/test/LexerTest.c libs/Lexer/src/Lexer.c -Ilibs/Lexer/include && ./build/test/LexerTest

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "Lexer.h"
#include "ChainedList.h"

void test_lex() {
    char *code = "int a = 33+2; printf('%i|%f', 6*8, a);a==7";
    List *tokens = listInit();
    lex(code, tokens);

    assert(tokens->size == 21);

    assert(((Token *)listGet(tokens, 0))->type == TOKEN_KEYWORD);
    assert(strcmp(((Token *)listGet(tokens, 0))->value, "int") == 0);

    assert(((Token *)listGet(tokens, 1))->type == TOKEN_IDENTIFIER);
    assert(strcmp(((Token *)listGet(tokens, 1))->value, "a") == 0);

    assert(((Token *)listGet(tokens, 2))->type == TOCKEN_DEFINITION);
    assert(strcmp(((Token *)listGet(tokens, 2))->value, "=") == 0);

    assert(((Token *)listGet(tokens, 3))->type == TOKEN_NUMBER);
    assert(strcmp(((Token *)listGet(tokens, 3))->value, "33") == 0);

    assert(((Token *)listGet(tokens, 4))->type == TOKEN_OPERATOR);
    assert(strcmp(((Token *)listGet(tokens, 4))->value, "+") == 0);

    assert(((Token *)listGet(tokens, 5))->type == TOKEN_NUMBER);
    assert(strcmp(((Token *)listGet(tokens, 5))->value, "2") == 0);

    assert(((Token *)listGet(tokens, 6))->type == TOKEN_DELIMITER);
    assert(strcmp(((Token *)listGet(tokens, 6))->value, ";") == 0);

    assert(((Token *)listGet(tokens, 7))->type == TOKEN_IDENTIFIER);
    assert(strcmp(((Token *)listGet(tokens, 7))->value, "printf") == 0);

    assert(((Token *)listGet(tokens, 8))->type == TOKEN_PARENTHESIS_OPEN);
    assert(strcmp(((Token *)listGet(tokens, 8))->value, "(") == 0);

    assert(((Token *)listGet(tokens, 9))->type == TOKEN_STRING);
    assert(strcmp(((Token *)listGet(tokens, 9))->value, "'%i|%f'") == 0);

    assert(((Token *)listGet(tokens, 10))->type == TOKEN_COMMA);
    assert(strcmp(((Token *)listGet(tokens, 10))->value, ",") == 0);

    assert(((Token *)listGet(tokens, 11))->type == TOKEN_NUMBER);
    assert(strcmp(((Token *)listGet(tokens, 11))->value, "6") == 0);

    assert(((Token *)listGet(tokens, 12))->type == TOKEN_OPERATOR);
    assert(strcmp(((Token *)listGet(tokens, 12))->value, "*") == 0);

    assert(((Token *)listGet(tokens, 13))->type == TOKEN_NUMBER);
    assert(strcmp(((Token *)listGet(tokens, 13))->value, "8") == 0);

    assert(((Token *)listGet(tokens, 14))->type == TOKEN_COMMA);
    assert(strcmp(((Token *)listGet(tokens, 14))->value, ",") == 0);

    assert(((Token *)listGet(tokens, 15))->type == TOKEN_IDENTIFIER);
    assert(strcmp(((Token *)listGet(tokens, 15))->value, "a") == 0);

    assert(((Token *)listGet(tokens, 16))->type == TOKEN_PARENTHESIS_CLOSE);
    assert(strcmp(((Token *)listGet(tokens, 16))->value, ")") == 0);

    assert(((Token *)listGet(tokens, 17))->type == TOKEN_DELIMITER);
    assert(strcmp(((Token *)listGet(tokens, 17))->value, ";") == 0);

    assert(((Token *)listGet(tokens, 18))->type == TOKEN_IDENTIFIER);
    assert(strcmp(((Token *)listGet(tokens, 18))->value, "a") == 0);

    assert(((Token *)listGet(tokens, 19))->type == TOCKEN_TEST);
    assert(strcmp(((Token *)listGet(tokens, 19))->value, "==") == 0);

    assert(((Token *)listGet(tokens, 20))->type == TOKEN_NUMBER);
    assert(strcmp(((Token *)listGet(tokens, 20))->value, "7") == 0);

    printf("\033[1;32m|  \033[0m\033[32mOK\033[0m | test_lex\n");
}

int main() {
    test_lex();
    return 0;
}