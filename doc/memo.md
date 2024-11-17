dans un calcul, liste des priorités dans l'expression

calcul des fonctions

calcul des parentheses

calcul des variables

calcul des multiplications

calcul des divisions

calcul des additions

calcul des soustractions

une expression est soit l'interieur d'une parenthese, soit l'argument d'une fonction ou le calcul d'une variable

doivent etre réalisé en premier, la compréhension du stockage d'une variable et donc une fonction de stockage de variable avec des listes dynamiques

si on rencontre un type suivi d'une lettre ou d'un _ puis d'une suite d'alphanumérique ou _ puis d'un = recuperer toute la suite jusqu'au \n et calculer puis utiliser la fonction de stockage des variables pour stocker le resultat avec le nom de la variable qui lui est associé

type de variable: ent = int, dec = float, car = char, longdec = double

### Ce que le parser va faire :

Le parser va analyser les tokens générés par le lexer et former une structure logique qui représente l'expression mathématique ou l'instruction donnée. Pour ton exemple, on va se concentrer sur des opérations simples comme l’addition, la multiplication, et peut-être un peu de stockage de variables. Pour garder ça clair et efficace, on va construire un **AST** ( *Abstract Syntax Tree* ) pour exécuter les calculs.

### Étapes principales :

1. **Lexer** : Découpe le code en tokens (ça, on l’a déjà).
2. **Parser** : Crée un arbre syntaxique en suivant les priorités d’opérations (`+`, `*`, etc.).
3. **Évaluation** : Parcourt l’arbre pour effectuer les calculs.

### Structure du Code

On va créer un parser avec des fonctions pour analyser et exécuter des expressions mathématiques. Voici un exemple pour commencer.

#### Structures pour le Parser

Pour simplifier, on va définir un AST simple avec des nœuds d'opérations et des nœuds de valeurs.

regarder le premier tocken, si il commence par type, nom, definition, cela signivie que c'est un stockage de variable, stocker la variable et effacer les tockens de la liste
si la variable n'est pas directement définie par un nombre ou une chaine de charactere recuperer les tocken qui la définisse et les envoyer dans le parser qui va recuperer les tocken, verrifier si il ya des noms de variable ou fonctions et les remplacer puis verrifier si il y a des oppérateurs / ou +, (si il y en a verrifier si les tockens qui l'entourent sont bien de type number ou float, si c'est le cas faire le calcul et supprimer les deux numbers, definir le tocken actuel comme float et y enregistrer la valeur)verrifier si il y a des opperateurs + ou - ( si il y en a verrifier si les tockens qui l'entoure sont des numbers ou des float, faire le calcul, si l'un des tocken qui l'entoure est un float la sortie sera un float sinon un int)


```
int
|\
| \
a  (
|  |\\\
|  | \\\_______ 
|  |  \\___    \
|  |   |   \    \
=  var num float string
```
