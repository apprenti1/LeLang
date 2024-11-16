#ifndef Var_h
#define Var_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum
{
    INT,
    FLOAT,
    DOUBLE,
    LONGDOUBLE,
    CHAR,
    SHORT,
    LONG
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

void varNodeFree(VarNode *node);
void varListFree(VarList *list);
VarList *varListInit();
void varAdd(VarList *list, const VarType type, const char *name, void *item);
void *varGet(VarList *list, const char *name);
void varDelete(VarList *list, const char *name);
void varListPrint(VarList *list);

void varAddChar(VarList *list, const char *name, char item);
void varAddShort(VarList *list, const char *name, short item);
void varAddInt(VarList *list, const char *name, int item);
void varAddLong(VarList *list, const char *name, long item);
void varAddFloat(VarList *list, const char *name, float item);
void varAddDouble(VarList *list, const char *name, double item);
void varAddLongDouble(VarList *list, const char *name, long double item);

char varGetChar(VarList *list, const char *name);
short varGetShort(VarList *list, const char *name);
int varGetInt(VarList *list, const char *name);
long varGetLong(VarList *list, const char *name);
float varGetFloat(VarList *list, const char *name);
double varGetDouble(VarList *list, const char *name);
long double varGetLongDouble(VarList *list, const char *name);

#endif

