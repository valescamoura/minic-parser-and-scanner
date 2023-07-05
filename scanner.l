%option noyywrap nodefault yylineno
%{
#include <stdlib.h>
#include "bison-tree.h"
#include "parser.tab.h"

#define YY_USER_ACTION yylval.t = strToTree(yytext, yyleng);

%}

%%   
">" |
"<" |
"," |
";" |
"(" |
")" |
"{" |
"}" |
"=" |
"*" |
"/" | 
"+" |
"-"                       {return yytext[0];}
"float"                   {return FLOAT;}
"int"                     {return INT;}
"if"                      {return IF;}
"else"                    {return ELSE;}
"for"                     {return FOR;}
"while"                   {return WHILE;}
"=="                      {return EQ;}
"<="                      {return LE;}
">="                      {return GE;}
"!="                      {return DIFF;} 
[0-9]+|[0-9]*"."[0-9]+    {return NUMBER;}
[A-Za-z][A-Za-z0-9]*      {return IDENTIFIER;}
\n                        {return EOL;}
[ \t]                     {}
.                         {printf("Character not matched: %c\n", *yytext);}
%%