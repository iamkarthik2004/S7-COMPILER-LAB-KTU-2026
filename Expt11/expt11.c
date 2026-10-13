#include <stdio.h>
#include <string.h>

char p[20][30], st[100], in[100];
int n, top = -1, pos = 0;

void convert(char s[], char t[]){
    int i = 0, j = 0;

    while(s[i]){
        if(s[i] == 'i' && s[i + 1] == 'd'){
            t[j++] = 'i';
            i += 2;
        }
        else
            t[j++] = s[i++];
    }
    t[j] = '\0';
}

void show(char type, char production[]){
    int i;
    printf("$");
    for(i = 0; i <= top; i++)
        printf(st[i] == 'i' ? "id" : "%c", st[i]);
    printf("\t\t");
    for(i = pos; in[i]; i++)
        printf(in[i] == 'i' ? "id" : "%c", in[i]);
    printf("$\t\t");
    if(type == 'S'){
        if(st[top] == 'i')
            printf("SHIFT -> id");
        else
            printf("SHIFT -> %c", st[top]);
    }
    else
        printf("REDUCE TO %c (%s)", p[production[0]][0], production);

    printf("\n");
}
int reduce(){
    int i, len;
    char rhs[30];
    for(i = 0; i < n; i++){
        convert(p[i] + 3, rhs);
        len = strlen(rhs);
        if(len <= top + 1 && strncmp(st + top - len + 1, rhs, len) == 0){
            if(len == 3 && rhs[0] == rhs[2] && rhs[1] == '+' && in[pos] == '*')
                return 0;
            top -= len;
            st[++top] = p[i][0];

            show('R', p[i]);
            return 1;
        }
    }
    return 0;
}

int main(){
    int i;
    char temp[100];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions:\n");

    for(i = 0; i < n; i++)
        scanf("%s", p[i]);

    printf("\nEnter input string: ");
    scanf("%s", temp);

    convert(temp, in);

    printf("\nStack\t\tInput\t\tAction\n");
    printf("$\t\t%s$\t\t--\n", temp);

    while(in[pos]){
        st[++top] = in[pos++];

        show('S', NULL);

        while(reduce());
    }

    while(reduce());

    if(top == 0 && st[0] == p[0][0])
        printf("$%c\t\t$\t\tACCEPT\n", st[0]);
    else
        printf("$%c\t\t$\t\tREJECT\n", st[0]);

    return 0;
}
