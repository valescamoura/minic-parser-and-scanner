#include "symbol-table.h"

enum typevalue {
    CHARTYPE = 0,
    INTTYPE,
    FLOATTYPE,
    ERRORTYPE
};

void insert_on_collision_list(ST* table, SYB* symbol, unsigned long index);

SYB* create_symbol(char* name, int type){

    SYB* newSymbol = (SYB*) malloc(sizeof(SYB));

    newSymbol->name = (char*) malloc(sizeof(char)*strlen(name) + 1);
    newSymbol->type = type;

    strcpy(newSymbol->name, name);

    return newSymbol;

}

ST* create_symbol_table(int size){

    ST* newST = (ST*) malloc(sizeof(ST));

    newST->items = (SYB**) malloc(sizeof(SYB*)*size);
    newST->collision_lists = (SLLT**) malloc(sizeof(SLLT*)*size);
    newST->size = size;
    newST->count = 0;

    for(int i = 0; i < size; i++){
        newST->items[i] = NULL;
        newST->collision_lists[i] = NULL;
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

void insert_on_collision_list(ST* table, SYB* symbol, unsigned long index){
    
    SLLT* head = table->collision_lists[index];

    if (!head){
        head = create_list_item(symbol, NULL);
        table->collision_lists[index] = head;
    }else{
        table->collision_lists[index] = insert_symbol_on_list(head, symbol);
    }

}

/* 
Try to insert a symbol in the symbol table.
Return -1 if the table is full
Return 1 if the symbol already is in the table
Return 0 if the insertion was sucessfull 
*/
int insert_symbol(ST* table, char* name, int type){

    SYB* newSymbol = create_symbol(name, type);

    unsigned long index = compute_hash(name, table->size);

    SYB* currentSymbol = table->items[index];

    if (!currentSymbol){

        if(table->count == table->size){

            printf("Too many symbols, symbol table is full");
            free_symbol(newSymbol);
            return -1;

        }

        table->items[index] = newSymbol;
        table->count++;

    }else{

        if (strcmp(currentSymbol->name, name) == 0){
            return 1;
        } else {
            SYB* collided_symbol = search_for_symbol_on_list(table->collision_lists[index], newSymbol->name);
            if (collided_symbol != NULL) return 1;
            insert_on_collision_list(table, newSymbol, index);
        }

    }

    return 0;

}

SYB* search_for_symbol(ST* table, char* name){

    unsigned long index = compute_hash(name, table->size);
    SYB* symbol = table->items[index];
    SLLT* head = table->collision_lists[index];

    if(symbol != NULL){
        if (strcmp(symbol->name, name) == 0) return symbol;
        if(!head) return NULL;
        return search_for_symbol_on_list(head, name);
    }

    return NULL;

}

void free_symbol(SYB* symbol){
    free(symbol->name);
    free(symbol);
}

void free_symbol_table(ST* table){

    for(int i = 0; i < table->size; i++){
        if(table->items[i] != NULL){
            free_symbol(table->items[i]);
        }
        if(table->collision_lists[i] != NULL){
            free_SLLT(table->collision_lists[i]);
        }
    }
    free(table->items);
    free(table->collision_lists);
    free(table);

}

void printST(ST* table){

    printf("\n\nSymbol Table\n\n");
    printf("Types: {%d} CHAR, {%d} INT, {%d} FLOAT\n", CHARTYPE, INTTYPE, FLOATTYPE);
    printf("-----------------------------------------\n");

    for (int i = 0; i < table->size; i++){
        if (table->items[i]){
            printf("[%d] {%d} %s\n", i, table->items[i]->type, table->items[i]->name);
        }
        SLLT* head = table->collision_lists[i];
        int j = 0;
        for (head; head != NULL; head = head->next){
            printf("\t[%d.%d] {%d} %s\n", i, j, head->symbol->type, head->symbol->name);
            j++;
        }
    }

    printf("-----------------------------------------\n");
    printf("\n");

}

SLLT* create_list_item(SYB* symbol, SLLT* next){

    SLLT* new_item = (SLLT*) malloc (sizeof(SLLT));

    new_item->symbol = symbol;
    new_item->next = next;

    return new_item;

}

SLLT* insert_symbol_on_list(SLLT* head, SYB* symbol){

    SLLT* new_head = create_list_item(symbol, head);

    return new_head;

}

SYB* search_for_symbol_on_list(SLLT* head, char* name){

    SLLT* temp = head;

    while (temp){
        
        if (strcmp(temp->symbol->name, name) == 0){
            return temp->symbol;
        }

        temp = temp->next;

    }
    
    return NULL;

}

void free_SLLT(SLLT* head){

    SLLT* temp = head;

    while (temp){

        temp = head;        
        head = head->next;
        free_symbol(temp->symbol);
        free(temp);
        
    }
    

}