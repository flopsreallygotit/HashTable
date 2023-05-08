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

We have already selected hash function, so now we need to consider ways to speed up hash table. 

We will use **valgrind** with **callgrind** tool and **kcachegrind** for callgrind output vizualizing ([Documentation](https://kcachegrind.sourceforge.net/html/Documentation.html)).

P.S. All measurements are made 4 times for better accuracy.

### Baseline

Let's take a look at baseline.

| Version  | Time         | Absolute speedup | Relative speedup |
| :------: | :----------: | :--------------: | :--------------: |
| Baseline | 4.11 +- 0.03 | 1                | 1                |

Kcachegrind output:

<img src = Data/baseline.png>

First we will try to use compiler optimization *-O2*, to boost our perfomance.

### Compiler optimization -O2

| Version  | Time           | Absolute speedup | Relative speedup |
| :------: | :------------: | :--------------: | :--------------: |
| Baseline | 4.11  +- 0.03  | 1                | 1                |
| -O2      | 2.675 +- 0.019 | 1.54             | 1.54             |

Profiler data:

<img src = Data/-o2.png>

As we see from profiler **__strcmp_avx2** is on first place in Self rating. So we need to optimize the element compare function (*strcmp*) to improve performance.

### 1 assembler optimization

Optimizing strcmp with inline assembler:

<details>
<summary> <b> Code </b> </summary>

```C++
int strcmpASM (const char *string1, const char *string2)
{
    int result = 0;

    asm volatile 
    (
        ".intel_syntax noprefix;"

        "1:"
        "lodsb;"
        "scasb;"
        "jne 2f;"

        "test al, al;"
        "jne 1b;"

        "xor eax, eax;"
        "jmp 3f;"

        "2:"
        "dec edi;"
        "sbb eax, eax;"

        "3:"
        ".att_syntax" 
        : "=a" (result)
        : "S" (string1), "D" (string2)
        : "memory"
    );

    return result;
}
```

</details>

| Version    | Time             | Absolute speedup | Relative speedup |
| :--------: | :--------------: | :--------------: | :--------------: |
| Baseline   | 4.11  +- 0.03    | 1                | 1                |
| -O2        | 2.675 +- 0.019   | 1.54             | 1.54             |
| first opt. | 0.4865 +- 0.0011 | 8.45             | 5.5              |

Profiler data:

<img src = Data/-o2+strcmpASM.png>

We see that our hash function is bottleneck now. Let's try to use our own hash function rewrited on assembler.

### 2 assembler optimization **(fail)**

| Version     | Time             | Absolute speedup | Relative speedup |
| :--------:  | :--------------: | :--------------: | :--------------: |
| Baseline    | 4.11  +- 0.03    | 1                | 1                |
| -O2         | 2.675 +- 0.019   | 1.54             | 1.54             |
| first opt.  | 0.4865 +- 0.0011 | 8.45             | 5.5              |
| second opt. | 0.6185 +- 0.0025 | 6.65             | 0.77             |

Profiler data:

<img src = Data/-o2+strcmpASM+hashFunctionASM.png>

Let's see this:

<details>
<summary> <b> Code </b> </summary>

```ASM
global polynomialRollingHashASM

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Pollynomial Rolling Hash Function on x86-64 asm
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Entry:    RDI = Address of string
; Exit:     RAX = Hash value
; Destroys: None
; Expects:  Constant number 'Power'
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

polynomialRollingHashASM:  
        push rdi    ; Saving registers values
        push rbx
        push rcx
        push rdx
        push r8
        push r9

        mov rax, 1      ; Moving 1 to register for current power
        mov r8, Power   ; Moving power to register

        xor rbx, rbx    ; Zeroing register for current symbol
        xor rcx, rcx    ; Zeroing register for hash

.next:  mov bl, byte [rdi]  ; Loading current symbol in BL
        test bl, bl         ; Checking that current symbol != '\0'
        jz .end

        mov r9, rax         ; Saving current power

        mul rbx             ; Mulling current power and current symbol
        add rcx, rax        ; Adding that value to hash

        mov rax, r9         ; Restoring current power

        mul r8              ; Increasing power
        inc rdi             ; Going to next symbol
        jmp .next           ; Going to next iteration

.end:   mov rax, rcx    ; Saving hash value to RAX

        pop  r9         ; Restoring registers values
        pop  r8
        pop  rdx 
        pop  rcx
        pop  rbx
        pop  rdi 

        ret
```

As we can see this function slows down our program and profiler shows that it is still a bottleneck. Let's try to use AVX instructions for hash function optimization.

### 3 assembler optimization

| Version     | Time             | Absolute speedup | Relative speedup |
| :--------:  | :--------------: | :--------------: | :--------------: |
| Baseline    | 4.11  +- 0.03    | 1                | 1                |
| -O2         | 2.675 +- 0.019   | 1.54             | 1.54             |
| first opt.  | 0.4865 +- 0.0011 | 8.45             | 5.5              |
| second opt. | 0.6185 +- 0.0025 | 6.65             | 0.77             |
| third opt.  | 0.437 +- 0.008   | 9.41             | 1.42             |

Profiler data:

<img src = Data/-o2+strcmpASM+hashFunctionAVX.png>

<details>
<summary> <b> Code </b> </summary>

```ASM
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; crc32 on x86-64 asm + AVX2
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Entry:    RDI = Address of string
; Exit:     RAX = Hash value
; Destroys: None
; Expects:  None
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

global crc32AVX

crc32AVX:       xor rax, rax                    ; Zero register for hash

                crc32 rax, qword [rdi + 0 * 8]  ; Counting hash
                crc32 rax, qword [rdi + 1 * 8]
                crc32 rax, qword [rdi + 2 * 8]
                crc32 rax, qword [rdi + 3 * 8]

                ret
```

</details>

In this optimization loop we replaced polynomial rolling hash function with crc32 hash function ([Intel Intrinsics Guide](https://www.laruence.com/sse/#text=crc32&expand=1286,1287,1288,1289)). Speedup relatively 1 optimization is 1.11 it isn't too much and according to profiler the bottleneck now is list search function, so we won't continue optimizing.

# Conclusion

It turns out, that not every optimization speeds up the program, sometimes it only slows it down. (c) [Dodokek](https://github.com/dodokek)

Ded's coefficient is 409

<img src = Data/ded.png>
