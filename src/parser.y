//variable definitions and data structure include
%{
#include <stdio.h>
#include "src/utils/bison-tree.h"
#define variable 'YYDEBUG'
%}

%union{
    struct dt *t;
}

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
| functionList YYEOF {generateTreeFile($1);}

functionList: functionList function     {$$ = createTree("functionlist", 2, $1, $2);}
|                                       {DT *t = createTree("epsilon", 0);$$ = createTree("functionList", 1, t);}

function: type IDENTIFIER '(' arglist ')' compoundstmt {$$ = createTree("function", 6, $1, $2, $3, $4, $5, $6);}

arglist: arg      {$$ = createTree("arglist", 1, $1);}
| arglist ',' arg {$$ = createTree("arglist", 3, $1, $2, $3);}

arg: type IDENTIFIER {$$ = createTree("arg", 2, $1, $2);}

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

declaration: type identlist ';' {$$ = createTree("declaration", 3, $1, $2, $3);}

identlist: IDENTIFIER ',' identlist {$$ = createTree("identlist", 3, $1, $2, $3);}
| IDENTIFIER                        {$$ = createTree("identlist", 1, $1);}

type: INT {$$ = createTree("type", 1, $1);}
| FLOAT   {$$ = createTree("type", 1, $1);}
| CHAR    {$$ = createTree("type", 1, $1);}

forStmt: FOR '(' expr ';' optExpr ';' optExpr ')' stmt {$$ = createTree("forStmt", 9, $1, $2, $3, $4, $5, $6, $7, $8, $9);}

optExpr: expr {$$ = createTree("optExpr", 1, $1);}
|             {DT *t = createTree("epsilon", 0);$$ = createTree("optExpr", 1, t);}

whileStmt: WHILE '(' expr ')' stmt {$$ = createTree("whileStmt", 5, $1, $2, $3, $4, $5);}

compoundstmt: '{' stmt_list '}' {$$ = createTree("compoundstmt", 3, $1, $2, $3);}

stmt_list: stmt_list stmt {$$ = createTree("stmt_list", 2, $1, $2);}
|                         {DT *t = createTree("epsilon", 0);$$ = createTree("stmt_list", 1, t);}

expr: IDENTIFIER '=' expr    {$$ = createTree("expr", 3, $1, $2, $3);}
| rvalue                     {$$ = createTree("expr", 1, $1);}

rvalue: rvalue compare mag  {$$ = createTree("rvalue", 3, $1, $2, $3);}
| mag                       {$$ = createTree("rvalue", 1, $1);}

compare: '<' {$$ = createTree("compare", 1, $1);}
| '>'        {$$ = createTree("compare", 1, $1);}
| EQ         {$$ = createTree("compare", 1, $1);}
| LE         {$$ = createTree("compare", 1, $1);}
| GE         {$$ = createTree("compare", 1, $1);}
| DIFF       {$$ = createTree("compare", 1, $1);} 

mag: term      {$$ = createTree("mag", 1, $1);}
| mag '+' term {$$ = createTree("mag", 3, $1, $2, $3);}
| mag '-' term {$$ = createTree("mag", 3, $1, $2, $3);}

term: factor      {$$ = createTree("term", 1, $1);}
| term '*' factor {$$ = createTree("term", 3, $1, $2, $3);}
| term '/' factor {$$ = createTree("term", 3, $1, $2, $3);}

factor: NUMBER   {$$ = createTree("factor", 1, $1);}
| IDENTIFIER     {$$ = createTree("factor", 1, $1);}
| CHAR_VALUE     {$$ = createTree("factor", 1, $1);}
| '(' expr ')'   {$$ = createTree("factor", 3, $1, $2, $3);}
| '+' factor     {$$ = createTree("factor", 2, $1, $2);}
| '-' factor     {$$ = createTree("factor", 2, $1, $2);}
%%

int main(int argc, char** argv){
    //yydebug = 1;
    return yyparse();
}