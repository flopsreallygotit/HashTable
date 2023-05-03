#include "hashFuncs.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#pragma GCC diagnostic ignored "-Wunused-parameter"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

size_t constHash             (const char *string)
{
    return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

size_t firstCharAsciiHash    (const char *string)
{
    return (size_t) string[0];
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

size_t stringLengthHash      (const char *string)
{
    return strlen(string);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

size_t charSumHash           (const char *string)
{
    size_t hash = 0;

    for (size_t symbolIndex = 0; string[symbolIndex] != '\0'; symbolIndex++)
        hash += (size_t) string[symbolIndex];
    
    return hash;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

size_t rollingLeftHash       (const char *string)
{
    size_t hash = 0;

    for (size_t symbolIndex = 0; string[symbolIndex] != '\0'; symbolIndex++)
    {
        size_t firstPart  = hash << 1;
        size_t secondPart = hash >> 31;

        hash += (firstPart | secondPart) ^ (size_t) string[symbolIndex];
    }

    return hash;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

size_t rollingRightHash      (const char *string)
{
    size_t hash = 0;

    for (size_t symbolIndex = 0; string[symbolIndex] != '\0'; symbolIndex++)
    {
        size_t firstPart  = hash >> 1;
        size_t secondPart = hash << 31;

        hash += (firstPart | secondPart) ^ (size_t) string[symbolIndex];
    }

    return hash;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

size_t polynomialRollingHash (const char *string)
{
    static const size_t power = 53;

    size_t hash = 0;
    size_t currentPower = 1;

    for (size_t symbolIndex = 0; string[symbolIndex] != '\0'; symbolIndex++)
    {
        hash += (size_t) string[symbolIndex] * currentPower;

        currentPower *= power;
    }

    return hash;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
