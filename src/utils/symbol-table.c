#include "symbol-table.h"

#define TABLE_SIZE 5000

SYB* createSymbol(char* name, int type){

    SYB* newSymbol = (SYB*) malloc(sizeof(SYB));

    newSymbol->name = (char*) malloc(sizeof(char)*strlen(name) + 1);
    newSymbol->type = type;

    strcpy(newSymbol->name, name);

    return newSymbol;

}

ST* createSymbolTable(int size){

    ST* newST = (ST*) malloc(sizeof(ST));

    newST->items = (SYB**) malloc(sizeof(SYB*)*size);
    newST->size = size;
    newST->count = 0;

    for(int i = 0; i < size; i++){
        newST->items[i] = NULL;
    }

    return newST;

}

unsigned long compute_hash(char* name, long hashsize){
    unsigned long sum = 0;
    int size = strlen(name);

    for (int i = 0; i < size; i++){
        sum += name[i];
    }

    return sum % hashsize;
}

void insertSymbol(ST* table, char* name, int type){

}

void freeSymbol(SYB* symbol){
    free(symbol->name);
    free(symbol->type);
    free(symbol);
}

void freeSymbolTable(ST* table){

    for(int i = 0; i < table->size; i++){
        if(table->items[i] != NULL){
            free(table->items[i]);
        }
    }
    free(table->items);
    free(table);

}

void printST(ST* table){

    printf("Symbol Table\n\n");

    for (int i = 0; i < table->size; i++){
        if (table->items[i]){
            printf("[%d] %s %s\n", i, table->items[i]->type, table->items[i]->name);
        }
    }

    printf("\n");

}