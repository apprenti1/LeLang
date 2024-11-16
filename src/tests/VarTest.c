#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Var.h"

void test_varListInit()
{
    VarList *list = varListInit();
    assert(list != NULL);
    assert(list->head == NULL);
    assert(list->size == 0);
    varListFree(list);
    printf("\033[1;32m|  \033[0m\033[32mOK\033[0m | test_varListInit\n");
}

void test_varAdd()
{
    VarList *list = varListInit();
    void *value = malloc(sizeof(int));
    *(int *)value = 1;
    varAdd(list, INT, "int", value);
    value = malloc(sizeof(float));
    *(float *)value = 1.0;
    varAdd(list, FLOAT, "float", value);
    value = malloc(sizeof(double));
    *(double *)value = 1.0;
    varAdd(list, DOUBLE, "double", value);
    value = malloc(sizeof(long double));
    *(long double *)value = 1.0;
    varAdd(list, LONGDOUBLE, "longdouble", value);
    value = malloc(sizeof(char));
    *(char *)value = 'c';
    varAdd(list, CHAR, "char", value);
    value = malloc(sizeof(short));
    *(short *)value = 1;
    varAdd(list, SHORT, "short", value);
    value = malloc(sizeof(long));
    *(long *)value = 1;
    varAdd(list, LONG, "long", value);

    assert(list->size == 7);
    varListFree(list);
    printf("\033[1;32m|  \033[0m\033[32mOK\033[0m | test_varAdd\n");
}

void test_varGet()
{
    VarList *list = varListInit();
    void *value = malloc(sizeof(int));
    *(int *)value = 1;
    varAdd(list, INT, "int", value);
    value = malloc(sizeof(float));
    *(float *)value = 1.0;
    varAdd(list, FLOAT, "float", value);
    value = malloc(sizeof(double));
    *(double *)value = 1.0;
    varAdd(list, DOUBLE, "double", value);
    value = malloc(sizeof(long double));
    *(long double *)value = 1.0;
    varAdd(list, LONGDOUBLE, "longdouble", value);
    value = malloc(sizeof(char));
    *(char *)value = 'c';
    varAdd(list, CHAR, "char", value);
    value = malloc(sizeof(short));
    *(short *)value = 1;
    varAdd(list, SHORT, "short", value);
    value = malloc(sizeof(long));
    *(long *)value = 1;
    varAdd(list, LONG, "long", value);
    assert(varGetInt(list, "int") == 1);
    assert(varGetFloat(list, "float") == 1.0);
    assert(varGetDouble(list, "double") == 1.0);
    assert(varGetLongDouble(list, "longdouble") == 1.0);
    assert(varGetChar(list, "char") == 'c');
    assert(varGetShort(list, "short") == 1);
    assert(varGetLong(list, "long") == 1);
    varListFree(list);
    printf("\033[1;32m|  \033[0m\033[32mOK\033[0m | test_varGet\n");
}

void test_varDelete()
{
    VarList *list = varListInit();
    void *value = malloc(sizeof(int));
    *(int *)value = 1;
    varAdd(list, INT, "int", value);
    value = malloc(sizeof(float));
    *(float *)value = 1.0;
    varAdd(list, FLOAT, "float", value);
    value = malloc(sizeof(double));
    *(double *)value = 1.0;
    varAdd(list, DOUBLE, "double", value);
    value = malloc(sizeof(long double));
    *(long double *)value = 1.0;
    varAdd(list, LONGDOUBLE, "longdouble", value);
    value = malloc(sizeof(char));
    *(char *)value = 'c';
    varAdd(list, CHAR, "char", value);
    value = malloc(sizeof(short));
    *(short *)value = 1;
    varAdd(list, SHORT, "short", value);
    value = malloc(sizeof(long));
    *(long *)value = 1;
    varAdd(list, LONG, "long", value);
    assert(list->size == 7);
    varDelete(list, "int");
    assert(list->size == 6);
    varDelete(list, "float");
    assert(list->size == 5);
    varDelete(list, "double");
    assert(list->size == 4);
    varDelete(list, "longdouble");
    assert(list->size == 3);
    varDelete(list, "char");
    assert(list->size == 2);
    varDelete(list, "short");
    assert(list->size == 1);
    varDelete(list, "long");
    assert(list->size == 0);
    varListFree(list);
    printf("\033[1;32m|  \033[0m\033[32mOK\033[0m | test_varDelete\n");
}

int main()
{
    test_varListInit();
    test_varAdd();
    test_varGet();
    test_varDelete();
    return 0;
}

