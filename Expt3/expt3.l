%{
#include <stdio.h>

int lines = 0;
int words = 0;
int chars = 0;

FILE *yyin;
%}

%%

[\t]+          ;

\n             {
                    lines++;
               }

[^ \t\n]+       {
                    words++;
                    chars += yyleng;
               }

%%

int yywrap()
{
    return 1;
}

int main()
{
    FILE *fp;
    char filename[100];

    printf("Enter the input file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    yyin = fp;
    yylex();

    fclose(fp);

    printf("\nNumber of lines: %d\n", lines);
    printf("Number of words: %d\n", words);
    printf("Number of characters: %d\n", chars);

    return 0;
}
