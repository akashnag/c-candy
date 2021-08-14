Strings
=====================
Header: `c-candy/str.h`

Version 0.1.0-alpha

&copy; Copyright 2021, Akash Nag. Distributed under GPL v2.0.

This is the documentation page for all functions and constants defined by the c-candy String library.

### Constants

| Name | Value |
|-|-|
| `STR_SIZE` | Size of a STRING type |

### Struct types

The base type `STRING` is defined as follows:

```c
typedef struct {
	char *data;
	int length;
} STRING;
```

### Functions

| Return type | Signature | Description |
|-|-|-|
| `STRING*` | `str(const char *s)` | Creates a string object from a C-style null-terminated string buffer |
| `STRING*` | `str_blank()` | Creates an empty string object |
