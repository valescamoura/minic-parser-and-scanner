#ifndef bisontree_h
#define bisontree_h


#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol-table.h"

typedef struct dt{
    char* value;
    int cnum;
    int type;
    struct dt **children;
    int id; // Identificador único para cada nó
}DT;

DT* createTree(char* value, int cnum, ...);
void freeTree(DT* node);
void generateTreeFile(DT* root);
void printTree(DT* t);
void yyerror(char* msg);
DT* strToTree(char* value, int length);
void turnLoopsIntoGoto(DT* root);

#endif
