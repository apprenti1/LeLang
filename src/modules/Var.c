#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum
{
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    SHORT,
    LONG,
    STRING,
    CUSTOM
} VarType;

typedef struct VarNode
{
    void *item;
    VarType type;
    char *name;
    struct VarNode *next;
} VarNode;

typedef struct
{
    VarNode *head;
    int size;
} VarList;





void varNodeFree(VarNode *node)
{
    free(node->name);
    free(node->item);
    free(node);
}

void varListFree(VarList *list)
{
    VarNode *current = list->head;
    VarNode *next;
    while (current != NULL)
    {
        next = current->next;
        varNodeFree(current);
        // printf("varnode free\n");
        current = next;
    }
    free(list);
}



VarList *varListInit()
{
    VarList *list = malloc(sizeof(VarList));
    if (list == NULL)
    {
        printf("Erreur : Pas assez de mémoire disponible\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void varAdd(VarList *list, const VarType type, const char *name, void *item)
{

    VarNode *new;

    new = malloc(sizeof(VarNode));
    new->name = malloc(strlen(name)+1);
    if (new->name == NULL)
    {
        free(new);
        printf("Erreur : Pas assez de mémoire disponible\n");
        return;
    }
    if (new == NULL)
    {
        printf("Erreur : Pas assez de mémoire disponible\n");
        return;
    }
    if (item == NULL)
    {
        printf("Erreur : L'item est NULL\n");
        return;
    }
    if (strlen(name) == 0)
    {
        printf("Erreur : Le nom est vide\n");
        return;
    }
    if (list == NULL)
    {
        printf("Erreur : La liste est NULL\n");
        return;
    }



    new->item = item;
    new->type = type;
    strcpy(new->name, name);
    new->next = NULL;

    if (list->head == NULL)
    {
        list->head = new;
    }
    else
    {
        VarNode *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new;
    }
    list->size++;
}
VarNode *varGetNode(VarList *list, const char *name)
{
    if (list == NULL)
    {
        printf("Erreur : La liste est NULL\n");
        return NULL;
    }
    if (strlen(name) == 0)
    {
        printf("Erreur : Le nom est vide\n");
        return NULL;
    }
    VarNode *current = list->head;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
void *varGet(VarList *list, const char *name)
{
    if (varGetNode(list, name) != NULL)
    {
        return varGetNode(list, name)->item;
    }
    
    return NULL;
}

void varDelete(VarList *list, const char *name)
{
    if (list == NULL)
    {
        printf("Erreur : La liste est NULL\n");
        return;
    }
    if (strlen(name) == 0)
    {
        printf("Erreur : Le nom est vide\n");
        return;
    }
    VarNode *current = list->head;
    VarNode *previous = NULL;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (previous == NULL)
            {
                list->head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            varNodeFree(current);
            list->size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}


void varListPrint(VarList *list)
{
    VarNode *current = list->head;
    while (current != NULL)
    {
        printf("| %s -> ", current->name);
        switch (current->type){
            case CHAR:
                printf("%c | ", *(char *)(current->item));
                break;
            case SHORT:
                printf("%hd | ", *(short *)(current->item));
                break;
            case INT:
                printf("%d | ", *(int *)(current->item));
                break;
            case LONG:
                printf("%ld | ", *(long *)(current->item));
                break;
            case FLOAT:
                printf("%f | ", *(float *)(current->item));
                break;
            case DOUBLE:
                printf("%lf | ", *(double *)(current->item));
                break;
        }
        current = current->next;
    }
    printf("\n");
}
void varAddChar(VarList *list, const char *name, char item)
{
    char *value = malloc(1);
    *value = item;
    varAdd(list, CHAR, name, value);
}

void varAddShort(VarList *list, const char *name, short item)
{
    short *value = malloc(sizeof(short));
    *value = item;
    varAdd(list, SHORT, name, value);
}
void varAddInt(VarList *list, const char *name, int item)
{
    int *value = malloc(sizeof(int));
    *value = item;
    varAdd(list, INT, name, value);
}
void varAddLong(VarList *list, const char *name, long item)
{
    long *value = malloc(sizeof(long));
    *value = item;
    varAdd(list, LONG, name, value);
}
void varAddFloat(VarList *list, const char *name, float item)
{
    float *value = malloc(sizeof(float));
    *value = item;
    varAdd(list, FLOAT, name, value);
}
void varAddDouble(VarList *list, const char *name, double item)
{
    double *value = malloc(sizeof(double));
    *value = item;
    varAdd(list, DOUBLE, name, value);
}

char varGetChar(VarList *list, const char *name)
{
    return *(char *)(varGet(list, name));
}
short varGetShort(VarList *list, const char *name)
{
    return *(short *)(varGet(list, name));
}
int varGetInt(VarList *list, const char *name)
{
    return *(int *)(varGet(list, name));
}

long varGetLong(VarList *list, const char *name)
{
    return *(long *)(varGet(list, name));
}
float varGetFloat(VarList *list, const char *name)
{
    return *(float *)(varGet(list, name));
}
double varGetDouble(VarList *list, const char *name)
{
    return *(double *)(varGet(list, name));
}


