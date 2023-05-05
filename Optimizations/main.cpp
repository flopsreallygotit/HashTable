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

    listDestructor(&words);

    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
