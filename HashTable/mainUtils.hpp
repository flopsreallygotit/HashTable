#ifndef MAIN_UTILS_HPP
#define MAIN_UTILS_HPP

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <immintrin.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "listUtils.h"
#include "universalUtils.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct table
{
    size_t tableSize = 0;
    void *hashFunction = NULL;

    list **listArray = NULL;
} table;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Creates hash table.
/// @param tableSize Size of hash table / Number of lists array.
/// @param hashFunction Hash function for pasting, deletion and searching elements in table.
/// @return Pointer to table struct.

table *tableConstructor (size_t tableSize, 
                         void *hashFunction);

/// @brief Deletes hash table.
/// @param Table Pointer to table struct.

void tableDestructor (table *Table);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif
