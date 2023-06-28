%{
#include <stdlib.h>
%}

%%    
"+" |     
"-" {
    char *s = (char*) malloc(sizeof(char));
    s[0] = yytext[0];
    printf("operator:%s\n", s);
}
[0-9]+|[0-9]*"."[0-9]+ {
    char *s = (char*) malloc(sizeof(char)*yyleng);
    strcpy(s, yytext);
    printf("number:%s\n", yytext);
}
\n                        {printf("eol\n");}
[ \t]                     {}
.                         {printf("Character not matched: %c\n", *yytext);}
%%

int main(void){
    yylex();
}