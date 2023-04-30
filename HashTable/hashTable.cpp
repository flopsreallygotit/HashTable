#include <stdlib.h>
// #include <immintrin.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "hashTable.hpp"
#include "textUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void hashTableConstructor (hashTable *table, size_t hashTableSize, 
                           size_t (*hashFunction) (char *string),
                           void (*elementDestructor) (elem_t element))
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

    table->hashTableSize = hashTableSize;
    table->hashFunction  = hashFunction;

    table->listArray = (list_t *) calloc (hashTableSize, sizeof(list_t));

    CHECKERROR(table->listArray != NULL &&
               "Can't allocate memory for list_t array.", 
               (void) NULL);

    for (size_t listIndex = 0; listIndex < hashTableSize; listIndex++)
        listConstructor(&table->listArray[listIndex], elementDestructor);
    
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

    if (listFind(&table->listArray[listIndex], element, stringComparator) == NULL)
    {
        node_t *elementNodePointer = listInsert(&table->listArray[listIndex], element);

        CHECKERROR(elementNodePointer != NULL, false);

        return true;
    }

    return false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void fillWordsFromFile (list_t *words, const char *filename)
{
    CHECKERROR(words != NULL &&
               "Words pointer can't be NULL.",
               (void) NULL);    

    CHECKERROR(filename != NULL &&
               "Filename can't be NULL pointer.",
               (void) NULL);

    listConstructor(words, stringDestructor);

    text_t text = {};
    textConstructor(&text, filename, false);  

    int length = 0;
    char *word = NULL;

    char *currentWordPointer = text.buffer;

    while (sscanf(currentWordPointer, "%ms%n", &word, &length) != EOF)
    {
        node_t *wordPointer = listInsert(words, word);

        CHECKERROR(wordPointer != NULL &&
                   "Can't insert word.",
                   (void) NULL);

        currentWordPointer += length;
    }

    textDestructor(&text);

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ISERROR hashFileWords (list_t *words, hashTable *table)
{
    node_t *currentNode = words->head->next;

    while (currentNode != NULL)
    {
        tableInsert(table, currentNode->element);

        currentNode = currentNode->next;
    }

    return NOTERROR;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ISERROR getStats (const char *filename, hashTable *table)
{
    CHECKERROR(table != NULL &&
               "Table pointer can't be NULL.",
               NULLPOINTER);

    CHECKERROR(filename != NULL &&
               "Filename pointer can't be NULL.", 
               NULLPOINTER);

    FILE *file = fopen(filename, "w");

    for (size_t listIndex = 0; listIndex < table->hashTableSize; listIndex++)
         fprintf(file, "%lu\t%lu\n", 
                 listIndex, table->listArray[listIndex].size);

    putc('\n', file);

    fclose(file);

    return NOTERROR;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// TODO Read about Google hash table optimization experience
// TODO Read about allocator work: Knut vol.1, Ritchie, Alexandresco
