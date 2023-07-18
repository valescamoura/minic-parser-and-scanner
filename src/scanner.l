%option noyywrap nodefault yylineno
%{
#include <stdlib.h>
#include "src/utils/bison-tree.h"
#include "src/utils/symbol-table.h"
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
"char"                    {return CHAR;}
"while"                   {return WHILE;}
"=="                      {return EQ;}
"<="                      {return LE;}
">="                      {return GE;}
"!="                      {return DIFF;} 
[0-9]*"."?[0-9]+(e[+-]?[0-9]+)? {
    yylval.t = createTree("number", 1, yylval.t);
    yylval.t->type = FLOATTYPE;
    return NUMBER;
}
[0-9]+                    {
    yylval.t = createTree("number", 1, yylval.t);
    yylval.t->type = INTTYPE;
    return NUMBER;
}
'[ -~]'                   {
    yylval.t = createTree("char", 1, yylval.t);
    yylval.t->type = CHARTYPE;
    return CHAR_VALUE;
}
[A-Za-z][A-Za-z0-9]*      {yylval.t = createTree("identifier", 1, yylval.t); return IDENTIFIER;}
<<EOF>>                   {return YYEOF;}
[ \t\n]                     {}
.                         {printf("Character not matched: %c\n", *yytext);exit(1);}
%%