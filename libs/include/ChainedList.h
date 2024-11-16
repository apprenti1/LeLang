#ifndef CHAINEDLIST_H
#define CHAINEDLIST_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



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
} ListType;

typedef struct ListNode
{
    void *item;
    ListType type;
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

void ListNodeFree(ListNode *node);
void ListFree(List *list);
void chainedStringFree(ChainedString *string);

List *listInit();
ChainedString *chainedStringInit();

void listAdd(List *list, const ListType type, void *item);
void chainedStringAppend(ChainedString *string, char character);

void *listGet(List *list, int id);
char chainedStringGet(ChainedString string, int id);

void listDelete(List *list, int id);
void chainedstringdelete(ChainedString *string, int id);

void listPrint(List *list);
char* chainedStringRender(ChainedString string);

void listAddChar(List *list, char item);
void listAddShort(List *list, short item);
void listAddInt(List *list, int item);
void listAddLong(List *list, long item);
void listAddFloat(List *list, float item);
void listAddDouble(List *list, double item);

char listGetChar(List *list, int id);
short listGetShort(List *list, int id);
int listGetInt(List *list, int id);
long listGetLong(List *list, int id);
float listGetFloat(List *list, int id);
double listGetDouble(List *list, int id);
char *listGetString(List *list, int id);

#endif
