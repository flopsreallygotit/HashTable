#include "textUtils.hpp"
#include "optimizations.hpp"

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
