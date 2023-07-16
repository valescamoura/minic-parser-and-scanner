#include "bison-tree.h"

int nodeIdCounter = 0; // Contador global para atribuir identificadores únicos
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

void generateDot(FILE* fp, DT* node) {
    if (node == NULL)
        return;

    fprintf(fp, "\"%d\" [label=\"%s\"];\n", node->id, node->value);

    for (int i = 0; i < node->cnum; i++) {
        fprintf(fp, "\"%d\" -> \"%d\";\n", node->id, node->children[i]->id);
        generateDot(fp, node->children[i]);
    }
}

void assignIds(DT* node) {
    if (node == NULL)
        return;

    node->id = nodeIdCounter++;
    
    for (int i = 0; i < node->cnum; i++) {
        assignIds(node->children[i]);
    }
}

void generateDotFile(DT* root, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo de saída.\n");
        return;
    }

    fprintf(fp, "digraph Tree {\n");
    assignIds(root);
    generateDot(fp, root);
    fprintf(fp, "}\n");

    fclose(fp);
}

void freeTree(DT* node) {
    if (node == NULL)
        return;

    for (int i = 0; i < node->cnum; i++) {
        freeTree(node->children[i]);
    }

    free(node->children);
    free(node->value);
    free(node);
}

void turnLoopsIntoGoto(DT* root) {}

void generateTreeFile(DT* root) {
    turnLoopsIntoGoto(root);
    generateDotFile(root, "tree.dot");
    // Chame o Graphviz para gerar a imagem
    system("dot -Tpng -o tree.png tree.dot");
    system("dot -Tpdf -o tree.pdf tree.dot");
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
    exit(1);
}
