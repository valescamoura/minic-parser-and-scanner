#include "bison-tree.h"

void printTreeAux(DT* t, int tabn);

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

void printTree(DT* t){

    if (t != NULL){
        printTreeAux(t, 0);
    }

}

void printTreeAux(DT* t, int tabn){

    int div = t->cnum/2; 
    int i;

    for (i=t->cnum-1; i >= t->cnum-div; i--){
        printTreeAux(t->children[i], tabn+1);
    }

    for (i = 0; i < tabn; i++){
        printf("\t");
    }
    printf("%s\n", t->value);

    if (t->cnum % 2 != 0){
        i = div;
    }else{
        i = div-1;
    }

    for (i; i >= 0; i--){
        printTreeAux(t->children[i], tabn+1);
    }

}

DT* strToTree(char* value, int length){

    char *s = (char*) malloc(sizeof(char)*length);
    strcpy(s, value);
    return createTree(s, 0);

}

void yyerror(char* msg){
    printf("%s\n", msg);
}