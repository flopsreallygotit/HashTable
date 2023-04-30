#include "mainUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

table *tableConstructor (size_t tableSize, 
                         size_t (*hashFunction) (char *string))
{
    table *Table = (table *) calloc (1, sizeof(table));

    CHECKERROR(Table != NULL &&
               "Can't allocate memory for table.", 
               NULL);

    Table->tableSize    = tableSize;
    Table->hashFunction = hashFunction;

    Table->listArray = (list **) calloc (tableSize, sizeof(list *));

    CHECKERROR(Table->listArray != NULL &&
               "Can't allocate memory for list array.", 
               NULL);

    for (size_t list_idx = 0; list_idx < tableSize; list_idx++)
    {
        Table->listArray[list_idx] = listConstructor();

        CHECKERROR(Table->listArray[list_idx] != NULL && // TODO change naming.
                   "Can't allocate memory for list array.", 
                   NULL);
    }

    return Table;
}

void tableDestructor (table *Table, 
                      void (*elementDestructor) (elem_t element))
{
    if (Table == NULL)
    {
        PUTWARNING("Can't destroy NULL pointer.");

        return;
    }

    for (size_t list_idx = 0; list_idx < Table->tableSize; ++list_idx)
    {
        listDestructor(Table->listArray[list_idx], 
                       elementDestructor);

        Table->listArray[list_idx] = NULL;
    }

    free(Table->listArray);
    // *Table = {
    //     .listArray = NULL,
    //     .hashFunction ... // TODO
    // };
    Table->listArray = NULL;

    Table->tableSize    = 0;
    Table->hashFunction = NULL;

    free(Table);

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void simpleTableDump (table *Table)
{
    printf(BOLD MAGENTA "Table dump:\n" RESET);

    for (size_t table_idx = 0; table_idx < Table->tableSize; table_idx++)
    {
        printf(BOLD MAGENTA "List number %lu:\n" RESET, table_idx);
        
        listDump(Table->listArray[table_idx]);
    }

    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool tableInsert (table *Table, elem_t element)
{
    CHECKERROR(Table != NULL && 
               "Table can't be NULL pointer.", 
               false);

    size_t list_idx = Table->hashFunction(element) % Table->tableSize;

    if (listFind(Table->listArray[list_idx], element, stringComparator) == NULL)
    {
        node *elementNodePointer = listInsert(Table->listArray[list_idx], element);

        CHECKERROR(elementNodePointer != NULL, false);

        return true;
    }

    return false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

list *getFileWords (const char *filename) // TODO rename readWords...
{
    CHECKERROR(filename != NULL &&
               "Filename can't be NULL pointer.",
               NULL);

    text *Text = textConstructor(filename, false);  // Ritchie B allocator
                                                    // Alexandresco cpp con std::allocator is the same to allocation as std::vector to vexation
    CHECKERROR(Text  != NULL &&                     // Bryant
               "Text can't be NULL pointer.",       // WARNING Knut vol.1 allocator
               NULL);                               // TODO Text static
                                                    // TODO google hash table               
    list *Words = listConstructor();

    CHECKERROR(Words != NULL &&
               "Words can't be NULL pointer.",
               NULL);

    int length = 0;
    char *word = NULL;

    char *currentWordPointer = Text->buffer;

    while (sscanf(currentWordPointer, "%ms%n", &word, &length) != EOF)
    {
        node *wordPointer = listInsert(Words, word);

        CHECKERROR(wordPointer != NULL &&
                   "Can't insert word.",
                   NULL);

        currentWordPointer += length;
    }

    textDestructor(Text);

    return Words;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ISERROR hashFileWords (list *Words, table *Table)
{
    CHECKERROR(Words != NULL &&
               "Words can't be NULL pointer.", 
               NULLPOINTER);

    CHECKERROR(Table != NULL &&
               "Table can't be NULL pointer.", // TODO Rename files
               NULLPOINTER);

    node *currentNode = Words->head->next;

    while (currentNode != NULL)
    {
        tableInsert(Table, currentNode->element);

        currentNode = currentNode->next;
    }

    return NOTERROR;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ISERROR getStats (const char *filename, table *Table)
{
    CHECKERROR(filename != NULL &&
               "Filename can't be NULL pointer.", 
               NULLPOINTER);

    CHECKERROR(Table != NULL &&
               "Table can't be NULL pointer.", 
               NULLPOINTER);

    FILE *file = fopen(filename, "w");

    for (size_t list_idx = 0; list_idx < Table->tableSize; list_idx++)
        fprintf(file, "%lu\t%lu\n", 
                list_idx, Table->listArray[list_idx]->size);

    putc('\n', file);

    fclose(file);

    return NOTERROR;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
