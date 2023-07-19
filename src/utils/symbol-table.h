#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef symboltable_h
#define symboltable_h

enum typevalue {
    CHARTYPE = 0,
    INTTYPE,
    FLOATTYPE,
    ERRORTYPE,
    UNKNOWNTYPE
};

typedef struct SimpleLinkedList SLLT;
typedef struct symbol SYB;

struct SimpleLinkedList{

    SYB* symbol;
    SLLT* next;

};

typedef struct symbol{

    char* name;
    int type;
    SLLT* arglist;

}SYB;

typedef struct symbolTable{

    SYB** symbols;
    SLLT** collision_lists;
    int size;
    int count;

}ST;


SYB* create_symbol(char* name, int type);
ST* create_symbol_table(int size);
int insert_symbol(ST* table, char* name, int type);
int insert_func_arg(ST* table, char* funcname, char* argname, int argtype);
unsigned long compute_hash(char* name, long hashsize); 
SYB* search_for_symbol(ST* table, char* name);
void free_symbol(SYB* symbol);
void free_symbol_table(ST* table);
void printST(ST* table);

char * get_type_name(int type);

SLLT* create_list_item(SYB* symbol, SLLT* next);
SLLT* insert_symbol_on_list(SLLT* head, SYB* symbol);
SLLT* combine_lists(SLLT* head, SLLT* tail);
SLLT* insert_symbol_on_list_end(SLLT* head, SYB* symbol);
SYB* search_for_symbol_on_list(SLLT* head, char* name);
void print_list(SLLT* list);
void free_SLLT(SLLT* head);

#endif