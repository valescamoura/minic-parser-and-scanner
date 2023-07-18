//variable definitions and data structure include
%{
#include <stdio.h>
#include "src/utils/bison-tree.h"
#include "src/utils/symbol-table.h"
#define variable 'YYDEBUG'
#define TABLESIZE 5000

int error_comp;

%}

%union{
    struct dt *t;
}

%parse-param{ ST* st };

%token <t> NUMBER IDENTIFIER CHAR_VALUE
%token <t> '+' '-' '*' '/' '=' '}' '{' ')' '(' ';' ',' '<' '>'
%token <t> FLOAT INT CHAR
%token <t> IF ELSE FOR WHILE
%token <t> EQ LE GE DIFF

%type <t> factor mag term compare expr rvalue stmt_list compoundstmt stmt whileStmt optExpr forStmt
%type <t> type identlist arg arglist function declaration ifStmt elsePart functionList

//define rules
%%
root: 
| functionList YYEOF {
    if (error_comp == 1) {
        printf("Compilation error\n");
        return 1;
    }
    generateTreeFile($1); 
}

functionList: functionList function     {$$ = createTree("functionlist", 2, $1, $2);}
|                                       {DT *t = createTree("epsilon", 0);$$ = createTree("functionList", 1, t);}

function: type IDENTIFIER '(' arglist ')' compoundstmt {
    $$ = createTree("function", 6, $1, $2, $3, $4, $5, $6);
    free_symbol_table(st);
    ST* st = create_symbol_table(TABLESIZE);
}

arglist: arg      {$$ = createTree("arglist", 1, $1);}
| arglist ',' arg {$$ = createTree("arglist", 3, $1, $2, $3);}

arg: type IDENTIFIER {
    $$ = createTree("arg", 2, $1, $2);
    insert_symbol(st, $2->children[0]->value, $1->type);
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
    set_unknowns(st, $1->type);
}

identlist: IDENTIFIER ',' identlist {
    $$ = createTree("identlist", 3, $1, $2, $3);
    int r = insert_symbol(st, $1->children[0]->value, UNKNOWNTYPE);
    if (r == 1){
        error_comp = 1;
        printf("Error: duplicate declaration of variable \"%s\" at line %d\n", $1->children[0]->value, yylineno);
    }
}
| IDENTIFIER                        {
    $$ = createTree("identlist", 1, $1);
    int r = insert_symbol(st, $1->children[0]->value, UNKNOWNTYPE);
    if (r == 1){
        error_comp = 1;
        printf("Error: duplicate declaration of variable \"%s\" at line %d\n", $1->children[0]->value, yylineno);
    }
}

type: INT {$$ = createTree("type", 1, $1); $$->type = INTTYPE;}
| FLOAT   {$$ = createTree("type", 1, $1); $$->type = FLOATTYPE;}
| CHAR    {$$ = createTree("type", 1, $1); $$->type = CHARTYPE;}

forStmt: FOR '(' expr ';' optExpr ';' optExpr ')' stmt {$$ = createTree("forStmt", 9, $1, $2, $3, $4, $5, $6, $7, $8, $9);}

optExpr: expr {$$ = createTree("optExpr", 1, $1);}
|             {DT *t = createTree("epsilon", 0);$$ = createTree("optExpr", 1, t);}

whileStmt: WHILE '(' expr ')' stmt {$$ = createTree("whileStmt", 5, $1, $2, $3, $4, $5);}

compoundstmt: '{' stmt_list '}' {$$ = createTree("compoundstmt", 3, $1, $2, $3);}

stmt_list: stmt_list stmt {$$ = createTree("stmt_list", 2, $1, $2);}
|                         {DT *t = createTree("epsilon", 0);$$ = createTree("stmt_list", 1, t);}

expr: IDENTIFIER '=' expr    {
    $$ = createTree("expr", 3, $1, $2, $3);
    SYB* sb = search_for_symbol(st, $1->children[0]->value);
    if (!sb){
        error_comp = 1;
        printf("Error: use of undeclared variable \"%s\" at line %d\n", $1->children[0]->value, yylineno);
    }else{
        if (sb->type != $3->type && $3->type != ERRORTYPE){
            error_comp = 1;
            printf("Error: invalid assignment at line %d expression of type %s cannot be assigned to variable of type %s\n", yylineno, get_type_name($3->type), get_type_name(sb->type));
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
    SYB* sb = search_for_symbol(st, $1->children[0]->value);
    if (!sb){
        error_comp = 1;
        printf("Error: use of undeclared variable \"%s\" at line %d\n", $1->children[0]->value, yylineno);
    }else{
        $$->type = sb->type;
    }
}
| CHAR_VALUE     {$$ = createTree("factor", 1, $1); $$->type = $1->type;}
| '(' expr ')'   {$$ = createTree("factor", 3, $1, $2, $3); $$->type = $2->type;}
| '+' factor     {$$ = createTree("factor", 2, $1, $2); $$->type = $2->type;}
| '-' factor     {$$ = createTree("factor", 2, $1, $2); $$->type = $2->type;}
%%

int main(int argc, char** argv){
    //yydebug = 1;
    ST* symbol_table = create_symbol_table(TABLESIZE);
    return yyparse(symbol_table);
}