#include "semantics.h"

SLLT* build_identl(DT* i){

    SLLT * new;
    SYB* syb = create_symbol(i->children[0]->children[0]->value, UNKNOWNTYPE);
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
        syb = create_symbol(i->children[0]->children[1]->children[0]->value, i->children[0]->children[0]->type);
        new = insert_symbol_on_list_end(NULL, syb);
    }else if(i->cnum == 3){
        syb = create_symbol(i->children[2]->children[1]->children[0]->value, i->children[2]->children[0]->type);
        new = insert_symbol_on_list_end(NULL, syb);
        new = combine_lists(build_argl(i->children[0]), new);
    }

    return new;

}

int check_operation_type(int type1, int type2, char operation, int lineno){

    if (type1 == CHARTYPE && type2 == CHARTYPE){
        return CHARTYPE;
    }
    if (type1 == CHARTYPE || type2 == CHARTYPE){
        printf("Error: invalid operation %c at line %d between types %s and %s\n", operation, lineno, get_type_name(type1), get_type_name(type2));
        return ERRORTYPE;
    }

    return (type1 > type2) ? type1 : type2;

}

SYB* check_definition(ST* st, char* name){

    SYB* symb;

    symb = search_for_symbol(st, name);

    return symb;

}

void set_unknowns(ST* st, int type){
    
    for (int i = 0; i < st->size; i++){

        if (st->symbols[i] != NULL){
            if (st->symbols[i]->type == UNKNOWNTYPE) st->symbols[i]->type = type;
            SLLT* head = st->collision_lists[i];
            if (head != NULL){
                for(head; head != NULL; head = head->next){
                    if (head->symbol->type == UNKNOWNTYPE) head->symbol->type = type;
                }
            }
        }

    }

}

void yyerror(ST* st_vars, ST* st_func, const char* msg, ...){

    va_list ap;
    va_start(ap, msg);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");

    error_count++;

}