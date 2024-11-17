
#include "ChainedList.h"
#include "Lexer.h"
#include "Var.h"

// Fonction pour évaluer une opération mathématique
double evaluateOperation(double a, double b, char operator)
{
    switch (operator)
    {
    case '*':
        return a * b;
    case '/':
        return b != 0 ? a / b : 0; // Protection contre division par zéro
    case '+':
        return a + b;
    case '-':
        return a - b;
    default:
        return 0;
    }
}

/*
*    cette fonction permet de parser une expression
*    [
*    "TOKEN_KEYWORD"=>"int",
*    "TOKEN_IDENTIFIER"=>"a",
*    "TOKEN_DEFINITION"=>"=",
*    "TOKEN_NUMBER"=>"33",
*    "TOKEN_OPERATOR"=>"+",
*    "TOKEN_NUMBER"=>"2"
*    ]
     --> verrifie si il y a des variables stocké identifiable, si oui les remplace dans les tockens
     --> verrifie si il y a des * ou / , si oui fait les calculs et les remplace dans les tockens
     --> verrifie si il y a des + ou - , si oui fait les calculs et les remplace dans les tockens
     ..> verrifie si il y a une execution de fonction primaire si oui execute
    todo verrifie si il y a une definition de variable, si oui
    todo verrifier qu'il ne reste qu'une valeur unique dans la définition (int,float, string) si oui
    todo stocker la variable
*/

void parseExpression(List *tokens, int endIndex, VarList *varList)
{
    Token *currentToken;

    for (int i = 0; i < endIndex; i++)
    {
        Token *token = listGet(tokens, i);
        if (token && token->type == TOKEN_IDENTIFIER && (!listGet(tokens, i + 1) || ((Token *)listGet(tokens, i + 1))->type != TOCKEN_DEFINITION))
        {

            VarNode *var = varGetNode(varList, token->value);
            if (var)
            {
                printf("Found variable:\n");
                if (var->type == FLOAT)
                {
                    token->type = TOKEN_FLOAT;
                    sprintf(token->value, "%f", *(float *)(var->item));
                }
                else if (var->type == INT)
                {
                    token->type = TOKEN_NUMBER;
                    sprintf(token->value, "%d", *(int *)(var->item));
                }
            }
        }
    }

    for (int i = 0; i < endIndex; i++)
    {
        Token *token = listGet(tokens, i);
        if (token && token->type == TOKEN_OPERATOR &&
            (strcmp(token->value, "*") == 0 || strcmp(token->value, "/") == 0))
        {

            Token *prevToken = listGet(tokens, i - 1);
            Token *nextToken = listGet(tokens, i + 1);

            if (
                prevToken &&
                nextToken &&
                (prevToken->type == TOKEN_NUMBER || prevToken->type == TOKEN_FLOAT) &&
                (nextToken->type == TOKEN_NUMBER || nextToken->type == TOKEN_FLOAT))
            {
                double a = atof(prevToken->value);
                double b = atof(nextToken->value);
                double result = evaluateOperation(a, b, token->value[0]);
                token->type = TOKEN_FLOAT;
                sprintf(token->value, "%f", result);
                prevToken->type = TOKEN_UNKNOWN;
                nextToken->type = TOKEN_UNKNOWN;
                endIndex -= 2;
                i -= 2;
            }
        }
    }

    for (int i = 0; i < endIndex; i++)
    {
        Token *token = listGet(tokens, i);
        if (token && token->type == TOKEN_OPERATOR &&
            (strcmp(token->value, "+") == 0 || strcmp(token->value, "-") == 0))
        {

            Token *prevToken = listGet(tokens, i - 1);
            Token *nextToken = listGet(tokens, i + 1);

            if (
                prevToken &&
                nextToken &&
                (prevToken->type == TOKEN_NUMBER || prevToken->type == TOKEN_FLOAT) &&
                (nextToken->type == TOKEN_NUMBER || nextToken->type == TOKEN_FLOAT))
            {
                double a = atof(prevToken->value);
                double b = atof(nextToken->value);
                double result = evaluateOperation(a, b, token->value[0]);
                if (prevToken->type == TOKEN_FLOAT || nextToken->type == TOKEN_FLOAT)
                {
                    token->type = TOKEN_FLOAT;
                    sprintf(token->value, "%f", result);
                }
                else
                {
                    token->type = TOKEN_NUMBER;
                    sprintf(token->value, "%i", (int)result);
                }

                listDelete(tokens, i + 1);
                listDelete(tokens, i - 1);
                endIndex -= 2;
                i -= 2;
            }
        }
    }

    // functions
    for (int i = 0; i < endIndex; i++)
    {
        if (((Token *)listGet(tokens, i))->type == TOKEN_IDENTIFIER)
        {

            if (strcmp(((Token *)listGet(tokens, i))->value, "printf") == 0 && ((Token *)listGet(tokens, i + 1))->type == TOKEN_PARENTHESIS_OPEN)
            {
                int j = i + 2;
                while (j < endIndex && ((Token *)listGet(tokens, j))->type != TOKEN_PARENTHESIS_CLOSE)
                {
                    printf("%s", ((Token *)listGet(tokens, j))->value);
                    listDelete(tokens, j);
                    endIndex--;
                }
                // printf("\n");
                listDelete(tokens, i);
                listDelete(tokens, i);
                listDelete(tokens, i);
                endIndex -= 3;
            }
            if (strcmp(((Token *)listGet(tokens, i))->value, "scanf") == 0 && ((Token *)listGet(tokens, i + 1))->type == TOKEN_PARENTHESIS_OPEN)
            {
                int j = i + 2;
                while (j < endIndex && ((Token *)listGet(tokens, j))->type != TOKEN_PARENTHESIS_CLOSE)
                {
                    Token *t = (Token *)listGet(tokens, j);
                    if (t->type == TOKEN_IDENTIFIER)
                    {
                    }
                }
            }
        }
    }

    // redef variable
    for (int i = 0; i < endIndex; i++)
    {
        if (((Token *)listGet(tokens, i))->type == TOKEN_IDENTIFIER && 
        ((Token *)listGet(tokens, i + 1))->type == TOCKEN_DEFINITION && 
        (!((Token *)listGet(tokens, i - 1)) ||
        ((Token *)listGet(tokens, i - 1))->type != TOKEN_KEYWORD )
        )
        {
            printf("Found variable:\n");
            VarNode *var = varGetNode(varList, ((Token *)listGet(tokens, i))->value);
            var->item = ((void*)((Token *)listGet(tokens, i + 2))->value);
           listDelete(tokens, i);
           listDelete(tokens, i);
           listDelete(tokens, i);
           endIndex -= 3;
        }
    }

    // Add variables
    for (int i = 0; i < endIndex; i++)
    {
        if (((Token *)listGet(tokens, i))->type == TOKEN_KEYWORD && ((Token *)listGet(tokens, i + 1))->type == TOKEN_IDENTIFIER && ((Token *)listGet(tokens, i + 2))->type == TOCKEN_DEFINITION)
        {
            int j = i + 3;
            while (j < endIndex && ((Token *)listGet(tokens, j))->type != TOKEN_DELIMITER)
            {
                j++;
            }
            if (j == i + 4)
            {
                if (strcmp(((Token *)listGet(tokens, i))->value, "int") == 0)
                {
                    varAddInt(varList, ((Token *)listGet(tokens, i + 1))->value, atoi(((Token *)listGet(tokens, i + 3))->value));
                }
                else if (strcmp(((Token *)listGet(tokens, i))->value, "float") == 0)
                {
                    varAddFloat(varList, ((Token *)listGet(tokens, i + 1))->value, atof(((Token *)listGet(tokens, i + 3))->value));
                }
            }

            // printf("!!!!!!%i|%i\n", i, j);
        }
    }

    //
    for (int i = 0; i < endIndex; i++)
    {
        if (((Token *)listGet(tokens, i + 1))->type == TOKEN_IDENTIFIER && ((Token *)listGet(tokens, i + 2))->type == TOCKEN_DEFINITION)
        {
            int j = i + 3;
            while (j < endIndex && ((Token *)listGet(tokens, j))->type != TOKEN_DELIMITER)
            {
                j++;
            }
            if (j == i + 4)
            {
            }
        }
    }

    for (int i = 0; i < endIndex; i++)
    {
        Token *token = listGet(tokens, i);
        if (token && token->type == TOKEN_UNKNOWN)
        {
            continue;
        }
    }
}

/*
 * le but de cette fonction sera de séparer les tockens par groupe d'expressions
 * et les envoyer dans la fonction parseexpression
 *
 * par exemple l'expression suivante : "int a = 33+2; printf('%i|%f', 6*8, a);a==7;"
 * une fois lexé sera :
 * [
 * "TOKEN_KEYWORD"=>"int",
 * "TOKEN_IDENTIFIER"=>"a",
 * "TOKEN_DEFINITION"=>"=",
 * "TOKEN_NUMBER"=>"33",
 * "TOKEN_OPERATOR"=>"+",
 * "TOKEN_NUMBER"=>"2",
 * "TOKEN_DELIMITER"=>";",
 * "TOKEN_IDENTIFIER"=>"printf",
 * "TOKEN_DELIMITER"=>",",
 * "TOKEN_NUMBER"=>"6",
 * "TOKEN_OPERATOR"=>"*",
 * "TOKEN_NUMBER"=>"8",
 * "TOKEN_DELIMITER"=>",",
 * "TOKEN_IDENTIFIER"=>"a",
 * "TOKEN_DELIMITER"=>"==",
 * "TOKEN_NUMBER"=>"7",
 * "TOKEN_DELIMITER"=>";"
 * ]
 *
 * et une fois passé par cette fonction sera envoyé à parseExpression :
 * [
 * "TOKEN_KEYWORD"=>"int",
 * "TOKEN_IDENTIFIER"=>"a",
 * "TOKEN_DEFINITION"=>"=",
 * "TOKEN_NUMBER"=>"33",
 * "TOKEN_OPERATOR"=>"+",
 * "TOKEN_NUMBER"=>"2"
 * ]
 *
 */
void parseTokens(List *tokens, VarList *varList)
{

    if (tokens == NULL || tokens->head == NULL)
    {
        return;
    }

    ListNode *current = tokens->head;
    int i = 0;
    int lastExpressionIndex = 0;
    while (current != NULL)
    {
        Token *token = (Token *)current->item;
        if (token != NULL && token->value != NULL)
        {
            if (token->type == TOKEN_DELIMITER && strcmp(token->value, ";") == 0)
            {

                parseExpression(tokens, lastExpressionIndex, varList);
                printf("expression parsed\n");
            }
            lastExpressionIndex = i + 1;
        }
        current = current->next;
        i++;
    }

    // S'il reste des tokens non parsés après le dernier point-virgule
    if (lastExpressionIndex < tokens->size)
    {
        parseExpression(tokens, lastExpressionIndex, varList);
    }
}
