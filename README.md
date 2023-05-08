# Hash Table

For average hash table enjoyers.

# Overview

**Goals of this project:**
- Investigate hash functions on number of collisions and choose the best of them;
- Implement different types of assembly optimizations to speed up the searching function

**Technical parameters:**

- **CPU**: Intel Core i5 11300H (AVX instructions: AVX-512)
- **Compiler**: g++
- **Table size:** 1009
- **Keys:** Words of __"The adventures of Sherlock Holmes"__ (*41935* words)
- **Utilities:** Valgrind, Callgrind, Kcachegring

P.S. During the research, the CPU was not trotled. Average room temperature was 21 degrees.

# Theory reference

A hash table is a data structure that uses a hash function to keep track of where data is put. Each piece of information to be stored has a name, which is called a key. Each name is matched up to one piece of data called a value.

There is always a possibility that two keys will have the same hash. This is called collision. So we are going to use chain method to avoid it. More information about it can be found here: [Click!](https://www.geeksforgeeks.org/separate-chaining-collision-handling-technique-in-hashing/)

It looks like:

<img src = Data/hashTable.png>

It is also important to mention that size of hash table is a prime number (*1009*), because on bad hash functions distribution will be better: [Why is it so?](https://ru.stackoverflow.com/questions/1470263/%D0%9E%D0%B1%D1%8F%D0%B7%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE-%D0%BB%D0%B8-%D0%B4%D0%B5%D0%BB%D0%B0%D1%82%D1%8C-%D0%BC%D0%B0%D0%BA%D1%81%D0%B8%D0%BC%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B9-%D1%80%D0%B0%D0%B7%D0%BC%D0%B5%D1%80-%D1%85%D1%8D%D1%88-%D1%82%D0%B0%D0%B1%D0%BB%D0%B8%D1%86%D1%8B-%D0%BF%D1%80%D0%BE%D1%81%D1%82%D1%8B%D0%BC-%D1%87%D0%B8%D1%81%D0%BB%D0%BE%D0%BC)

# First part. Choose your fighter.

It’s obvious that the *more* collisions we have - the *slower* search of values we'll get. So we need to select the function with the least number of collisions of these:

### 1) constHash

This wonderful function always gives the same value on different keys:

```C++
size_t constHash (const char *string)
{
    return 1;
}
```

<details>
<summary> <b> Distribution </b> </summary>
<img src = Data/constHash.png>
</details>

Kinda fun, but it's the worst hash function I can imagine...

### 2) firstCharAsciiHash
Returns ASCII code of string's first symbol:

```C++
size_t firstCharAsciiHash (const char *string)
{
    return (size_t) string[0];
}
```

<details>
<summary> <b> Distribution </b> </summary>
<img src = Data/firstCharAsciiCodeHash.png>
</details>

This function is better than previous and it can be used on small text. However, the large text doesn't give a chance to it.

### 3) stringLengthHash
Returns length of string:

```C++
size_t stringLengthHash (const char *string)
{
    return strlen(string);
}
```

<details>
<summary> <b> Distribution </b> </summary>
<img src = Data/stringLengthHash.png>
</details>

We have even more collisions on that function. English words are not very long as we can see.

### 4) charSumHash
Returns sum of symbols ASCII codes:

```C++
size_t charSumHash (const char *string)
{
    size_t hash = 0;

    for (size_t symbolIndex = 0; string[symbolIndex] != '\0'; symbolIndex++)
        hash += (size_t) string[symbolIndex];
    
    return hash;
}
```

<details>
<summary> <b> Distribution </b> </summary>
<img src = Data/charAsciiCodesSumHash.png>
</details>

Dispersion became slightly better (~*250*).

### 5) ROL Hash
For average left Twix stick enjoyers:

```C++
size_t rollingLeftHash (const char *string)
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
```

<details>
<summary> <b> Distribution </b> </summary>
<img src = Data/rolHash.png>
</details>

Less dispersion - more search speed! (More speed to the God of the speed u-ha-ha-ha)

### 6) ROR Hash
For average right Twix stick enjoyers:

```C++
size_t rollingRightHash (const char *string)
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
```

<details>
<summary> <b> Distribution </b> </summary>
<img src = Data/rorHash.png>
</details>

Interesting result: ROR's Dispersion is less than the ROL's Dispersion by ~*6* times. Usually the ROL's results are better. Apparently the sample has a big impact.

### 7) polynomialRollingHash
Based hash function for string hashing:

```C++
size_t polynomialRollingHash (const char *string)
{
    static const size_t power = 53; // Good value for letters in upper and lower cases

    size_t hash = 0;
    size_t currentPower = 1;

    for (size_t symbolIndex = 0; string[symbolIndex] != '\0'; symbolIndex++)
    {
        hash += (size_t) string[symbolIndex] * currentPower;

        currentPower *= power;
    }

    return hash;
}
```

<details>
<summary> <b> Distribution </b> </summary>
<img src = Data/polynomialRollingHash.png>
</details>

It gives dispersion about ~*42*. Bingo! I will use this hash function for the next part, because it has a great potential for optimizations and small dispersion.

# Second part. Optimizations.

### Baseline


