#include "symbol-table.h"
#include "bison-tree.h"

#ifndef semantics_h
#define semantics_h


SLLT* build_identl(DT* i);
SLLT* build_argl(DT* i);
void yyerror(ST* st_vars, ST* st_func, char* msg, ...);

#endif