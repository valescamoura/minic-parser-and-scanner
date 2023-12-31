#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol-table.h"

#ifndef bisontree_h
#define bisontree_h

typedef struct dt{
    char* value;
    int cnum;
    int type;
    struct dt **children;
    int id; // Identificador único para cada nó
}DT;

extern int yylineno;
extern int error_count;

DT* createTree(char* value, int cnum, ...);
void freeTree(DT* node);
void generateTreeFile(DT* root);
void printTree(DT* t);
DT* strToTree(char* value, int length);
char* mergeStr(char* s, int n);

#endif
