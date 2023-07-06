#include <stdarg.h>
#include <stdlib.h>

typedef struct dt{
    char* value;
    int cnum;
    struct dt **children;
    int id; // Identificador único para cada nó
}DT;

DT* createTree(char* value, int cnum, ...);

void freeTree(DT* node);

void generateTreeFile(DT* root);
