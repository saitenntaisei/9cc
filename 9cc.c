#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    TK_RESERVED,
    TK_NUM,
    TK_EOF
} TokenKind;
typedef struct Token Token;
struct Token
{
    TokenKind kind;
    Token *next;
    long val;
    char c;
};

Token *token;

void preDecl()
{
    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
}
Token *newReserve(Token *pre, TokenKind kind, char c)
{
    Token *next = calloc(1, sizeof(Token));
    pre->next = next;
    next->kind = kind;
    next->c = c;
    return next;
}
Token *categorize(char *c)
{
    Token head;
    head.next = NULL;
    Token *cur = &head;
    while (*c != '\0')
    {
        if (*c == ' ')
        {
            c++;
            continue;
        }
        if (*c == '+' || *c == '-')
        {
            cur = newReserve(cur, TK_RESERVED, *c);
            c++;
            continue;
        }
        if (0 <= *c - '0' <= 9)
        {
            cur = newReserve(cur, TK_NUM, '#');
            cur->val = strtol(c, &c, 10);
            continue;
        }
        fprintf(stderr, "unexpected input!");
        exit(1);
    }
    cur = newReserve(cur, TK_EOF, '\0');
    return head.next;
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
    Token *token = categorize(p);

    Token *cur = token;
    if (token->kind != TK_NUM)
    {
        fprintf(stderr, "incorrect argc!");
        return 1;
    }
    printf("mov rax, %ld\n", cur->val);
    cur = token->next;
    free(token);
    token = cur;
    while (token->kind != TK_EOF)
    {
        if (token->kind == TK_RESERVED && token->c == '+')
        {
            printf("    add rax, ");
            cur = token->next;
            free(token);
            token = cur;
            continue;
        }
        if (token->kind == TK_RESERVED && token->c == '-')
        {
            printf("    sub rax, ");
            cur = token->next;
            free(token);
            token = cur;
            continue;
        }
        printf("%ld\n", token->val);
        cur = token->next;
        free(token);
        token = cur;
    }
    printf("    ret\n");
    return 0;
}