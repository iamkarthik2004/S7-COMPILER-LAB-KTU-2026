#include <stdio.h>
int main(){
 FILE *in, *out;
 char op, a[20], b[20], c[20];
 char file[50];
 printf("Enter input file name: ");
 scanf("%s", file);
 in = fopen(file, "r");
 out = fopen("output.txt", "w");
 if (in == NULL || out == NULL){
 printf("File error!\n");
 return 1;
 }
 while (fscanf(in, " %c %s %s %s", &op, a, b, c) == 4){
 if (op == '+'){
 fprintf(out, "MOV R0,%s\n", a);
 fprintf(out, "ADD R0,%s\n", b);
 fprintf(out, "MOV %s,R0\n", c);
 }
 else if (op == '-'){
 fprintf(out, "MOV R0,%s\n", a);
 fprintf(out, "SUB R0,%s\n", b);
 fprintf(out, "MOV %s,R0\n", c);
 }
 else if (op == '*'){
 fprintf(out, "MOV R0,%s\n", a);
 fprintf(out, "MUL R0,%s\n", b);
 fprintf(out, "MOV %s,R0\n", c);
 }
 else if (op == '/'){ 
fprintf(out, "MOV R0,%s\n", a);
 fprintf(out, "DIV R0,%s\n", b);
 fprintf(out, "MOV %s,R0\n", c);
 }
 else if (op == '='){
 fprintf(out, "MOV R0,%s\n", a);
 fprintf(out, "MOV %s,R0\n", c);
 }
 }
 fclose(in);
 fclose(out);
 printf("Target code generated in output.txt\n");
 return 0;
}
