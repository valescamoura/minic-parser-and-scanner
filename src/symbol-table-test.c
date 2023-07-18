#include "utils/symbol-table.h"

int main(void){

    ST* st = create_symbol_table(5000);

    printf("%d\n", insert_symbol(st, "abcd", 1)); 
    printf("%d\n", insert_symbol(st, "dcba", 1)); 
    printf("%d\n", insert_symbol(st, "dbca", 1));
    printf("%d\n", insert_symbol(st, "acbd", 1));  

    SYB* symbol =  search_for_symbol(st, "ksks");

    if(symbol){
        printf("%s, %d\n", symbol->name, symbol->type);
    }else{
        printf("symbol not found\n");
    }
    

    printST(st);

}