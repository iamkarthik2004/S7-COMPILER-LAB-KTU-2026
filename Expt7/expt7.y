%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token ID
%token NL
%token KEYWORD

%%

stmt : exp NL
       {
           printf("Valid Identifier\n");
       }
     ;

exp  : ID
     ;

%%
int main()
{
    printf("Enter an identifier: ");
    yyparse();
    return 0;
}
void yyerror(const char *s){
   printf("Invalid Identifier\n");
}
