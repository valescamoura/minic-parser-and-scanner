%options 

//define any needed variables
%{

%}


//matches all the tokens present on the language
//TODO: Add the char token
%%
    [A-Za-z][A-Za-z0-9]*      {return IDENTIFIER;}
    [0-9]+|[0-9]*.[0-9]+      {return NUMBER;}
    "float"                   {return FLOAT;}
    "int"                     {return INT;}
    "if"                      {return IF;}
    "else"                    {return ELSE;}
    "for"                     {return FOR;}
    "while"                   {return WHILE;}
    "=="                      {return EQ;}
    "<"                       {return LT;}
    ">"                       {return GT;}
    "<="                      {return LE;}
    ">="                      {return GE;}
    "!="                      {return DIFF;}
    ","                       {return COMMA;}
    ";"                       {return SEMICOLON;}
    "("                       {return OP;}
    ")"                       {return CP;}
    "{"                       {return OB;}
    "}"                       {return CB;}
    "+"                       {return PLUS;}
    "-"                       {return MINUS;}
    "/"                       {return DIVIDE;}
    "*"                       {return TIMES;}
    "="                       {return ASSIGN;}
    "\n"                      {return EOL;}
    " \t"                     {}
    .                         {printf("Character not matched: %c\n", *yytext);}
%%

//Only present for testing purposes
int main(void){
    return 0;
}