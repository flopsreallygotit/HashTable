#pragma once

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <stddef.h>
#include <string.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Hash functions for table:

/// @brief Always returns 1.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t constHash             (char *string);

/// @brief Returns ascii code of first symbol of string.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t firstCharAsciiHash    (char *string);

/// @brief Returns length of string.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t stringLengthHash      (char *string);

/// @brief Returns sum of symbols ASCII codes.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t charSumHash           (char *string);

/// @brief Performs code rotation to the left and xors that value with current symbol.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t rollingLeftHash       (char *string);

/// @brief Performs code rotation to the right and xors that value with current symbol.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t rollingRightHash      (char *string);

/// @brief Polynomial rolling hash C implementation.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t polynomialRollingHash (char *string);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
