%{
#include<stdio.h>
#include<stdlib.h>

int yylex(void);
int yyerror(const char *s);

%}

%%

S : 'a' '\n'
  ;

%%

int main()
{
    printf("Enter a character: ");
    if (yyparse() == 0)
        printf("Accepted\n");
    return 0;
}

int yylex()
{
    return getchar();
}

int yyerror(const char *s)
{
    printf("Rejected\n");
    return 0;
}
