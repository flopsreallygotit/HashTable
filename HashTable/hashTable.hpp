#pragma once

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "list.hpp"
#include "hashFuncs.hpp"
#include "universalUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct hashTable
{
    size_t hashTableSize = 0;
    size_t (*hashFunction) (elem_t element);

    list_t *listArray = NULL;
} hashTable;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Create hash table
/// @param tableSize Size of hash table / Number of lists array
/// @param hashFunction Hash function for pasting, deletion and searching elements in hashTable
/// @param elementDestructor Function that deallocates memory allocated for element

void hashTableConstructor (hashTable *table, size_t hashTableSize, 
                           size_t (*hashFunction) (char *string),
                           void (*elementDestructor) (elem_t element));

/// @brief Delete hash table

void tableDestructor (hashTable *table);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief  Insert element in hash table
/// @return True if insert ended with success and false if element is already in hash table

bool tableInsert (hashTable *table, elem_t element);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Fill list with words from file

void fillWordsFromFile (list_t *words, const char *filename);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Put words in the file in hash table

ISERROR hashFileWords (list_t *words, hashTable *table);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Output size of lists in file for subsequent processing

ISERROR hashTableDump (FILE *file, hashTable *table);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Dump info about hash tables in output file
/// @param hashFunctions Array of hash functions to research

ISERROR researchHashFunctions (const char *filename, list_t *words,
                               size_t (*hashFunctions[])(elem_t element));

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
