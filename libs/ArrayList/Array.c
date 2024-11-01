#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    void *item;
    char type[20];
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    int size;
} arraylist;

/**
 * @brief Crée une liste d'éléments
 * @return Un pointeur sur la liste créée. NULL si la mémoire est insuffisante.
 */
arraylist *arrayInit()
{
    arraylist *list = malloc(sizeof(arraylist));
    if (list == NULL)
    {
        printf("Erreur : Pas assez de mémoire disponible\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}



void arrayAdd(arraylist *list, void *item, const char *type)
{
    if (item == NULL)
    {
        printf("Erreur : L'item est NULL\n");
        return;
    }
    if (strlen(type) > 20)
    {
        printf("Erreur : La description du type dépasse 20 caractères\n");
        return;
    }
    Node *new = malloc(sizeof(Node));
    if (new == NULL)
    {
        printf("Erreur : Pas assez de mémoire disponible\n");
        return;
    }
    new->item = item;
    strncpy(new->type, type, 20);
    new->next = NULL;
    if (list->head == NULL)
    {
        list->head = new;
    }
    else
    {
        Node *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new;
    }
    list->size++;
}

void arrayDelete(arraylist *list, int id)
{
    if (id < 0 || id >= list->size)
    {
        printf("Index inexistant");
        return;
    }

    Node *current = list->head;
    Node *previous = NULL;

    for (int i = 0; i < id; i++)
    {
        previous = current;
        current = current->next;
    }

    if (previous == NULL)
    {
        list->head = current->next;
    }
    else
    {
        previous->next = current->next;
    }
    free(current->item);
    free(current);
    list->size--;
}

void *arrayGet(arraylist *list, int id)
{
    if (id < 0 || id >= list->size)
    {
        printf("Index inexistant");
        return NULL;
    }

    Node *current = list->head;
    for (int i = 0; i < id; i++)
    {
        current = current->next;
    }

    return current->item;
}

void arrayFree(arraylist *list)
{
    Node *current = list->head;
    Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->item);
        free(current);
        current = next;
    }

    free(list);
}

void arrayPrint(arraylist *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        if (strcmp(current->type, "char") == 0)
        {
            printf("%c | ", *(char *)(current->item));
        }
        else if (strcmp(current->type, "short") == 0)
        {
            printf("%hd | ", *(short *)(current->item));
        }
        else if (strcmp(current->type, "int") == 0)
        {
            printf("%d | ", *(int *)(current->item));
        }
        else if (strcmp(current->type, "long") == 0)
        {
            printf("%ld | ", *(long *)(current->item));
        }
        else if (strcmp(current->type, "float") == 0)
        {
            printf("%f | ", *(float *)(current->item));
        }
        else if (strcmp(current->type, "double") == 0)
        {
            printf("%lf | ", *(double *)(current->item));
        }
        else if (strcmp(current->type, "long double") == 0)
        {
            printf("%Lf | ", *(long double *)(current->item));
        }
        else
        {
            printf("type inconnu | ");
        }

        current = current->next;
    }
    printf(" \n");
}




void arrayAddChar(arraylist *list, char item)
{
    char *value = malloc(1);
    *value = item;
    arrayAdd(list, value, "char");
}
void arrayAddShort(arraylist *list, short item)
{
    short *value = malloc(sizeof(short));
    *value = item;
    arrayAdd(list, value, "short");
}
void arrayAddInt(arraylist *list, int item)
{
    int *value = malloc(sizeof(int));
    *value = item;
    arrayAdd(list, value, "int");
}
void arrayAddLong(arraylist *list, long item)
{
    long *value = malloc(sizeof(long));
    *value = item;
    arrayAdd(list, value, "long");
}
void arrayAddFloat(arraylist *list, float item)
{
    float *value = malloc(sizeof(float));
    *value = item;
    arrayAdd(list, value, "float");
}
void arrayAddDouble(arraylist *list, double item)
{
    double *value = malloc(sizeof(double));
    *value = item;
    arrayAdd(list, value, "double");
}
void arrayAddLongDouble(arraylist *list, long double item)
{
    long double *value = malloc(sizeof(long double));
    *value = item;
    arrayAdd(list, value, "long double");
}



char arrayGetChar(arraylist *list, int id)
{
    return *(char *)(arrayGet(list, id));
}
short arrayGetShort(arraylist *list, int id)
{
    return *(short *)(arrayGet(list, id));
}
int arrayGetInt(arraylist *list, int id)
{
    return *(int *)(arrayGet(list, id));
}
long arrayGetLong(arraylist *list, int id)
{
    return *(long *)(arrayGet(list, id));
}
float arrayGetFloat(arraylist *list, int id)
{
    return *(float *)(arrayGet(list, id));
}
double arrayGetDouble(arraylist *list, int id)
{
    return *(double *)(arrayGet(list, id));
}
long double arrayGetLongDouble(arraylist *list, int id)
{
    return *(long double *)(arrayGet(list, id));
}

int main()
{
    arraylist *list = arrayInit();

    char *value = malloc(1);
    *value = 'l';
    arrayAdd(list, value, "charssssssssssssssssssss");

    arrayAddChar(list, 'v');
    arrayAddChar(list, 'v');
    arrayAddChar(list, 'q');
    arrayAddChar(list, 'q');
    arrayAddChar(list, 'q');
    arrayAddChar(list, 'q');
    arrayPrint(list);
    printf("%c\n", arrayGetChar(list, 1));

    arrayDelete(list, 1);
    arrayPrint(list);

    arrayFree(list);
    return 0;
}