//!  gcc -o build/main main.c libs/Lexer/src/Lexer.c -Ilibs/include


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "Lexer.h"

char* getArgument(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return NULL;
    }
    char *resolvedPath = malloc(PATH_MAX);
    if (resolvedPath == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    if (realpath(argv[1], resolvedPath) == NULL) {
        perror("Error resolving path");
        free(resolvedPath);
        return NULL;
    }
    return resolvedPath;
}



int main(int argc, char *argv[]) {
    

    char *resolvedPath = getArgument(argc, argv);
    
    printf("File path: %s\n", resolvedPath);

    FILE *file = fopen(resolvedPath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = malloc(fileSize + 1);
    if (content == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }
    fread(content, 1, fileSize, file);
    content[fileSize] = '\0';
    fclose(file);

    //printf("%s", content);

    int token_count = 0;
    Token *tokens = malloc(sizeof(Token)*(token_count));

    lex(content, tokens, &token_count);


    const char *token_type_names[] = {
        "type de variable",
        "nom de variable ou fonction",
        "opérateur, +,-,*,/",
        "définission d'une variable",
        "test d'égalité",
        "nombre",
        "chaine de char",
        "parenthese ouvrante",
        "parenthese fermante",
        "virgule",
        "fin de commande",
        "ensemble non reconnu"
    };

    for (int i = 0; i < token_count; i++) {
        printf("Token Type: %s, Value: %s\n", token_type_names[tokens[i].type], tokens[i].value);
    }





    free(content);
    

    return 0;
}
