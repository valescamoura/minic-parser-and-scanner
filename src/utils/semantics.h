#include "symbol-table.h"
#include "bison-tree.h"

#ifndef semantics_h
#define semantics_h


SLLT* build_identl(DT* i);
SLLT* build_argl(DT* i);
int check_operation_type(int type1, int type2, char operation, int lineno);
SYB* check_definition(ST* st, char* name);
void set_unknowns(ST* st, int type);
void yyerror(ST* st_vars, ST* st_func, const char* msg, ...);

#endif