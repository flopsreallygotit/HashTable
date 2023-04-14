#include "mainUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main (const int argc, const char **argv)
{
    const char *filename = simpleCommandLineParser(argc, argv);

    CHECKERROR(filename != NULL && 
               "Filename is NULL.", 
               -1);

    table *Table = tableConstructor(10, NULL);

    // DOTHIS(hashFileWords(filename, Table));
    // DOTHIS(outputHashTable(filename));

    tableDestructor(Table);

    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
