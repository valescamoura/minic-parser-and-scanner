//variable definitions and data structure include
%{
#include <stdio.h>
#include "bison-tree.h"
#define variable 'YYDEBUG'
%}

%union{
    struct dt *t;
}

%token <t> NUMBER IDENTIFIER
%token <t> '+' '-' '*' '/' '=' '}' '{' ')' '(' ';' ',' '<' '>'
%token <t> FLOAT INT
%token <t> IF ELSE FOR WHILE
%token <t> EQ LE GE DIFF
%token EOL

%type <t> factor mag

//define rules
%%
king: 
| king mag EOL {printTree($2);}
mag: factor {$$ = createTree("mag", 1, $1);}
| mag '+' factor {$$ = createTree("mag", 3, $1, $2, $3);}
| mag '-' factor {$$ = createTree("mag", 3, $1, $2, $3);}
factor: NUMBER  {$$ = createTree("factor", 1, $1);}
| '+' factor {$$ = createTree("factor", 2, $1, $2);}
| '-' factor {$$ = createTree("factor", 2, $1, $2);}
%%

int main(int argc, char** argv){
    //yydebug = 1;
    return yyparse();
}