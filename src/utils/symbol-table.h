#ifndef symboltable_h
#define symboltable_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct symbol{

    char* name;
    int type;

}SYB;

typedef struct symbolTable{

    SYB** items;
    int size;
    int count;

}ST;

SYB* createSymbol(char* name, int type);
ST* createSymbolTable(int size);
void insertSymbol(ST* table, char* name, int type);
unsigned long compute_hash(char* name, long hashsize); 
SYB* searchForSymbol(ST* table, char* name);
void freeSymbol(SYB* symbol);
void freeSymbolTable(ST* table);
void printST(ST* table);

#endif