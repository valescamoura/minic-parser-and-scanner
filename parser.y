//variable definitions and data structure include
%{
#include <stdio.h>
%}

%token IDENTIFIER NUMBER
%token INT FLOAT
%token IF ELSE FOR WHILE
%token EQ LT GT LE GE DIFF
%token COMMA SEMICOLON OP CP OB CB
%token PLUS MINUS DIVIDE TIMES ASSIGN
%token EOL

//define rules
%%

%%

int main(int argc, char** argv){
    yyparse();
}

void yyerror(char* msg){
    fprintf(stderr, "error: %s\n", msg);
}