#include "mainUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main (const int argc, const char **argv)
{
    const char *filename = simpleCommandLineParser(argc, argv);

    CHECKERROR(filename != NULL &&
               "Filename can't be NULL pointer.",
               -1);

    list *Words = getFileWords(filename);

    CHECKERROR(Words != NULL &&
               "Words can't be NULL pointer.",
               -1);

    table *Table = tableConstructor(1009, polynomialRollingHash);

    CHECKERROR(Table != NULL &&
               "Table can't be NULL pointer.",
               -1);

    DOTHIS(hashFileWords(Words, Table));

    char *output = stralloccat(filename, ".out");
    DOTHIS(getStats(output, Table));
    free(output);

    listDestructor(Words,  stringDestructor);

    tableDestructor(Table, passDestruction);

    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
