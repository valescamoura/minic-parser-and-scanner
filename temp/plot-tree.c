#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dt {
    char* value;
    int cnum;
    struct dt** children;
    int id; // Identificador único para cada nó
} DT;

int nodeIdCounter = 0; // Contador global para atribuir identificadores únicos

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


int main() {
    DT* root = (DT*)malloc(sizeof(DT));
    root->value = "A";
    root->cnum = 2;
    root->children = (DT**)malloc(root->cnum * sizeof(DT*));

    DT* child1 = (DT*)malloc(sizeof(DT));
    child1->value = "B";
    child1->cnum = 1;
    child1->children = (DT**)malloc(child1->cnum * sizeof(DT*));

    DT* child2 = (DT*)malloc(sizeof(DT));
    child2->value = "C";
    child2->cnum = 1;
    child2->children = (DT**)malloc(child2->cnum * sizeof(DT*));

    DT* grandchild = (DT*)malloc(sizeof(DT));
    grandchild->value = "D";
    grandchild->cnum = 0;
    grandchild->children = NULL;

    DT* grandchild2 = (DT*)malloc(sizeof(DT));
    grandchild2->value = "D";
    grandchild2->cnum = 0;
    grandchild2->children = NULL;


    child2->children[0] = grandchild;
    child1->children[0] = grandchild2;

    root->children[0] = child1;
    root->children[1] = child2;

    generateDotFile(root, "tree.dot");

    // Chame o Graphviz para gerar a imagem
    system("dot -Tpng -o tree.png tree.dot");

    // Libere a memória alocada
    freeTree(root);

    return 0;
}
