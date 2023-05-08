#include <time.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "optimizations.hpp"
#include "optimizationUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main (const int argc, const char **argv)
{
    const char *filename = checkFirstArgvAndGetIt(argc, argv);

    CHECKERROR(filename != NULL &&
               "Filename can't be NULL pointer.",
               -1);

    elementComparator_t elementComparator = strcmpASM; // strcmp for baseline / -o2
    hashFunction_t      hashFunction      = crc32AVX;  // polynomialRollingHash for baseline / -o2 / -o2 + strcmpASM

    list_t words = {};
    listConstructor(&words, stringDestructor, elementComparator);
    fillWordsFromFile(&words, filename);

    hashTable table = {};
    tableConstructor(&table, HashTableSize, 
                     hashFunction, 
                     passDestruction, 
                     elementComparator);

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
