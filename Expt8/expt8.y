%{
#include <stdio.h>
int yylex();
void yyerror(char *s);
int error = 0;
%}
%token DIGIT NL
%left '+' '-'
%left '*' '/'
%%
stmt : exp NL { if (!error) printf("Result = %d\n", $1); };
exp : exp '+' exp { $$ = $1 + $3; }
    | exp '-' exp { $$ = $1 - $3; }
    | exp '*' exp { $$ = $1 * $3; }
    | exp '/' exp { if ($3 == 0) { yyerror("Division by zero"); error = 1; $$ = 0; } else $$ = $1 / $3; }
    | DIGIT { $$ = $1; }
    ;
%%
int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}
void yyerror(char *s) {
    printf("Error: %s\n", s);
}
