#include "mainUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main ()
{
    list *List = listConstructor();

    char *element = NULL;
    scanf("%ms", &element);

    list *pointerToNodeWithMyElement = insertAfter(List, element);
    listDump(List);

    listDestructor(List);

    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
