#pragma once

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "list.hpp"
#include "hashFuncs.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef size_t (*hashFunction_t) (elem_t element);

typedef struct hashTable
{
    size_t size = 0;
    hashFunction_t hashFunction;

    list_t *listArray = NULL;
} hashTable;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Create hash table
/// @param tableSize Size of hash table / Number of lists array
/// @param hashFunction Hash function for pasting, deletion and searching elements in hashTable
/// @param elementDestructor Function that deallocates memory allocated for element
/// @param elementComparator Function that returns difference sign of elem_t elements

void tableConstructor (hashTable *table, size_t hashTableSize, 
                       size_t (*hashFunction) (elem_t element),
                       void (*elementDestructor) (elem_t element),
                       int  (*elementComparator) (elem_t element1, elem_t element2));

/// @brief Delete hash table

void tableDestructor (hashTable *table);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief  Insert element in hash table
/// @return True if insert ended with success and false if element is already in hash table

bool tableInsert (hashTable *table, elem_t element);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool tableFind (hashTable *table, elem_t element);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
