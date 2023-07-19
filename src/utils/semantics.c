#include "semantics.h"

SLLT* build_identl(DT* i){

    SLLT * new;
    SYB* syb = create_symbol(i->children[0]->children[0]->value, UNKNOWNTYPE, 1);
    new = insert_symbol_on_list_end(NULL, syb);
    if(i->cnum == 3){
        new = combine_lists(new, build_identl(i->children[2])); 
    }

    return new;
}

SLLT* build_argl(DT* i){

    SLLT* new;
    SYB* syb;
    if (i->cnum == 1){
        syb = create_symbol(i->children[0]->children[1]->children[0]->value, i->children[0]->children[0]->type, 1);
        new = insert_symbol_on_list_end(NULL, syb);
    }else if(i->cnum == 3){
        syb = create_symbol(i->children[2]->children[1]->children[0]->value, i->children[2]->children[0]->type, 1);
        new = insert_symbol_on_list_end(NULL, syb);
        new = combine_lists(build_argl(i->children[0]), new);
    }

    return new;

}

void yyerror(ST* st_vars, ST* st_func, char* msg, ...){

    va_list ap;
    va_start(ap, msg);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");

    error_count++;

}