#include <malloc.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "hashTable.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main (const int argc, const char **argv)
{
    const char *filename = simpleCommandLineParser(argc, argv);

    CHECKERROR(filename != NULL &&
               "Filename can't be NULL pointer.",
               -1);

    list_t words = {};
    fillWordsFromFile(&words, filename);

    char *outputFilename = stralloccat(filename, ".out");

    CHECKERROR(outputFilename != NULL &&
               "Can't allocate memory for output filename.",
               ALLOCATIONERROR);

    size_t (*hashFunctions[])(elem_t element) = 
    {
        constHash, firstCharAsciiHash,
        stringLengthHash, charSumHash,
        rollingLeftHash, rollingRightHash,
        polynomialRollingHash
    };

    DOTHIS(researchHashFunctions(outputFilename, &words, hashFunctions));

    free(outputFilename);

    listDestructor(&words);

    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
