#ifndef PARSER_H
#define PARSER_H

#include "ChainedList.h"
#include "Lexer.h"
#include "Var.h"

/**
 * @brief Parse une expression spécifique dans la liste des tokens
 * 
 * Cette fonction analyse une sous-séquence de tokens représentant une expression
 * et effectue les opérations suivantes:
 * - Vérifie et remplace les variables stockées identifiables
 * - Effectue les calculs de multiplication et division
 * - Exécute les fonctions primaires
 * - Gère les définitions de variables
 * - Vérifie la validité des types (int, float, string)
 * 
 * @param tokens La liste complète des tokens
 * @param i L'index de début de l'expression à parser
 */
void parseExpression(List *tokens, int endIndex, VarList *varList);
/**
 * @brief Sépare et analyse les tokens par groupes d'expressions
 * 
 * Cette fonction:
 * - Parcourt la liste complète des tokens
 * - Identifie les délimiteurs d'expressions (;)
 * - Envoie chaque groupe de tokens à parseExpression
 * 
 * Exemple d'entrée:
 * "int a = 33+2; printf('%i|%f', 6*8, a); a==7;"
 * 
 * @param tokens La liste des tokens à analyser
 */
void parseTokens(List *tokens, VarList *varList);

#endif // PARSER_H