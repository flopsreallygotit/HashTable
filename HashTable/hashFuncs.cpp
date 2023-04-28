#include "hashFuncs.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

size_t constHash             (char *string)
{
    return 1;
}

size_t firstCharAsciiHash    (char *string)
{
    return (size_t) string[0];
}

size_t stringLengthHash      (char *string)
{
    return strlen(string);
}

size_t charSumHash           (char *string)
{
    size_t hash = 0;

    size_t symbol_idx = 0;

    while (string[symbol_idx] != '\0')
    {
        hash += (size_t) string[symbol_idx];

        symbol_idx++;
    }

    return hash;
}

// size_t rollingLeftHash       (char *string);

// size_t rollingRightHash      (char *string);

size_t polynomialRollingHash (char *string)
{
    static const size_t power = 53;

    size_t idx  = 0;
    size_t hash = 0;
    size_t currentPower = 1;

    while (string[idx] != '\0')
    {
        hash += (size_t) string[idx] * currentPower;

        currentPower *= power;
        idx++;
    }

    return hash;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
