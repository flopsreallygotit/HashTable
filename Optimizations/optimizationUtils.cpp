#include <immintrin.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "optimizationUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int strcmpASM (const char *string1, const char *string2)
{
    int result = 0;

    asm volatile 
    (
        ".intel_syntax noprefix;"

        "1:"
        "lodsb;"
        "scasb;"
        "jne 2f;"

        "test al, al;"
        "jne 1b;"

        "xor eax, eax;"
        "jmp 3f;"

        "2:"
        "dec edi;"
        "sbb eax, eax;"

        "3:"
        ".att_syntax" 
        : "=a" (result)
        : "S" (string1), "D" (string2)
        : "memory"
    );

    return result;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
