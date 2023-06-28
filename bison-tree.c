#include "bison-tree.h"

DT* createTree(char* value, int cnum, ...){
    va_list valist;

    DT* t = (DT*) malloc(sizeof(DT));
    t->value = value;
    t->cnum = cnum;
    t->children = NULL;
    if (cnum > 0){
        t->children = (DT**) malloc(sizeof(DT*)*cnum);
    }
    
    va_start(valist, cnum);

    for (int i=0; i < cnum; i++){
        t->children[i] = va_arg(valist, DT*);
    }

    va_end(valist);
    
    return t;

}