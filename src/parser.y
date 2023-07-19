//variable definitions and data structure include
%{
#include <stdio.h>
#include "src/utils/bison-tree.h"
#include "src/utils/symbol-table.h"
#include "src/utils/semantics.h"
#define variable 'YYDEBUG'
#define TABLESIZE 5000

int error_count;

%}

%union{
    struct dt *t;
}

%parse-param{ ST* st_func } {ST* st_vars}

%token <t> NUMBER IDENTIFIER CHAR_VALUE RETURN
%token <t> '+' '-' '*' '/' '=' '}' '{' ')' '(' ';' ',' '<' '>'
%token <t> FLOAT INT CHAR
%token <t> IF ELSE FOR WHILE
%token <t> EQ LE GE DIFF

%type <t> factor mag term compare expr rvalue stmt_list compoundstmt stmt whileStmt optExpr forStmt
%type <t> type identlist arg arglist function declaration ifStmt elsePart functionList functionBody
%type <t> returnStmt functionCall

//define rules
%%
root: 
| functionList YYEOF {
    if (error_count > 0) {
        printf("Compilation error\n");
        return 1;
    }
    generateTreeFile($1); 
}

functionList: functionList function     {$$ = createTree("functionlist", 2, $1, $2);}
|                                       {DT *t = createTree("epsilon", 0);$$ = createTree("functionList", 1, t);}

function: type IDENTIFIER '(' arglist ')' functionBody {
    $$ = createTree("function", 6, $1, $2, $3, $4, $5, $6);
    insert_symbol(st_func, $2->children[0]->value, $1->type, 0);

    if ($6->type != $1->type) yyerror(st_vars, st_func, "invalid return type of function %s. expected %s got %s", $2->children[0]->value, get_type_name($1->type), get_type_name($6->type));

    SLLT* as = build_argl($4);
    SLLT* aux = as;

    while(aux != NULL){
        int r = insert_func_arg(st_func, $2->children[0]->value, aux->symbol->name, aux->symbol->type);
        if (r == 1){
            yyerror(st_vars, st_func, "duplicated argument %s", aux->symbol->name);
        }
        aux = aux->next;
    }

    printf("\n\nSymbol table for function %s", $2->children[0]->value);
    printST(st_vars);
    free_symbol_table(st_vars);
    st_vars = create_symbol_table(TABLESIZE);
}

functionCall: IDENTIFIER '(' identlist ')' {
    $$ = createTree("functionCall", 4, $1, $2, $3, $4);
    DT* ident = $1->children[0];
    SYB* sb = check_definition(st_vars, st_func, ident->value, 0);
    if (sb != NULL){

        SLLT* ls = build_identl($3);
        SLLT* aux = ls;
        SYB* argsb;
        while(aux != NULL){
            argsb = check_definition(st_vars, st_func, aux->symbol->name, 1);
            if (argsb != NULL) aux->symbol->type = argsb->type;
            aux = aux->next;
        }
        aux = ls;
        SLLT * aux2 = sb->arglist;

        while(aux != NULL && aux2 != NULL){
            int type1, type2;
            type1 = aux->symbol->type;
            type2 = aux2 ->symbol->type;
            if(type1 != type2){
                yyerror(st_vars, st_func, "invalid argument of type %s. expected %s", get_type_name(type1), get_type_name(type2));
            }
            aux = aux->next;
            aux2 = aux2->next;
        }

        if (aux) yyerror(st_vars, st_func, "too many parameters");
        if (aux2) yyerror(st_vars, st_func, "lacking parameters");

        $$->type = sb->type;
    }
}

arglist: arg      {$$ = createTree("arglist", 1, $1);}
| arglist ',' arg {$$ = createTree("arglist", 3, $1, $2, $3);}

arg: type IDENTIFIER {
    $$ = createTree("arg", 2, $1, $2);
    insert_symbol(st_vars, $2->children[0]->value, $1->type, 1);
}

stmt: expr ';' {$$ = createTree("stmt", 2, $1, $2);}
| whileStmt    {$$ = createTree("stmt", 1, $1);}
| ';'          {$$ = createTree("stmt", 1, $1);}
| compoundstmt {$$ = createTree("stmt", 1, $1);}
| forStmt      {$$ = createTree("stmt", 1, $1);}
| declaration  {$$ = createTree("stmt", 1, $1);}
| ifStmt       {$$ = createTree("stmt", 1, $1);}

ifStmt: IF '(' expr ')' stmt elsePart {$$ = createTree("ifStmt", 6, $1, $2, $3, $4, $5, $6);}

elsePart: ELSE stmt {$$ = createTree("elsePart", 2, $1, $2);}
|                   {DT *t = createTree("epsilon", 0);$$ = createTree("elsePart", 1, t);}

declaration: type identlist ';' {
    $$ = createTree("declaration", 3, $1, $2, $3);
    SLLT* ls = build_identl($2);
    SLLT* aux = ls;

    while(aux != NULL){
        int r = insert_symbol(st_vars, aux->symbol->name, $1->type, 1);
        if (r == 1){
            yyerror(st_vars, st_func, "duplicate declaration of variable \"%s\"", $1->children[0]->value);
        }
        aux = aux->next;
    }

}

