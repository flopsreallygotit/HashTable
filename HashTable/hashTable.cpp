#include <stdlib.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "hashTable.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void hashTableConstructor (hashTable *table, size_t hashTableSize, 
                           size_t (*hashFunction) (elem_t element),
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

    table->hashTableSize = hashTableSize;
    table->hashFunction  = hashFunction;

    table->listArray = (list_t *) calloc (hashTableSize, sizeof(list_t));

    CHECKERROR(table->listArray != NULL &&
               "Can't allocate memory for list_t array.", 
               (void) NULL);

    for (size_t listIndex = 0; listIndex < hashTableSize; listIndex++)
        listConstructor(&table->listArray[listIndex], 
                        elementDestructor, elementComparator);
    
    return;
}

void tableDestructor (hashTable *table)
{
    CHECKERROR(table != NULL &&
               "Table pointer can't be NULL.",
               (void) NULL);

    for (size_t listIndex = 0; listIndex < table->hashTableSize; ++listIndex)
        listDestructor(&table->listArray[listIndex]);

    free(table->listArray);

    *table = {
                .hashTableSize = 0,

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

    size_t listIndex = table->hashFunction(element) % table->hashTableSize;

    if (listFind(&table->listArray[listIndex], element) == NULL)
    {
        node_t *elementNodePointer = listInsert(&table->listArray[listIndex], element);

        CHECKERROR(elementNodePointer != NULL, false);

        return true;
    }

    return false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
