#include <iostream>
#include <stdexcept>
#include <limits>

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            throw std::invalid_argument("incorrect argc!");
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
    printf("  mov rax, %d\n", atoi(argv[1]));
    printf("  ret\n");
}