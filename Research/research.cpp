#include "research.hpp"
#include "textUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void fillWordsFromFile (list_t *words, const char *filename)
{
    CHECKERROR(words != NULL &&
               "Words pointer can't be NULL.",
               (void) NULL);    

    CHECKERROR(filename != NULL &&
               "Filename can't be NULL pointer.",
               (void) NULL);

    text_t text = {};
    textConstructor(&text, filename, false);  

    int length = 0;
    char *word = NULL;

    char *currentWordPointer = text.buffer;

    while (sscanf(currentWordPointer, "%ms%n", &word, &length) != EOF)
    {
        node_t *wordPointer = listInsert(words, (elem_t) word);

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

ISERROR hashTableDump (FILE *file, hashTable *table)
{
    CHECKERROR(table != NULL &&
               "Table pointer can't be NULL.",
               NULLPOINTER);

    CHECKERROR(file != NULL &&
               "File pointer can't be NULL.", 
               NULLPOINTER);

    for (size_t listIndex = 0; listIndex < table->size; listIndex++)
         fprintf(file, "%lu\t%lu\n", 
                 listIndex, table->listArray[listIndex].size);

    putc('\n', file);

    return NOTERROR;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ISERROR researchHashFunctions (const char *filename, list_t *words,
                               hashFunction_t hashFunctions[])
{
    FILE *output = fopen(filename, "w");

    CHECKERROR(output != NULL &&
               "Can't open output file.",
               WRONGFILE);

    hashTable table = {};
    for (size_t hashFunctionIndex = 0; 
         hashFunctionIndex < HashFunctionsCount;
         hashFunctionIndex++)
    {
        hashTableConstructor(&table, HashTableSize, 
                            hashFunctions[hashFunctionIndex],
                            passDestruction, strcmp);

        hashFileWords(words,  &table);
        hashTableDump(output, &table);
        
        tableDestructor(&table);
    }

    fclose(output);

    return NOTERROR;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
