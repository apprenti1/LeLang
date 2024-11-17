1. ### le ti loup 🐺* — *Aujourd’hui à 20:59

   [https://nospy.notion.site/Projet-Cr-ation-d-un-Interpr-teur-de-Langage-de-Programmation-e890d1624945429eafc4ce91cbcce315?pvs=4](https://nospy.notion.site/Projet-Cr-ation-d-un-Interpr-teur-de-Langage-de-Programmation-e890d1624945429eafc4ce91cbcce315?pvs=4 "https://nospy.notion.site/Projet-Cr-ation-d-un-Interpr-teur-de-Langage-de-Programmation-e890d1624945429eafc4ce91cbcce315?pvs=4")

   Noé's Notion on Notion

   [Projet : Création d&#39;un Interpréteur de Langage de Programmation | N...](https://nospy.notion.site/Projet-Cr-ation-d-un-Interpr-teur-de-Langage-de-Programmation-e890d1624945429eafc4ce91cbcce315?pvs=4)

   Objectif Général
2. ![ ](https://cdn.discordapp.com/avatars/279012381965680640/5a7b0440a55b996873bcf80337f1fc35.webp?size=96)### La souris éclair* — *Aujourd’hui à 20:59

   Squeak
3. ![ ](https://cdn.discordapp.com/avatars/391710712373837826/a5c0c2012c85de983dd0f4a3a9b9d7cc.webp?size=96)### le ti loup 🐺* — *Aujourd’hui à 21:33

   dis si t là je veux bien que tu verrifie un truc
   j'ai écrit ça pour organiser mes idées

   <pre><div class="codeContainer_f8f345"><code class="scrollbarGhostHairline_c858ce scrollbar_c858ce hljs c">/*
   le but de cette fonction sera de séparer les tockens par groupe d'expressions 
   et les envoyer dans la fonction parseexpression

   par exemple l'expression suivante : "int a = 33+2; printf('%i|%f', 6*8, a);a==7;"
   une fois lexé sera : 
   [
   "TOKEN_KEYWORD"=>"int",
   "TOKEN_IDENTIFIER"=>"a",
   "TOKEN_DEFINITION"=>"=",
   "TOKEN_NUMBER"=>"33",
   "TOKEN_OPERATOR"=>"+",
   "TOKEN_NUMBER"=>"2",
   "TOKEN_DELIMITER"=>";",
   "TOKEN_IDENTIFIER"=>"printf",
   "TOKEN_DELIMITER"=>",",
   "TOKEN_NUMBER"=>"6",
   "TOKEN_OPERATOR"=>"*",
   "TOKEN_NUMBER"=>"8",
   "TOKEN_DELIMITER"=>",",
   "TOKEN_IDENTIFIER"=>"a",
   "TOKEN_DELIMITER"=>"==",
   "TOKEN_NUMBER"=>"7",
   "TOKEN_DELIMITER"=>";"
   ]

   et une fois passé par cette fonction sera envoyé à parseExpression :
   [
   "TOKEN_KEYWORD"=>"int",
   "TOKEN_IDENTIFIER"=>"a",
   "TOKEN_DEFINITION"=>"=",
   "TOKEN_NUMBER"=>"33",
   "TOKEN_OPERATOR"=>"+",
   "TOKEN_NUMBER"=>"2"
   ]

   */
   void parseTokens(List *tokens) {

   }


   /*
       cette fonction permet de parser une expression
       [
       "TOKEN_KEYWORD"=>"int",
       "TOKEN_IDENTIFIER"=>"a",
       "TOKEN_DEFINITION"=>"=",
       "TOKEN_NUMBER"=>"33",
       "TOKEN_OPERATOR"=>"+",
       "TOKEN_NUMBER"=>"2"
       ]
       verrifie si il y a des variables stocké identifiable, si oui les remplace dans les tockens
       verrifie si il y a des * ou / , si oui fait les calculs et les remplace dans les tockens
       verrifie si il y a une execution de fonction primaire si oui execute
       verrifie si il y a une definition de variable, si oui 
       verrifier qu'il ne reste qu'une valeur unique dans la définition (int,float, string) si oui
       stocker la variable
   */
   void parseExpression(List *tokens) {

   }</code></div></pre>

   tu peux me dire ce que tu en pense si ce que je compte faire tiens la route ?
4. ![ ](https://cdn.discordapp.com/avatars/279012381965680640/5a7b0440a55b996873bcf80337f1fc35.webp?size=96)### La souris éclair* — *Aujourd’hui à 21:33

   Oui, je te dis cela :🙂:

   :💕:

   1
5. ![ ](https://cdn.discordapp.com/avatars/391710712373837826/a5c0c2012c85de983dd0f4a3a9b9d7cc.webp?size=96)### le ti loup 🐺* — *Aujourd’hui à 21:34

   j'ai pas mis les parentheses, je verrai plus tard pour ça
6. ![ ](https://cdn.discordapp.com/avatars/279012381965680640/5a7b0440a55b996873bcf80337f1fc35.webp?size=96)### La souris éclair* — *Aujourd’hui à 21:38

   Pourquoi `parseExpression` ne renvoi pas une liste d'instruction à exécuté pas à pas ?
7. ![ ](https://cdn.discordapp.com/avatars/391710712373837826/a5c0c2012c85de983dd0f4a3a9b9d7cc.webp?size=96)### le ti loup 🐺* — *Aujourd’hui à 21:41

   c'est pas en quelques sorte ce que fait parseTokens? parseexpression s'occupe des verrifications interne a l'expression/à l'instruction et executer , les différentes demarches
8. *[* 21:41*]*tu voyais les choses comment toi?
9. ![ ](https://cdn.discordapp.com/avatars/279012381965680640/5a7b0440a55b996873bcf80337f1fc35.webp?size=96)### La souris éclair* — *Aujourd’hui à 21:48

   Tel que ça retourne une liste d'instructions
   "L'instruction" en tant que tel serait de différent type, l'une d'entre elle serait les Expressions représentaient par des arbres syntaxiques à résoudre
10. ![ ](https://cdn.discordapp.com/avatars/391710712373837826/a5c0c2012c85de983dd0f4a3a9b9d7cc.webp?size=96)### le ti loup 🐺* — *Aujourd’hui à 21:51

    tu peux essayer de me faire un exemple avec "int a = 33+2; printf('%i|%f', 6*8, a);" juste pour voir concretement les chauses s'agenceraient, un exemple du déroulé, pas du programme, car c'est assez obscur, je sais pas trop comment m'y prendre
11. *[* 21:52*]*on a jamais vraiment etudié ce genre de truc
12. ![ ](https://cdn.discordapp.com/avatars/391710712373837826/a5c0c2012c85de983dd0f4a3a9b9d7cc.webp?size=96)### le ti loup 🐺* — *Aujourd’hui à 22:00

    jvai demander a chat gpt pour voir ce qu'il me dit
13. ![ ](https://cdn.discordapp.com/avatars/279012381965680640/5a7b0440a55b996873bcf80337f1fc35.webp?size=96)### La souris éclair* — *Aujourd’hui à 22:01

    Voilà l'étape 1

    <pre><div class="codeContainer_f8f345"><code class="scrollbarGhostHairline_c858ce scrollbar_c858ce hljs">let lexer: list<Token> = lexer("int a = 33+2; printf('%i|%f', 6*8, a);");
    // List<EnumType::Int, Variable(Value="a"), EnumOperator::Equal, Number(Value=33), EnumExpressionOperator, EnumExpressionOperator::Add Number(Value=2), CommonPoint, EnumBeginFunctionPrintF, String(Value='%i|%f'), Number(Value=6), EnumExpressionOperator::Mul, Number(Value=8), Variable(Value="a"), EnumEndFunction, CommonPoint></code></div></pre>

    **(modifié)**
14. *[* 22:01*]*Je ne peux pas écrire aussi vite que ChatGPT, laisse moi du temps :c

   :👍:

   1

1. ![ ](https://cdn.discordapp.com/avatars/391710712373837826/a5c0c2012c85de983dd0f4a3a9b9d7cc.webp?size=96)### le ti loup 🐺* — *Aujourd’hui à 22:02

   hihi t'inquiete pas petite souris, merci beaucoup :😘: c'est dur d'etre tt seul sur un truc quand on sait pas trop ou on va
2. *[* 22:03*]*tu me sauve bien
3. ![ ](https://cdn.discordapp.com/avatars/279012381965680640/5a7b0440a55b996873bcf80337f1fc35.webp?size=96)### La souris éclair* — *Aujourd’hui à 22:08

   L'étape 2 c'est le parseur, qui retourne une liste d'instructions

   <pre><div class="codeContainer_f8f345"><code class="scrollbarGhostHairline_c858ce scrollbar_c858ce hljs">let parser = parser(&lexer)
   // List<[
     Instruction::Assigniation<EnumType::Int, Variable(Value="a"), Expression<EnumOperator::Equal, Number(Value=33), EnumExpressionOperator::Add Number(Value=2)>>,
     Instruction::FunctionCall<EnumFunctionPrintF, String(Value='%i|%f'), Expression<Number(Value=6), EnumExpressionOperator::Mul, Number(Value=8)>, StateGetVariable("a")
   ]></code></div></pre>

   Celles-ci sont de deux types :
   1- soit ça demandera d'assigner une valeur dans une state, par exemple le résulta d'une expression dans une variable "a",
   2- soit ça demandera d'appeller une fonction

   L'étape 3 peut être un Ast pour simplifier, par exemple transformer les Expression en des Valeurs (des Numbers)

   <pre><div class="codeContainer_f8f345"><code class="scrollbarGhostHairline_c858ce scrollbar_c858ce hljs">// List<[
     Instruction::Assigniation<EnumType::Int, Variable(Value="a"), Expression<EnumOperator::Equal, Number(Value=33), EnumExpressionOperator::Equal Number(Value=35)>>,
     Instruction::FunctionCall<EnumFunctionPrintF, String(Value='%i|%f'), Number(Value=48), StateGetVariable("a")
   ]></code></div></pre>

   Remarque que le StateGetVariable "a" n'est pas retiré
   L'étape 4 executera cette liste d'instructions **(modifié)**
4. *[* 22:10*]*Donc `a=35; printf("%i|%f", a->35);`

   :💕:

   1

1. ![ ](https://cdn.discordapp.com/avatars/391710712373837826/a5c0c2012c85de983dd0f4a3a9b9d7cc.webp?size=96)### le ti loup 🐺* — *Aujourd’hui à 22:28

   je crois avoir compris l'idée, en gros plutot que d'executer directement je crée des sous instructions, pour les passer aux différents modules ou différentes fonctions pour dissocier les calculs, du stockage de variable, de la gestion des fonctions et je passe par l'ast

   :👍:

   1
2. *[* 22:29*]*merci beaucoup petite souris
