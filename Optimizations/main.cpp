#include <time.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "optimizations.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main (const int argc, const char **argv)
{
    const char *filename = checkFirstArgvAndGetIt(argc, argv);

    CHECKERROR(filename != NULL &&
               "Filename can't be NULL pointer.",
               -1);

    list_t words = {};
    listConstructor(&words, stringDestructor, strcmp);
    fillWordsFromFile(&words, filename);

    hashTable table = {};
    tableConstructor(&table, HashTableSize, 
                     polynomialRollingHash, 
                     passDestruction, strcmp);

    hashFileWords(&words, &table);

    clock_t start = clock();
    searchWordsInTable(&words, &table);
    clock_t end   = clock();

    printf(BOLD MAGENTA "Time: %lf;\n" RESET, (double) (end - start) / CLOCKS_PER_SEC);

    tableDestructor(&table);
    listDestructor(&words);

    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
