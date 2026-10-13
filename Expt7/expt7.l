%{
   #include "y.tab.h"
%}

%%

"int"|"double"|"float"|"char"|"if"|"else"|"while"|"for"|"return"|"void"    return KEYWORD;

[a-zA-Z_][a-zA-Z0-9_]*    return ID;

\n                        return NL;

[ \t]                     ;

.                         return yytext[0];

%%

int yywrap()
{
    return 1;
}
