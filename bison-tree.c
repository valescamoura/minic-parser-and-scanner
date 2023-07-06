#include "bison-tree.h"

int nodeIdCounter = 0; // Contador global para atribuir identificadores únicos

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

void generateTreeFile(DT* root) {
    generateDotFile(root, "tree.dot");
    // Chame o Graphviz para gerar a imagem
    system("dot -Tpng -o tree.png tree.dot");
}
