# DString 
**Version:** 0.1 Alpha  
**Date:** 2024-07-19  
**Author:** Diego Moreira  
**License:** MIT  
**Compatibility:** C and C++

## Note
*It is important to note that the library is in its Alpha phase and still has some inconsistencies. At this time, it is not recommended for use in high-stakes projects.*

## Description 
DString is a safer and more functional alternative to the standard C library "string.h". Its goal is to provide enhanced string manipulation functionalities similar to higher-level languages like JavaScript and Java.

## Features
- Safe string length calculation
- Buffer overflow prevention features
- String comparison with error checking
- Enhanced string filling and copying functionality

## Usage
Include the header in your C project:
```c
#include "dstring.h"
```

## Dependencies
- **Dtypes**: available [here](https://github.com/diegomoreira2/dtypes)

## Macros
### size
*Calculates the size in bytes of an array regardless of type*  
**Return:** `size_t`

Usage examples:
```c
char foo[10];
int x[34];

size(foo); // 10
size(x); // 34
```

## Functions

### Initialization
*Before using the functions in your project, you must call the `init_dstring_h()` function to initialize.*

### str.len
**Alternative to `strlen`:** Calculates the length of a string.  
**Arguments:** `(u8 *)`  
**Return:** `u64` aka `uint64_t`

Usage examples:
```c
str.len(NULL); // 0
str.len((u8 *)""); // 0
```

```c
u8 foo[] = "I am using Dstring!\n";
str.len((u8 *)"Test"); // 4
str.len(foo); // 20
// Note: "u8 *" is "uint8_t *"
```

### str.tlen
**Alternative to `strlen`:** Calculates the length of a string, counting all non-null bytes.  
**Arguments:** `(u8 *, size_t)`  
**Return:** `u64` aka `uint64_t`

Usage examples:

```c
u8 foo[10];
foo[5] = 'A';
foo[8] = 'B';
foo[3] = 'C';

strlen(foo); // 0
str.len(foo); // 0

str.tlen(foo, size(foo)); // 3
```

```c
u8 foo[] = "\0ok\0test";
str.tlen(foo, size(foo)); // 6

str.tlen(NULL); // 0
```

### str.cmp
**Alternative to `strcmp`:** Compares two strings and returns different types of flags.  
**Arguments:** `(u8 *, u8 *)`  
**Return:** `i64` aka `int64_t`

Usage examples:

```c
u8 str1[25] = "I am using Dstring!";
u8 str2[50] = "I am using Dstring!";

str.cmp(str1, str2); // 0
```

```c
str.cmp(NULL, NULL); // 0
str.cmp((u8 *)"", (u8 *)""); // 0
```

```c
u8 foo[10] = "Example";
u8 foo2[24] = "";

str.cmp(NULL, foo); // -1
str.cmp(foo, NULL); // -2

str.cmp(foo2, foo); // -3 (First string is empty)
str.cmp(foo, foo2); // -4 (Second string is empty)
```

```c
u8 foo[50] = "Example";
u8 foo2[34] = "Example 2";

str.cmp(foo2, foo); // -5 (First string is longer)
str.cmp(foo, foo2); // -6 (Second string is longer)
```

```c
u8 foo[] = "1236";
u8 foo2[] = "1234";

u8 test1[] = "1 Example 1";
u8 test2[] = "2 Example 2";

str.cmp(foo, foo2); // 1 (Number of differences)
str.cmp(test1, test2); // 2 (Number of differences)
```

### str.icmp
**Alternative to `strncmp`:** Compares a range of two strings and returns different types of flags.  
**Arguments:** `(u8 *, u8 *, u64, u64)`  
**Return:** `i64` aka `int64_t`

Usage examples:
```c
u8 foo[] = "Lib";
u8 foo2[] = "Library";

str.icmp(foo, foo2, 0, 2); // 0

u8 foo3[] = "The Example";
u8 foo4[] = "??? Example";

str.icmp(foo3, foo4, 3, 10); // 0
```

```c
u8 foo[] = "Ok";

str.icmp(NULL, NULL, 0, 4); // -1 (Both strings are NULL)
str.icmp(NULL, foo, 0, 2); // -2 (First string is NULL)
str.icmp(foo, NULL, 0, 2); // -3 (Second string is NULL)

str.icmp((u8 *)"", (u8 *)"", 0, 1); // -4 (Both strings are empty)
```

```c
u8 foo[] = "?String";
u8 foo2[] = "DString";

str.icmp(foo, foo2, 10, 34); // -5 (Invalid start index)

str.icmp(foo, foo2, 1, 100); // 0 (Note: The function corrects end index errors)
```

### str.fill
**Alternative to `memset`:** Fills a string with a specific character.  
**Arguments:** `(u8 *, u8, size_t)`  
**Return:** `u32` aka `uint32_t`

Usage examples:
```c
u8 foo[100];

str.fill(foo, 0, size(foo)); // Initializes the string with null bytes
```

```c
u8 foo[40];

str.fill(foo, 'A', size(foo)); // foo = "AAAA...\0" (Note: str.fill appends a null byte)
```
