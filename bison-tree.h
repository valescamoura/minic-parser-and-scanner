#ifndef bisontree_h
#define bisontree_h


#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dt{
    char* value;
    int cnum;
    struct dt **children;
}DT;

DT* createTree(char* value, int cnum, ...);
void printTree(DT* t);
void yyerror(char* msg);
DT* strToTree(char* value, int length);

#endif