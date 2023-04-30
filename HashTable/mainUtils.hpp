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
#include "textUtils.h"
#include "universalUtils.h"

#include "hashFuncs.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct table
{
    size_t tableSize = 0;
    size_t (*hashFunction) (elem_t element);

    list **listArray = NULL;
} table;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief  Create hash table
/// @param  tableSize Size of hash table / Number of lists array
/// @param  hashFunction Hash function for pasting, deletion and searching elements in table
/// @return Pointer to table struct

table *tableConstructor (size_t tableSize, 
                         size_t (*hashFunction) (char *string));

/// @brief Deletes table.
/// @param Table Pointer to table struct.
/// @param elementDestructor Function that deletes element.

void tableDestructor (table *Table, 
                      void (*elementDestructor) (elem_t element));

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Dumps all table lists.
/// @param Table Pointer to table struct.

void simpleTableDump (table *Table);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief  Inserts element in hash table.
/// @param  Table Pointer to table struct.
/// @param  element Element.
/// @return True if insert ended with success and false if element is already in table.

bool tableInsert (table *Table, elem_t element);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief  Creates list with words from file.
/// @param  filename Name of file.
/// @return List with words.

list *getFileWords (const char *filename);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Puts words in the file in hash table.
/// @param Words List of words.
/// @param Table Pointer to table struct.

ISERROR hashFileWords (list *Words, table *Table);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Outputs size of lists in file for subsequent processing.
/// @param filename Name of file.
/// @param Table Pointer to table struct.

ISERROR getStats (const char *filename, table *Table);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif
