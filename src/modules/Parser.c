
#include "ChainedList.h"
#include "Lexer.h"
#include "Var.h"

double evaluateOperation(double a, double b, char operator)
{
    switch (operator)
    {
    case '*':
        return a * b;
    case '/':
        return b != 0 ? a / b : 0;
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
    todo verrifie si il y a des * ou / , si oui fait les calculs et les remplace dans les tockens
    todo verrifie si il y a une execution de fonction primaire si oui execute
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
        if (token && token->type == TOKEN_IDENTIFIER)
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
                listDelete(tokens, i + 1);
                listDelete(tokens, i - 1);
                endIndex -= 2;
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
            }
        }
    }
/
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
                lastExpressionIndex = i + 1;
            }
        }
        current = current->next;
        i++;
    }
    if (lastExpressionIndex < tokens->size)
    {
        parseExpression(tokens, lastExpressionIndex, varList);
    }
}
