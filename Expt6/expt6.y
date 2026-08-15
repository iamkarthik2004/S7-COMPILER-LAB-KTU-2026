%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char *s);
%}

%token DIGIT ID NL

%left '+' '-'
%left '*' '/'

%%

stmt : ID '=' exp NL
     {
        printf("Valid Expression\n");
     }
     | exp '=' ID NL
     {
        printf("Valid Expression\n");
     }
     | exp NL
     {
        printf("Valid Expression\n");
     }
     ;

exp : exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | '(' exp ')'
    | DIGIT
    | ID
    ;

%%

int main()
{
    printf("Enter expression: ");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    printf("Invalid Expression\n");
}
