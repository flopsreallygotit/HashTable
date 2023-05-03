#pragma once

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <stddef.h>
#include <string.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Always returns 1.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t constHash             (const char *string);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Returns ascii code of first symbol of string.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t firstCharAsciiHash    (const char *string);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Returns length of string.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t stringLengthHash      (const char *string);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Returns sum of symbols ASCII codes.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t charSumHash           (const char *string);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Performs code rotation to the left and xors that value with current symbol.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t rollingLeftHash       (const char *string);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Performs code rotation to the right and xors that value with current symbol.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t rollingRightHash      (const char *string);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// @brief Polynomial rolling hash C implementation.
/// @param string Default zero terminated string.
/// @return Index of string in table.

size_t polynomialRollingHash (const char *string);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