identlist: IDENTIFIER ',' identlist { $$ = createTree("identlist", 3, $1, $2, $3); }
| IDENTIFIER                        { $$ = createTree("identlist", 1, $1); }

type: INT {$$ = createTree("type", 1, $1); $$->type = INTTYPE;}
| FLOAT   {$$ = createTree("type", 1, $1); $$->type = FLOATTYPE;}
| CHAR    {$$ = createTree("type", 1, $1); $$->type = CHARTYPE;}

forStmt: FOR '(' expr ';' optExpr ';' optExpr ')' stmt {$$ = createTree("forStmt", 9, $1, $2, $3, $4, $5, $6, $7, $8, $9);}

optExpr: expr {$$ = createTree("optExpr", 1, $1);}
|             {DT *t = createTree("epsilon", 0);$$ = createTree("optExpr", 1, t);}

whileStmt: WHILE '(' expr ')' stmt {$$ = createTree("whileStmt", 5, $1, $2, $3, $4, $5);}

compoundstmt: '{' stmt_list '}' {$$ = createTree("compoundstmt", 3, $1, $2, $3);}

functionBody: '{' stmt_list returnStmt '}'  {$$ = createTree("functionBody", 4, $1, $2, $3, $4); $$->type = $3->type;}

returnStmt: RETURN rvalue ';' {$$ = createTree("returnStmt", 3, $1, $2, $3); $$->type = $2->type;}

stmt_list: stmt_list stmt {$$ = createTree("stmt_list", 2, $1, $2);}
|                         {DT *t = createTree("epsilon", 0);$$ = createTree("stmt_list", 1, t);}

expr: IDENTIFIER '=' expr    {
    $$ = createTree("expr", 3, $1, $2, $3);
    SYB* sb = search_for_symbol(st_vars, $1->children[0]->value, 1);
    if (!sb){
        yyerror(st_vars, st_func, "use of undeclared variable \"%s\"", $1->children[0]->value);
    }else{
        if (sb->type != $3->type){
            yyerror(st_vars, st_func, "invalid assignment: expression of type %s cannot be assigned to variable of type %s", get_type_name($3->type), get_type_name(sb->type));
        }
    }
    
}
| rvalue                     {$$ = createTree("expr", 1, $1); $$->type = $1->type;}

rvalue: rvalue compare mag  {
    $$ = createTree("rvalue", 3, $1, $2, $3); 
    int check = check_operation_type($1->type, $3->type, $2->children[0]->value[0], yylineno);
    if (check != ERRORTYPE) $$->type = INTTYPE;
}
| mag                       {$$ = createTree("rvalue", 1, $1); $$->type = $1->type;}

compare: '<' {$$ = createTree("compare", 1, $1);}
| '>'        {$$ = createTree("compare", 1, $1);}
| EQ         {$$ = createTree("compare", 1, $1);}
| LE         {$$ = createTree("compare", 1, $1);}
| GE         {$$ = createTree("compare", 1, $1);}
| DIFF       {$$ = createTree("compare", 1, $1);} 

mag: term      {$$ = createTree("mag", 1, $1); $$->type = $1->type;}
| mag '+' term {$$ = createTree("mag", 3, $1, $2, $3); $$->type = check_operation_type($1->type, $3->type, '+', yylineno);}
| mag '-' term {$$ = createTree("mag", 3, $1, $2, $3); $$->type = check_operation_type($1->type, $3->type, '-', yylineno);}

term: factor      {$$ = createTree("term", 1, $1); $$->type = $1->type;}
| term '*' factor {$$ = createTree("term", 3, $1, $2, $3); $$->type = check_operation_type($1->type, $3->type, '*', yylineno);}
| term '/' factor {$$ = createTree("term", 3, $1, $2, $3); $$->type = check_operation_type($1->type, $3->type, '/', yylineno);}

factor: NUMBER   {$$ = createTree("factor", 1, $1); $$->type = $1->type;}
| IDENTIFIER     {
    $$ = createTree("factor", 1, $1); 
    SYB* sb = check_definition(st_vars, st_func, $1->children[0]->value, 1);
    if (sb != NULL){
        $$->type = sb->type;
    }
}
| CHAR_VALUE     {$$ = createTree("factor", 1, $1); $$->type = $1->type;}
| functionCall   {$$ = createTree("factor", 1, $1); $$->type = $1->type;}
| '(' expr ')'   {$$ = createTree("factor", 3, $1, $2, $3); $$->type = $2->type;}
| '+' factor     {$$ = createTree("factor", 2, $1, $2); $$->type = $2->type;}
| '-' factor     {$$ = createTree("factor", 2, $1, $2); $$->type = $2->type;}
%%

int main(int argc, char** argv){
    //yydebug = 1;
    ST* symbol_table_functions = create_symbol_table(TABLESIZE);
    ST* symbol_table_vars = create_symbol_table(TABLESIZE);
    return yyparse(symbol_table_vars, symbol_table_functions);
}