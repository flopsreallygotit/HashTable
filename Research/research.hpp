#pragma once

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "hashTable.hpp"
#include "universalUtils.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Number of functions we'll research

static const size_t HashFunctionsCount = 7;

/// @brief Size of hash table

static const size_t HashTableSize = 1009;

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
                               hashFunction_t hashFunctions[]);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
