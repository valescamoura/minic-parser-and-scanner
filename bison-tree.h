#include <stdarg.h>
#include <stdlib.h>

typedef struct dt{
    char* value;
    int cnum;
    struct dt **children;
}DT;

DT* createTree(char* value, int cnum, ...);
