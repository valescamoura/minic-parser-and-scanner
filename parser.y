//variable definitions and data structure include
%{
#include <stdio.h>
#include "bison-tree.h"
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
%token EOL

%type <t> factor mag term compare expr rvalue

//define rules
%%
king: 
| king expr EOL {printTree($2);}

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
| '(' expr ')'   {$$ = createTree("factor", 3, $1, $2, $3);}
| '+' factor     {$$ = createTree("factor", 2, $1, $2);}
| '-' factor     {$$ = createTree("factor", 2, $1, $2);}
%%

int main(int argc, char** argv){
    yydebug = 1;
    return yyparse();
}