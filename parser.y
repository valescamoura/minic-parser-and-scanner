//variable definitions and data structure include
%{
#include <stdio.h>

%}

%union{
    struct dt *t;
    char* s;
}



%token <s> NUMBER
%token <s> PLUS MINUS
//%token IDENTIFIER NUMBER
//%token INT FLOAT
//%token IF ELSE FOR WHILE
//%token EQ LT GT LE GE DIFF
//%token COMMA SEMICOLON OP CP OB CB
//%token PLUS MINUS DIVIDE TIMES ASSIGN
//%token EOL

%type <t> factor

//define rules
%%
factor: NUMBER  {}
| PLUS factor
| MINUS factor
%%

int main(int argc, char** argv){
    yyparse();
}

void yyerror(char* msg){
    fprintf(stderr, "error: %s\n", msg);
}