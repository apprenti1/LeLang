#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "Lexer.h"
#include "ChainedList.h"
#include "Parser.h"

char* getArgument(int argc, char *argv[]) {
    if (argc < 2) {
        return NULL;
    }
    char *resolvedPath = malloc(1024);
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

void printTokens(List *tokens) {
    const char *token_type_names[] = {
        "type de variable\t\t\t",
        "nom de variable ou fonction\t",
        "opérateur, +,-,*,/\t\t",
        "définission d'une variable\t",
        "test d'égalité\t\t\t",
        "nombre\t\t\t\t",
        "décimal\t\t\t\t",
        "chaine de char\t\t\t",
        "parenthese ouvrante\t\t",
        "parenthese fermante\t\t",
        "virgule\t\t\t\t",
        "fin de commande\t\t\t",
        "ensemble non reconnu"
    };

    ListNode *current = tokens->head;
    int index = 0;
    while (current != NULL) {
        printf("| %i -> %s | %s\n", index++, token_type_names[((Token *)(current->item))->type], ((Token *)(current->item))->value);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    List *tokens = listInit();
    VarList *varList = varListInit();

    if (argc < 2) {
        printf("Mode interactif activé. Tapez 'exit' pour quitter.\n");
        char input[1024];
        while (1) {
            ListFree(tokens);
            tokens = listInit();
            printf(">> ");
            scanf("%1023[^\n]", input);
            getchar();
            if (strcmp(input, "exit") == 0) {
                printf("Sortie du mode interactif.\n");
                exit(0);
            }
            
            lex(input, tokens);
            parseTokens(tokens, varList);
            printTokens(tokens);
        }

        ListFree(tokens);
        varListFree(varList);
        return 0;
    }

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

    lex(content, tokens);
    printTokens(tokens);
    parseTokens(tokens, varList);
    printTokens(tokens);

    free(content);
    ListFree(tokens);
    varListFree(varList);
    return 0;
}
