/* Un lexer, ou analyseur lexical, est un outil qui prend en entr e un flux de
caract res et qui le d compose en une s quence de mots-cl s, appel s
jetons. Les jetons sont ensuite utilis s par l'analyseur syntaxique pour
v rifier que le code source est valide par rapport  une grammaire donn e. */


/* Structure du projet :
 * - lexer.c : le lexer qui prend en entr e un flux de caract res et qui le d compose en une s quence de jetons
 * - parser.c : l'analyseur syntaxique qui prend en entr e une s quence de jetons et qui v rifie que le code source est valide par rapport  une grammaire donn e
 * - ast.c : l'arbre abstrait qui repr sente le code source sous une forme hi rarchique
 * - variables.c : la gestion des variables qui permet de stocker et de r cup rer des valeurs
 * - fonctions.c : la gestion des fonctions qui permet de d finir et d appeler des sous-programmes
 * - main.c : le point d'entr e du programme qui lit le code source depuis un fichier et qui l'envoie au lexer
 *
 * les fichiers de header (.h) sont utilis s pour d finir les structures et les prototypes de fonctions
 */


/* Un lexer doit contenir au moins les fonctions suivantes :
 * - init() : initialise le lexer et pr pare le flux de caract res
 * - next() : prend le prochain caract re du flux et renvoie le jeton qui correspond
 * - current() : renvoie le jeton actuel
 * - push() : remet le jeton actuel dans le flux
 * - end() : lib re les ressources utilis es par le lexer */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    INT,
    PLUS,
    EOF
} TokenType;

typedef struct
{
    TokenType type;
    char *value;
} Token;

Token *currentToken;
Token *tokens;

void init(char *source)
{
    tokens = (Token *)malloc(sizeof(Token) * 100);

    int i = 0;
    char *token = strtok(source, " \n");
    while (token != NULL)
    {
        Token t;
        if (strcmp(token, "+") == 0)
        {
            t.type = PLUS;
        }
        else
        {
            t.type = INT;
        }
        t.value = token;
        tokens[i++] = t;
        token = strtok(NULL, " \n");
    }

    tokens[i].type = EOF;
    tokens[i].value = NULL;

    currentToken = tokens;
}

Token *next()
{
    return currentToken++;
}

Token *current()
{
    return currentToken;
}

void push()
{
    currentToken--;
}

void end()
{
    free(tokens);
}

int main()
{
    init("1 + 2");
    Token *t = next();
    while (t->type != EOF)
    {
        printf("%d %s\n", t->type, t->value);
        t = next();
    }
    end();
    return 0;
}


