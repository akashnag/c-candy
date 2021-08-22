String Iterator
=====================
Header: `c-candy/striterator.h`

Version 0.1.0-alpha

&copy; Copyright 2021, Akash Nag. Distributed under GPL v2.0.

This is the documentation page for all functions and constants defined by the c-candy String Iterator library. The type `STR_ITERATOR` is an implementation of a String Iterator.

### Struct types

The base type `STR_ITERATOR` is defined as follows:

```c
typedef struct {
	STRING *data;
	int marker;
} STRING_ITERATOR;
```

### Constants

| Constant | Value | Description |
|-|-|-|
| STRI_BOS | 0 | Denotes the beginning of the string |
| STRI_EOS | -1 | Denotes the end of the string |


### Functions

| Return type | Signature | Description |
|-|-|-|
| void | stri_dump(STRING_ITERATOR *s) | Frees memory allocated for the string iterator |
| STRING_ITERATOR* | stri_cs(const char *s) | Creates a String Iterator object from a C-Style char buffer |
| STRING_ITERATOR* | stri(const STRING *s) | Creates a String Iterator object from a C-Candy String |
| char | stri_this(const STRING_ITERATOR *s) | Returns the character at the current head position |
| char | stri_next(const STRING_ITERATOR *s) | Returns the character to the right of the current head position |
| char | stri_prev(const STRING_ITERATOR *s) | Returns the character to the left of the current head position |
| int | stri_pos(const STRING_ITERATOR *s) | Returns the current head position |
| BOOL | stri_move_next(STRING_ITERATOR *s) | Moves the head one character to the right |
| BOOL | stri_move_prev(STRING_ITERATOR *s) | Moves the head one character to the left |
| BOOL | stri_move(STRING_ITERATOR *s, int num_chars) | Moves the head a given number of characters (positive: right, negative: left) |
| BOOL | stri_skip(STRING_ITERATOR *s, unsigned int num_chars) | Moves the head right skipping a given number of characters |
| BOOL | stri_reset(STRING_ITERATOR *s) | Brings the head to the beginning of the string |
| BOOL | stri_move_bos(STRING_ITERATOR *s) | Alias for `stri_reset` |
| BOOL | stri_move_eos(STRING_ITERATOR *s) | Moves the head to the end of the string |
| int | stri_move_until(STRING_ITERATOR *s, const char *chars, int step) | Moves the head until a given character is encountered; moving `step` characters each time |
| int | stri_move_while(STRING_ITERATOR *s, const char *chars, int step) | Moves the head as long as the given character is under the head, moving `step` characters each time |
| BOOL | stri_is_at_eos(const STRING_ITERATOR *s) | Returns TRUE if the head is at the end of the string |
| BOOL | stri_is_at_bos(const STRING_ITERATOR *s) | Returns TRUE if the head is at the beginning of the string |
| BOOL | stri_is_at(const STRING_ITERATOR *s, int position) | Returns TRUE if the head is at the given position |
