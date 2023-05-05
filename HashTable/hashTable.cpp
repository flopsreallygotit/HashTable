#include <stdlib.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "hashTable.hpp"
#include "universalUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void hashTableConstructor (hashTable *table, size_t size, 
                           hashFunction_t hashFunction,
                           void (*elementDestructor) (elem_t element),
                           int  (*elementComparator) (elem_t element1, elem_t element2))
{
    CHECKERROR(table != NULL &&
               "Table pointer can't be NULL.",
               (void) NULL);

    CHECKERROR(hashFunction != NULL &&
               "Hash function pointer can't be NULL.",
               (void) NULL);

    CHECKERROR(elementDestructor != NULL &&
               "Element destructor function pointer can't be NULL.",
               (void) NULL);

    CHECKERROR(elementComparator != NULL &&
               "Element comparator function pointer can't be NULL.",
               (void) NULL);

    table->size = size;
    table->hashFunction = hashFunction;

    table->listArray = (list_t *) calloc (size, sizeof(list_t));

    CHECKERROR(table->listArray != NULL &&
               "Can't allocate memory for list_t array.", 
               (void) NULL);

    for (size_t listIndex = 0; listIndex < size; listIndex++)
        listConstructor(&table->listArray[listIndex], 
                        elementDestructor, elementComparator);
    
    return;
}

void tableDestructor (hashTable *table)
{
    CHECKERROR(table != NULL &&
               "Table pointer can't be NULL.",
               (void) NULL);

    for (size_t listIndex = 0; listIndex < table->size; ++listIndex)
        listDestructor(&table->listArray[listIndex]);

    free(table->listArray);

    *table = {
                .size = 0,

                .hashFunction = NULL,
                .listArray    = NULL,
             };

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool tableInsert (hashTable *table, elem_t element)
{
    CHECKERROR(table != NULL &&
               "Table pointer can't be NULL.",
               false);

    size_t listIndex = table->hashFunction(element) % table->size;

    if (listFind(&table->listArray[listIndex], element) == NULL)
    {
        node_t *elementNodePointer = listInsert(&table->listArray[listIndex], element);

        CHECKERROR(elementNodePointer != NULL, false);

        return true;
    }

    return false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
