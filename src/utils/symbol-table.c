#include "symbol-table.h"

void insert_on_collision_list(ST* table, SYB* symbol, unsigned long index);

SYB* create_symbol(char* name, int type){

    SYB* newSymbol = (SYB*) malloc(sizeof(SYB));

    newSymbol->name = (char*) malloc(sizeof(char)*strlen(name) + 1);
    newSymbol->type = type;
    newSymbol->arglist = NULL;

    strcpy(newSymbol->name, name);

    return newSymbol;

}

ST* create_symbol_table(int size){

    ST* newST = (ST*) malloc(sizeof(ST));

    newST->symbols = (SYB**) malloc(sizeof(SYB*)*size);
    newST->collision_lists = (SLLT**) malloc(sizeof(SLLT*)*size);
    newST->size = size;
    newST->count = 0;

    for(int i = 0; i < size; i++){
        newST->symbols[i] = NULL;
        newST->collision_lists[i] = NULL;
    }

    return newST;

}

int insert_func_arg(ST* table, char* funcname, char* argname, int argtype){

    SYB* symbol = search_for_symbol(table, funcname);

    if (!symbol) return -1;

    SYB* look = search_for_symbol_on_list(symbol->arglist, argname);

    if (look) return 1;

    SYB* newarg = create_symbol(argname, argtype);

    symbol->arglist = insert_symbol_on_list_end(symbol->arglist, newarg);

    return 0;

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

    SYB* currentSymbol = table->symbols[index];

    if (!currentSymbol){

        if(table->count == table->size){

            printf("Too many symbols, symbol table is full");
            free_symbol(newSymbol);
            return -1;

        }

        table->symbols[index] = newSymbol;
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

char* get_type_name(int type){

    switch (type)
    {
    case CHARTYPE:
        return "char";
        break;
    case INTTYPE:
        return "int";
        break;
    case FLOATTYPE:
        return "float";
        break;
    case ERRORTYPE:
        return "error";
        break;
    default:
        return "unknown";
        break;
    }

}

SYB* search_for_symbol(ST* table, char* name){

    unsigned long index = compute_hash(name, table->size);
    SYB* symbol = table->symbols[index];
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
    free_SLLT(symbol->arglist);
    free(symbol);
}

void free_symbol_table(ST* table){

    for(int i = 0; i < table->size; i++){
        if(table->symbols[i] != NULL){
            free_symbol(table->symbols[i]);
        }
        if(table->collision_lists[i] != NULL){
            free_SLLT(table->collision_lists[i]);
        }
    }
    free(table->symbols);
    free(table->collision_lists);
    free(table);

}

void printST(ST* table){

    printf("\n\nSymbol Table\n\n");
    printf("Types: {%d} CHAR, {%d} INT, {%d} FLOAT\n", CHARTYPE, INTTYPE, FLOATTYPE);
    printf("-----------------------------------------\n");

    for (int i = 0; i < table->size; i++){
        if (table->symbols[i]){
            printf("[%d] {%d} %s\n", i, table->symbols[i]->type, table->symbols[i]->name);
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

SLLT* combine_lists(SLLT* head, SLLT* tail){

    if(head == NULL) return tail;

    SLLT* aux = head;

    while (aux->next != NULL)
    {
        aux = aux->next;
    }
    
    aux->next = tail;

    return head;

}

SLLT* insert_symbol_on_list_end(SLLT* head, SYB* symbol){

    if (!head) {
        SLLT* new = create_list_item(symbol, NULL);
        return new;
    }else if(head->next == NULL){
        head->next = create_list_item(symbol, NULL);
        return head;
    }

    SLLT* temp = head;

    while (temp->next->next){
        temp = temp->next;
    }
    
    temp->next = create_list_item(symbol, NULL);

    return head;

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

void print_list(SLLT* list){

    if (!list) return;

    SLLT* aux = list;

    while (aux != NULL)
    {
        printf("->%s", aux->symbol->name);
        aux = aux->next;
    }
    printf("\n");
    

}
