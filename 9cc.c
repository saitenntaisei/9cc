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
    char *p = argv[1];
    printf("mov rax, %ld\n", strtol(p, &p, 10));
    while (*p != '\0')
    {
        if (*p == '+')
        {
            p++;
            printf("    add rax, %ld\n", strtol(p, &p, 10));
            continue;
        }
        if (*p == '-')
        {
            p++;
            printf("    sub rax, %ld\n", strtol(p, &p, 10));
            continue;
        }
        fprintf(stderr, "unepected input!");
        exit(1);
    }
    printf("    ret\n");
    return 0;
}