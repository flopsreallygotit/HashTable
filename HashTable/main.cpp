#include "mainUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main (const int argc, const char **argv)
{
    const char *filename = simpleCommandLineParser(argc, argv);

    CHECKERROR(filename != NULL &&
               "Filename can't be NULL pointer.",
               -1);

    list_t words = {};
    fillWordsFromFile(&words, filename);

    hashTable table = {};
    hashTableConstructor(&table, 1009, 
                         constHash,
                         passDestruction);

    DOTHIS(hashFileWords(&words, &table));

    char *output = stralloccat(filename, ".out");

    CHECKERROR(output != NULL &&
               "Output filename string can't be NULL pointer.",
               -1);

    DOTHIS(getStats(output, &table));
    
    free(output);
    tableDestructor(&table);
    listDestructor(&words);

    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
