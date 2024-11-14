#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct arraylist arraylist;

arraylist *arrayInit();
void arrayAdd(arraylist *list, void *item, const char *type);
void arrayDelete(arraylist *list, int id);
void arrayPrint(arraylist *list);
void arrayFree(arraylist *list);

void arrayAddInt(arraylist *list, int item);
void arrayAddShort(arraylist *list, short item);
void arrayAddLong(arraylist *list, long item);
void arrayAddFloat(arraylist *list, float item);
void arrayAddDouble(arraylist *list, double item);
void arrayAddLongDouble(arraylist *list, long double item);
void arrayAddChar(arraylist *list, char item);

int arrayGetInt(arraylist *list, int id);
short arrayGetShort(arraylist *list, int id);
long arrayGetLong(arraylist *list, int id);
float arrayGetFloat(arraylist *list, int id);
double arrayGetDouble(arraylist *list, int id);
long double arrayGetLongDouble(arraylist *list, int id);
char arrayGetChar(arraylist *list, int id);

#endif
