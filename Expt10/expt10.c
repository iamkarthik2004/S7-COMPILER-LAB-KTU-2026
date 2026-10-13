#include <stdio.h>
#include <ctype.h>

char p[20][20], first[26][20], follow[26][20];
int n, firstCount[26], followCount[26];
int firstVis[26], followVis[26];

void add(char set[], int *count, char ch){
    for (int i = 0; i < *count; i++)
        if (set[i] == ch) return;
    set[(*count)++] = ch;
}

void findFirst(int nt){
    if (firstVis[nt]) return;
    firstVis[nt] = 1;

    for (int i = 0; i < n; i++){
        if (p[i][0] - 'A' != nt) continue;

        char *rhs = p[i] + 3;

        for (int j = 0; rhs[j]; j++){
            if (!isupper(rhs[j])){
                add(first[nt], &firstCount[nt], rhs[j]);
                break;
            }

            int next = rhs[j] - 'A', eps = 0;
            findFirst(next);

            for (int k = 0; k < firstCount[next]; k++)
                if (first[next][k] == '#') eps = 1;
                else add(first[nt], &firstCount[nt], first[next][k]);

            if (!eps) break;
            if (!rhs[j + 1]) add(first[nt], &firstCount[nt], '#');
        }
    }
    firstVis[nt] = 0;
}

void findFollow(int nt){
    if (followVis[nt]) return;
    followVis[nt] = 1;

    for (int i = 0; i < n; i++){
        char *rhs = p[i] + 3;

        for (int j = 0; rhs[j]; j++){
            if (rhs[j] != 'A' + nt) continue;

            int k = j + 1, eps = 1;

            while (rhs[k]){
                if (!isupper(rhs[k])){
                    if (rhs[k] != '#')
                        add(follow[nt], &followCount[nt], rhs[k]);
                    eps = 0;
                    break;
                }

                int next = rhs[k] - 'A', hasEps = 0;
                findFirst(next);

                for (int m = 0; m < firstCount[next]; m++)
                    if (first[next][m] == '#') hasEps = 1;
                    else add(follow[nt], &followCount[nt], first[next][m]);

                if (!hasEps) { eps = 0; break; }
                k++;
            }

            if (eps && p[i][0] - 'A' != nt){
                int lhs = p[i][0] - 'A';
                findFollow(lhs);

                for (int m = 0; m < followCount[lhs]; m++)
                    add(follow[nt], &followCount[nt], follow[lhs][m]);
            }
        }
    }

    followVis[nt] = 0;
}

void print(char name[], char set[][20], int count[]){
    int seen[26] = {0};

    for (int i = 0; i < n; i++){
        int x = p[i][0] - 'A';
        if (seen[x]) continue;
        seen[x] = 1;
        printf("\n%s(%c) = { ", name, p[i][0]);
        for (int j = 0; j < count[x]; j++)
            printf("%c, ", set[x][j]);
        printf("}");
    }
}

int main(){
    printf("Enter no. of production rules: ");
    scanf("%d", &n);

    printf("\nEnter the production rules\n");
    for (int i = 0; i < n; i++)
        scanf("%s", p[i]);

    for (int r = 0; r < 26; r++)
        for (int i = 0; i < n; i++)
            findFirst(p[i][0] - 'A');

    print("First", first, firstCount);

    printf("\n\n-----------------------------------------------\n");

    add(follow[p[0][0] - 'A'], &followCount[p[0][0] - 'A'], '$');

    for (int r = 0; r < 26; r++)
        for (int i = 0; i < n; i++)
            findFollow(p[i][0] - 'A');

    print("Follow", follow, followCount);

    printf("\n");
    return 0;
}
