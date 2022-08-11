#include <stdio.h>
#include <stdlib.h>
void preDecl()
{
    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
}
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "incorrect argc!");
        return 1;
    }
    preDecl();
    printf("mov rax, ");
    while (*argv[1] != '\0')
    {
        if (*argv[1] == '+')
        {
            argv[1]++;
            printf("\n");
            printf("    add rax, ");
            continue;
        }
        if (*argv[1] == '-')
        {
            argv[1]++;
            printf("\n");
            printf("    sub rax, ");
            continue;
        }
        printf("%c", *argv[1]);
        argv[1]++;
    }
    printf("\n");
    printf("    ret\n");
    return 0;
}