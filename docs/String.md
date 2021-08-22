Strings
=====================
Header: `c-candy/str.h`

Version 0.1.0-alpha

&copy; Copyright 2021, Akash Nag. Distributed under GPL v2.0.

This is the documentation page for all functions and constants defined by the c-candy String library. The type `STRING` is an implementation of a mutable String.

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
| void | str_dump(STRING *sobj) | Frees memory allocated for a string object |
| STRING* | str_blank() | Creates an empty string |
| STRING* | string(const char *s) | Creates a String object from a C-style char buffer |
| STRING* | str_copy(const STRING *s) | Returns a copy of a string |
| unsigned int | str_len(const STRING* sobj) | Returns the number of characters in the string |
| char* | cstr(const STRING *sobj) | Returns a C-style char buffer representation of a string object |
| BOOL | str_is_char_in(const STRING *sobj, char c) | Returns TRUE if the given character exists in the string |
| BOOL | str_append(STRING *sobj, const STRING *suffix) | Appends string to the end of another string |
| BOOL | str_insert(STRING *sobj, int index, const STRING *ins_str) | Inserts a string at a given index in another string |
| BOOL | str_replace_part(STRING *sobj, int start, int end, const STRING *ins_str) | Replaces a part of a string with another string |
| STRING* | str_replace_first(const STRING *sobj, const STRING *find, const STRING *replace_with) | Replaces the first occurrence of a string with another string in a given string |
| STRING* | str_replace_all(const STRING *sobj, const STRING *find, const STRING *replace_with) | Replaces all non-overlapping occurrences of a string with another string in a given string |
| STRING* | str_reverse(const STRING *sobj) | Returns a reversed-copy of a string |
| STRING* | str_center(const STRING *sobj, unsigned int length, char pad_char) | Aligns a string to the center by padding characters to both ends |
| STRING* | str_ljust(const STRING *sobj, unsigned int length, char pad_char) | Left-justifies a string by padding characters to the right |
| STRING* | str_rjust(const STRING *sobj, unsigned int length, char pad_char) | Right justifies a string by padding characters to the left |
| STRING* | str_strip(const STRING *sobj) | Removes any leading and trailing whitespaces from a string |
| STRING* | str_lstrip(const STRING *sobj) | Removes any leading whitespaces from a string |
| STRING* | str_rstrip(const STRING *sobj) | Removes any trailing whitespaces from a string |
| char | str_char_at(const STRING *sobj, int index) | Returns the character at the given index |
| int | str_count(const STRING *sobj, const STRING *match) | Returns the count of the number of times a given string is found in another string |
| BOOL | str_starts_with(const STRING *sobj, const STRING *prefix) | Returns TRUE if the string starts with a specified prefix |
| BOOL | str_ends_with(const STRING *sobj, const STRING *suffix) | Returns TRUE if the string ends with a specified suffix |
| int | str_find(const STRING *sobj, const STRING *match) | Returns the first index at which a given string is found; or -1 if not found |
| int str_find_all(const STRING *sobj, const STRING *match, unsigned int *indices) | Returns the number of times a string is found in another string, and puts the indices as an array in the `indices` parameter |
| int | str_find_within(const STRING *sobj, const STRING *match, int start, int end) | Returns the first index at which a string is found within a portion of another string |
| int | str_rfind(const STRING *sobj, const STRING *match) | Returns the first index (from right) at which a string is found; or -1 if not found |
| int | str_rfind_within(const STRING *sobj, const STRING *match, int start, int end) | Returns the first index (from right) at which a string is found within a portion of another string |
| BOOL | str_is_alphanumeric(const STRING *sobj) | Returns TRUE if the string contains only alpanumeric characters |
| BOOL | str_is_alpha(const STRING *sobj) | Returns TRUE if the string contains only alphabetic characters |
| BOOL | str_is_decimal(const STRING *sobj) | Returns TRUE if the string only contains digits |
| BOOL | str_is_whitespace(const STRING *sobj) | Returns TRUE if the string only contains whitespaces |
| BOOL | str_is_upper(const STRING *sobj) | Returns TRUE if a string is in uppercase |
| BOOL | str_is_lower(const STRING *sobj) | Returns TRUE if a string is in lowercase |
| STRING* | str_substring(const STRING *sobj, int start, int end) | Returns a portion of a given string |
| STRING* | str_to_upper(const STRING *sobj) | Converts a string to uppercase |
| STRING* | str_to_lower(const STRING *sobj) | Converts a string to lowercase |
| STRING** | str_split(const STRING *sobj, const char *delimiter, int max_split, int *split_count) | Splits a string using a given delimiter string |
| STRING** | str_split_whitespace(const STRING *sobj, int max_split, int *split_count) | Splits a string using space |
| STRING* | str_zfill(const STRING *sobj, unsigned int length) | Pads a string with zeroes to the left |
| STRING* | str_swap_case(const STRING *sobj) | Toggles the case of the characters in the string |
| STRING* | str_title(const STRING *sobj) | Converts a string into titlecase |
| STRING* | str_chop(const STRING *sobj, unsigned int num_chars_left, unsigned int num_chars_right) | Removes a certain number of characters from the left and right of a string |
| BOOL | str_equals(const STRING *sobj1, const STRING *sobj2) | Returns TRUE if two strings are identical |
| BOOL | str_equals_ignore_case(const STRING *sobj1, const STRING *sobj2) | Returns TRUE if two strings are equal ignoring uppercase and lowercase distinctions |
| int | str_compare(const STRING *sobj1, const STRING *sobj2) | Compares two strings; returns 0 if equal |
| int | str_compare_ignore_case(const STRING *sobj1, const STRING *sobj2) | Compares two strings ignoring case; returns 0 if equal |
| BOOL | str_is_empty(const STRING *sobj) | Returns TRUE if a string is empty |
| STRING* | str_expand_tabs(const STRING *sobj, unsigned int tab_size) | Replaces tabs in a string with a specified number of whitespaces |
| STRING* | str_cfmt(int max_len, const char *format, ...) | Formats arguments and converts it into a C-Candy string |
| unsigned long long | str_hash(const STRING *sobj) | Returns the hash of the given string |

