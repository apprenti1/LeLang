//!  gcc -o build/test/ChainedListTest libs/ChainedList/test/ChainedListTest.c libs/ChainedList/src/ChainedList.c -Ilibs/ChainedList/include && ./build/test/ChainedListTest


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "ChainedList.h"

void test_listInit()
{
    List *list = listInit();
    assert(list != NULL);
    assert(list->head == NULL);
    assert(list->size == 0);
    ListFree(list);
    printf("\033[32mOK\033[0m | test_listInit\n");
}

void test_listAdd()
{
    List *list = listInit();
    void *item;

    item = malloc(sizeof(int));
    *(int *)item = 1;
    listAdd(list, INT, item);

    item = malloc(sizeof(float));
    *(float *)item = 2.0;
    listAdd(list, FLOAT, item);

    item = malloc(sizeof(double));
    *(double *)item = 3.0;
    listAdd(list, DOUBLE, item);

    item = malloc(1);
    *(char *)item = 'a';
    listAdd(list, CHAR, item);

    item = malloc(sizeof(short));
    *(short *)item = 5;
    listAdd(list, SHORT, item);

    item = malloc(sizeof(long));
    *(long *)item = 6;
    listAdd(list, LONG, item);

    item = malloc(sizeof(char *));
    *(char **)item = "string";
    listAdd(list, STRING, item);

    assert(list->size == 7);
    ListFree(list);
    printf("\033[32mOK\033[0m | test_listAdd\n");
}

void test_listGet()
{
    List *list = listInit();
    void *item;
    item = malloc(sizeof(int));
    *(int *)item = 1;
    listAdd(list, INT, item);
    item = malloc(sizeof(float));
    *(float *)item = 2.0;
    listAdd(list, FLOAT, item);
    item = malloc(sizeof(double));
    *(double *)item = 3.0;
    listAdd(list, DOUBLE, item);
    item = malloc(1);
    *(char *)item = 'a';
    listAdd(list, CHAR, item);
    item = malloc(sizeof(short));
    *(short *)item = 5;
    listAdd(list, SHORT, item);
    item = malloc(sizeof(long));
    *(long *)item = 6;
    listAdd(list, LONG, item);
    item = malloc(sizeof(char *));
    *(char **)item = "string";
    listAdd(list, STRING, item);
    assert(listGetInt(list, 0) == 1);
    assert(listGetFloat(list, 1) == 2.0);
    assert(listGetDouble(list, 2) == 3.0);
    assert(listGetChar(list, 3) == 'a');
    assert(listGetShort(list, 4) == 5);
    assert(listGetLong(list, 5) == 6);
    assert(strcmp(listGetString(list, 6), "string") == 0);
    ListFree(list);
    printf("\033[32mOK\033[0m | test_listGet\n");
}

void test_listDelete()
{
    List *list = listInit();
    void *item;
    item = malloc(sizeof(int));
    *(int *)item = 1;
    listAdd(list, INT, item);
    item = malloc(sizeof(float));
    *(float *)item = 2.0;
    listAdd(list, FLOAT, item);
    item = malloc(sizeof(double));
    *(double *)item = 3.0;
    listAdd(list, DOUBLE, item);
    item = malloc(1);
    *(char *)item = 'a';
    listAdd(list, CHAR, item);
    item = malloc(sizeof(short));
    *(short *)item = 5;
    listAdd(list, SHORT, item);
    item = malloc(sizeof(long));
    *(long *)item = 6;
    listAdd(list, LONG, item);
    item = malloc(sizeof(char *));
    *(char **)item = "string";
    listAdd(list, STRING, item);
    assert(list->size == 7);
    listDelete(list, 0);
    assert(list->size == 6);
    listDelete(list, 0);
    assert(list->size == 5);
    listDelete(list, 0);
    assert(list->size == 4);
    listDelete(list, 0);
    assert(list->size == 3);
    listDelete(list, 0);
    assert(list->size == 2);
    listDelete(list, 0);
    assert(list->size == 1);
    listDelete(list, 0);
    assert(list->size == 0);
    ListFree(list);
    printf("\033[32mOK\033[0m | test_listDelete\n");
}

void cest_chainedchainedStringInit()
{
    ChainedString *string = chainedStringInit();
    assert(string != NULL);
    assert(string->head == NULL);
    assert(string->size == 0);
    chainedStringFree(string);
    printf("\033[32mOK\033[0m | cest_chainedchainedStringInit\n");
}

void test_chainedStringAppend()
{
    ChainedString *string = chainedStringInit();
    chainedStringAppend(string, 'a');
    chainedStringAppend(string, 'b');
    chainedStringAppend(string, 'c');
    chainedStringAppend(string, 'd');
    chainedStringAppend(string, 'e');
    chainedStringAppend(string, 'f');
    chainedStringAppend(string, 'g');
    chainedStringAppend(string, 'h');
    assert(string->size == 8);
    chainedStringFree(string);
    printf("\033[32mOK\033[0m | test_chainedStringAppend\n");
}

void test_chainedStringGet()
{
    ChainedString *string = chainedStringInit();
    chainedStringAppend(string, 'a');
    chainedStringAppend(string, 'b');
    chainedStringAppend(string, 'c');
    chainedStringAppend(string, 'd');
    chainedStringAppend(string, 'e');
    chainedStringAppend(string, 'f');
    chainedStringAppend(string, 'g');
    chainedStringAppend(string, 'h');
    assert(chainedStringGet(*string, 0) == 'a');
    assert(chainedStringGet(*string, 1) == 'b');
    assert(chainedStringGet(*string, 2) == 'c');
    assert(chainedStringGet(*string, 3) == 'd');
    assert(chainedStringGet(*string, 4) == 'e');
    assert(chainedStringGet(*string, 5) == 'f');
    assert(chainedStringGet(*string, 6) == 'g');
    assert(chainedStringGet(*string, 7) == 'h');
    chainedStringFree(string);
    printf("\033[32mOK\033[0m | test_chainedStringGet\n");
}

void test_chainedstringDelete()
{
    ChainedString *string = chainedStringInit();
    chainedStringAppend(string, 'a');
    chainedStringAppend(string, 'b');
    chainedStringAppend(string, 'c');
    chainedStringAppend(string, 'd');
    chainedStringAppend(string, 'e');
    chainedStringAppend(string, 'f');
    chainedStringAppend(string, 'g');
    chainedStringAppend(string, 'h');
    assert(string->size == 8);
    chainedstringdelete(string, 0);
    assert(string->size == 7);
    chainedstringdelete(string, 0);
    assert(string->size == 6);
    chainedstringdelete(string, 0);
    assert(string->size == 5);
    chainedstringdelete(string, 0);
    assert(string->size == 4);
    chainedstringdelete(string, 0);
    assert(string->size == 3);
    chainedstringdelete(string, 0);
    assert(string->size == 2);
    chainedstringdelete(string, 0);
    assert(string->size == 1);
    chainedstringdelete(string, 0);
    assert(string->size == 0);
    chainedStringFree(string);
    printf("\033[32mOK\033[0m | test_chainedstringDelete\n");
}

int main()
{
    test_listInit();
    test_listAdd();
    test_listGet();
    test_listDelete();
    cest_chainedchainedStringInit();
    test_chainedStringAppend();
    test_chainedStringGet();
    test_chainedstringDelete();
    return 0;
}

