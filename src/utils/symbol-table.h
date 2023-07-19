#ifndef symboltable_h
#define symboltable_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum typevalue {
    CHARTYPE = 0,
    INTTYPE,
    FLOATTYPE,
    ERRORTYPE,
    UNKNOWNTYPE
};

typedef struct symbol{

    char* name;
    int type;

}SYB;

typedef struct SimpleLinkedList SLLT;

struct SimpleLinkedList{

    SYB* symbol;
    SLLT* next;

};

typedef struct symbolTable{

    SYB** items;
    SLLT** collision_lists;
    int size;
    int count;

}ST;



SYB* create_symbol(char* name, int type);
ST* create_symbol_table(int size);
int insert_symbol(ST* table, char* name, int type);
void set_unknowns(ST* st, int type);
unsigned long compute_hash(char* name, long hashsize); 
int check_operation_type(int type1, int type2, char operation, int lineno);
char * get_type_name(int type);
SYB* search_for_symbol(ST* table, char* name);
void free_symbol(SYB* symbol);
void free_symbol_table(ST* table);
void printST(ST* table);

SLLT* create_list_item(SYB* symbol, SLLT* next);
SLLT* insert_symbol_on_list(SLLT* head, SYB* symbol);
SYB* search_for_symbol_on_list(SLLT* head, char* name);
void free_SLLT(SLLT* head);

#endif