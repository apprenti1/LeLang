#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Var.h"



typedef struct ListNode
{
    void *item;
    VarType type;
    struct ListNode *next;
} ListNode;

typedef struct
{
    ListNode *head;
    int size;
} List;

typedef struct
{
    ListNode *head;
    int size;
} ChainedString;



void ListNodeFree(ListNode *node)
{
    free(node->item);
    free(node);
}

void ListFree(List *list)
{
    ListNode *current = list->head;
    ListNode *next;
    while (current != NULL)
    {
        next = current->next;
        ListNodeFree(current);
        // printf("Listnode free\n");
        current = next;
    }
    free(list);
}

void chainedStringFree(ChainedString *string)
{
    ListNode *current = string->head;
    ListNode *next;
    while (current != NULL)
    {
        next = current->next;
        ListNodeFree(current);
        current = next;
    }
    free(string);
}

List *listInit()
{
    List *list = malloc(sizeof(List));
    if (list == NULL)
    {
        printf("Erreur : Pas assez de mémoire disponible\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

ChainedString *chainedStringInit()
{
    ChainedString *list = malloc(sizeof(ChainedString));
    if (list == NULL)
    {
        printf("Erreur : Pas assez de mémoire disponible\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}


void listAdd(List *list, const VarType type, void *item)
{

    ListNode *new;

    new = malloc(sizeof(ListNode));
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
    if (list == NULL)
    {
        printf("Erreur : La liste est NULL\n");
        return;
    }



    new->item = item;
    new->type = type;
    new->next = NULL;

    if (list->head == NULL)
    {
        list->head = new;
    }
    else
    {
        ListNode *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new;
    }
    list->size++;
}

void chainedStringAppend(ChainedString *string, char character) {
    if (string == NULL) {
        printf("Erreur : La chaîne est NULL\n");
        return;
    }

    ListNode *new_node = malloc(sizeof(ListNode));
    if (new_node == NULL) {
        printf("Erreur : Pas assez de mémoire disponible\n");
        return;
    }

    char *value = malloc(sizeof(char));
    if (value == NULL) {
        printf("Erreur : Pas assez de mémoire disponible pour le caractère\n");
        free(new_node);
        return;
    }

    *value = character;
    new_node->item = value;
    new_node->type = CHAR;
    new_node->next = NULL;

    if (string->head == NULL) {
        string->head = new_node;
    } else {
        ListNode *current = string->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    string->size++;
}


void *listGet(List *list, int id)
{
    if (list == NULL)
    {
        printf("Erreur : La liste est NULL\n");
        return NULL;
    }
    ListNode *current = list->head;
    int currentid = 0;
    while (current != NULL)
    {
        if (currentid == id)
        {
            return current->item;
        }
        currentid++;
        current = current->next;
    }
    return NULL;
}

char chainedStringGet(ChainedString string, int id)
{
    ListNode *current = string.head;
    int currentid = 0;
    while (current != NULL)
    {
        if (currentid == id)
        {
            return *(char *)(current->item);
        }
        currentid++;
        current = current->next;
    }
    return '\0';
}

void listDelete(List *list, int id)
{
    if (list == NULL)
    {
        printf("Erreur : La liste est NULL\n");
        return;
    }
    ListNode *current = list->head;
    ListNode *previous = NULL;
    int currentid = 0;
    while (current != NULL)
    {
        if (currentid == id)
        {
            if (previous == NULL)
            {
                list->head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            ListNodeFree(current);
            list->size--;
            return;
        }
        previous = current;
        current = current->next;
        currentid++;
    }
}

void chainedstringdelete(ChainedString *string, int id)
{
    ListNode *current = string->head;
    ListNode *previous = NULL;
    int currentid = 0;
    while (current != NULL)
    {
        if (currentid == id)
        {
            if (previous == NULL)
            {
                string->head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            ListNodeFree(current);
            string->size--;
            return;
        }
        previous = current;
        current = current->next;
        currentid++;
    }
}

void listPrint(List *list)
{
    ListNode *current = list->head;
    int index = 0;
    while (current != NULL)
    {
        printf("| %i -> ", index++);
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
            case CUSTOM:
                printf("CUSTOM_VALUE | ");
                break;
        }
        current = current->next;
    }
    printf("\n");
}

char* chainedStringRender(ChainedString string)
{
    char *str = malloc(string.size + 1);
    int i = 0;
    ListNode *current = string.head;
    while (current != NULL)
    {
        str[i] = chainedStringGet(string, i);
        current = current->next;
        i++;
    }
    str[i] = '\0';
    return str;
}

void listAddChar(List *list, char item)
{
    char *value = malloc(1);
    *value = item;
    listAdd(list, CHAR, value);
}
void listAddShort(List *list, short item)
{
    short *value = malloc(sizeof(short));
    *value = item;
    listAdd(list, SHORT, value);
}
void listAddInt(List *list, int item)
{
    int *value = malloc(sizeof(int));
    *value = item;
    listAdd(list, INT, value);
}
void listAddLong(List *list, long item)
{
    long *value = malloc(sizeof(long));
    *value = item;
    listAdd(list, LONG, value);
}
void listAddFloat(List *list, float item)
{
    float *value = malloc(sizeof(float));
    *value = item;
    listAdd(list, FLOAT, value);
}
void listAddDouble(List *list, double item)
{
    double *value = malloc(sizeof(double));
    *value = item;
    listAdd(list, DOUBLE, value);
}

char listGetChar(List *list, int id)
{
    return *(char *)(listGet(list, id));
}
short listGetShort(List *list, int id)
{
    return *(short *)(listGet(list, id));
}
int listGetInt(List *list, int id)
{
    return *(int *)(listGet(list, id));
}
long listGetLong(List *list, int id)
{
    return *(long *)(listGet(list, id));
}
float listGetFloat(List *list, int id)
{
    return *(float *)(listGet(list, id));
}
double listGetDouble(List *list, int id)
{
    return *(double *)(listGet(list, id));
}
char *listGetString(List *list, int id)
{
    return *(char **)(listGet(list, id));
}









