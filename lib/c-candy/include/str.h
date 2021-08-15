/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/include/str.h
 *
 * (C) Copyright 2021 Akash Nag
 *
 * This program is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this
 * program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

/* start of include guard */
#ifndef STR_H

#define STR_H

#include <constants.h>

/* other constants */
#define STR_SIZE 						sizeof(STRING)

#ifdef __cplusplus
extern "C" {
#endif

/* definition of STRING object */
typedef struct {
	char *data;
	unsigned int length;
} STRING;

/* <------------------------------ function declarations --------------------------------> */

/*
 * dump_str() -	Frees memory allocated for the string object
 * @sobj:		the string to free
 */
void dump_str(STRING *sobj);

/*
 * str_blank() - Creates a blank string
 *
 * Returns a pointer to a new STRING object
 */
STRING* str_blank();

/*
 * str() - 	Converts a string literal to a STRING object
 * @s: 		string literal to convert
 *
 * Returns a pointer to a STRING object
 */
STRING* str(const char *s);

/*
 * str_copy() -	Returns a copy of the given string
 * @s: 			the string object to copy
 *
 * Returns a copy of the STRING object
 */
STRING* str_copy(const STRING *s);

/*
 * str_len() - 	Computes the length of a string
 * @sobj: 		string object whose length is to be returned
 *
 * Returns the length in number of characters of a string object
 */
unsigned int str_len(const STRING* sobj);

/*
 * cstr() - Converts STRING object to a C-style string constant
 * @sobj: 	the string object to convert
 *
 * Returns a C-style string constant
 */
char* cstr(const STRING *sobj);

/*
 * str_is_char_in() -	Checks if a character is in the string
 * @sobj: 				the string to check in
 * @c:					the character to search for
 *
 * Returns TRUE if the character is in the given string
 */
BOOL str_is_char_in(const STRING *sobj, char c);

/*
 * str_append() - 	Appends a suffix to the end of the given string and modifies it in-place
 * @sobj: 			the string to append to (modified in-place)
 * @suffix: 		the string to append
 *
 * Returns TRUE if successful
 */
BOOL str_append(STRING *sobj, const STRING *suffix);

/*
 * str_insert() - 	Inserts a string into the given string at the specified index
 * @sobj: 			the string to insert into (modified in-place)
 * @index: 			the position to insert at
 * @ins_str: 		the string to insert
 *
 * Returns TRUE if successful
 */
BOOL str_insert(STRING *sobj, int index, const STRING *ins_str);

/*
 * str_replace_part() -	Replaces a portion of the given string with another string
 * @sobj:				the string in which to replace (modified in-place)
 * @start:				the index to start replacement at (inclusive)
 * @end:				the index to stop replacement at (exclusive)
 * @ins_str:			the string to replace with
 *
 * Returns TRUE if successful
 */
BOOL str_replace_part(STRING *sobj, int start, int end, const STRING *ins_str);

/*
 * str_replace_first() - 	Replaces the first occurrence of a string with another string in the given string
 * @sobj:					the string to replace in
 * @find:					the string to find
 * @replace_with:			the string to replace with
 *
 * Returns the modified string
 */
STRING* str_replace_first(const STRING *sobj, const STRING *find, const STRING *replace_with);

/*
 * str_replace_all() -	Replaces all occurrences of a string with another string in the given string
 * @sobj:				the string to replace in
 * @find:				the string to find
 * @replace_with:		the string to replace with
 *
 * Returns the modified string
 */
STRING* str_replace_all(const STRING *sobj, const STRING *find, const STRING *replace_with);

/* 
 * str_reverse() -	Reverses a string
 * @sobj: 			the string to reverse
 *
 * Returns a reversed copy of the given string
 */
STRING* str_reverse(const STRING *sobj);

/*
 * str_center() -	Centers a string within a fixed-width by padding on boths sides with a given padding character
 * @sobj:			the string to justify
 * @length:			the width to maintain (if not evenly divisible, pads 1 more on right)
 * @pad_char:		the character to pad with
 *
 * Returns the center-justified string
 */
STRING* str_center(const STRING *sobj, unsigned int length, char pad_char);

/*
 * str_ljust() -	Left justifies a string in a fixed-width column by padding on the right with a given character
 * @sobj:			the string to justify
 * @length:			the width to maintain
 * @pad_char:		the character to pad with
 *
 * Returns the left-justified string
 */
STRING* str_ljust(const STRING *sobj, unsigned int length, char pad_char);

/*
 * str_rjust() -	Right justifies a string in a fixed-width column by padding on the left with a given character
 * @sobj:			the string to justify
 * @length:			the width to maintain
 * @pad_char:		the character to pad with
 *
 * Returns the right-justified string
 */
STRING* str_rjust(const STRING *sobj, unsigned int length, char pad_char);

/*
 * str_strip()	-	Removes any leading and trailing whitespaces from a string
 * @sobj:			the string to strip
 *
 * Returns the stripped string
 */
STRING* str_strip(const STRING *sobj);

/*
 * str_lstrip() - 	Removes any leading whitespaces from a string
 * @sobj:			the string to strip
 *
 * Returns the stripped string
 */
STRING* str_lstrip(const STRING *sobj);

/*
 * str_rstrip() -	Removes any trailing whitespaces from a string
 * @sobj:			the string to strip
 *
 * Returns the stripped string
 */
STRING* str_rstrip(const STRING *sobj);

/*
 * str_char_at() -	Returns the character at a given index
 * @sobj: 			the string to extract from
 * @index: 			the position of the character to extract
 *
 * Returns the character in the string at the given index
 */
char str_char_at(const STRING *sobj, int index);

/*
 * str_cfmt() -	Returns the string representation of a format string
 * @max_len		expected maximum length of the string
 * @format:		the format string
 * ...			0 or more arguments
 *
 * Returns a string representation of the arguments
 */
STRING* str_cfmt(int max_len, const char *format, ...);

/* 
 * str_count() - 	Counts the number of occurrences of a string in another string
 * @sobj:			the string to find in
 * @match:			the string to match with
 *
 * Returns a count of the number of matches found
 */
int str_count(const STRING *sobj, const STRING *match);

/*
 * str_starts_with() -	Checks if a string has another string as prefix
 * @sobj: 				the string to check in
 * @prefix: 			the string to check for
 *
 * Returns TRUE if 'prefix' occurs as a prefix to 'sobj', else FALSE
 */
BOOL str_starts_with(const STRING *sobj, const STRING *prefix);

/*
 * str_ends_with() -	Checks if a string has another string as suffix
 * @sobj: 				the string to check in
 * @suffix: 			the string to check for
 *
 * Returns TRUE if 'suffix' occurs as a suffix to 'sobj', else FALSE
 */
BOOL str_ends_with(const STRING *sobj, const STRING *suffix);

/*
 * str_expand_tabs() -	Replaces each tab with a given number of spaces
 * @sobj: 				the string to check for tabs
 * @tab_size: 			the number of spaces to replace each tab with
 *
 * Returns the expanded string
 */
STRING* str_expand_tabs(const STRING *sobj, unsigned int tab_size);

/*
 * str_find() -	Finds the index of the first occurrence of a string in another string
 * @sobj:		the string to search in
 * @match:		the string to search for
 *
 * Returns the index of the first match, or -1 if no matches are found
 */
int str_find(const STRING *sobj, const STRING *match);

/*
 * str_find_all() - Finds the indices of all occurrences of a string in another string
 * @sobj:			the string to search in
 * @match:			the string to search for
 * @indices:		empty pointer where the match indices will be stored
 *
 * Returns the number of occurrences found; stores the match indices in 'indices' array
 */
int str_find_all(const STRING *sobj, const STRING *match, unsigned int *indices);

/*
 * str_find_within() - 	Finds the first occurrence of a string in a portion of another string
 * @sobj:				the string to search in
 * @match:				the string to search for
 * @start:				the position to start the search at (inclusive)
 * @end:				the position to end the search at (exclusive)
 *
 * Returns the index of the first match, or -1 if no matches are found
 */
int str_find_within(const STRING *sobj, const STRING *match, int start, int end);

/*
 * str_rfind() - 	Finds the index of the last occurrence of a string in another string
 * @sobj:			the string to search in
 * @match:			the string to search for
 *
 * Returns the index of the last match, or -1 if no matches are found
 */
int str_rfind(const STRING *sobj, const STRING *match);

/*
 * str_rfind_within() -	Finds the index of the last match of a string in a portion of another string
 * @sobj:				the string to search in
 * @match:				the string to search for
 * @start:				the index to start the search at (inclusive)
 * @end:				the index to end the search at (exclusive)
 *
 * Returns the index of the last match, or -1 if no matches are found
 */
int str_rfind_within(const STRING *sobj, const STRING *match, int start, int end);

/* 
 * is_alphanumeric() - 	Checks if a string contains only alphanumeric characters
 * @sobj: 				the string to check
 *
 * Returns TRUE if the string contains only alphanumeric characters (A-Z, a-z, 0-9)
 */
BOOL str_is_alphanumeric(const STRING *sobj);

/* 
 * is_alpha() - Checks if a string contains only alphabetic characters
 * @sobj: 		the string to check
 *
 * Returns TRUE if the string contains only alphabetic characters (A-Z, a-z)
 */
BOOL str_is_alpha(const STRING *sobj);

/* 
 * is_decimal() -	Checks if a string contains only numeric characters
 * @sobj: 			the string to check
 *
 * Returns TRUE if the string contains only numeric characters (0-9)
 */
BOOL str_is_decimal(const STRING *sobj);

/*
 * is_whitespace() -	Checks if a string contains only whitespaces
 * @sobj: 				the string to check
 *
 * Returns TRUE if the string contains only whitespaces (\t, \r, \n, \v, \f or space)
 */
BOOL str_is_whitespace(const STRING *sobj);

/*
 * is_upper() - Checks if a string contains no lowercase characters
 * @sobj: 		the string to check
 *
 * Returns FALSE if the string contains any lowercase characters (a-z)
 */
BOOL str_is_upper(const STRING *sobj);

/*
 * is_lower() - Checks if a string contains no uppercase characters
 * @sobj: 		the string to check
 *
 * Returns FALSE if the string contains any uppercase characters (A-Z)
 */
BOOL str_is_lower(const STRING *sobj);

/* 
 * substring() - 	Extracts a portion of a given string from index 'start' to 'end'-1
 * @sobj: 			the string from which to extract
 * @start: 			the index to start extraction from (inclusive)
 * @end: 			the index to stop extraction at (exclusive)
 *
 * Returns a new string containing the extracted portion
 */
STRING* str_substring(const STRING *sobj, int start, int end);

/*
 * upper() - 	Converts a string to uppercase
 * @sobj: 		the string object to convert
 *
 * Returns the original string converted to uppercase
 */
STRING* str_to_upper(const STRING *sobj);

/*
 * lower() - 	Converts a string to lowercase
 * @sobj: 		the string object to convert
 *
 * Returns the original string converted to lowercase
 */
STRING* str_to_lower(const STRING *sobj);

/*
 * str_split() -	Splits a string into a number of parts based on some delimiter
 * @sobj:			the string to split
 * @delimiter:		the string to be used as delimiter
 * @max_split:		the maximum number of splits to make, use -1 to get all splits
 * @parts:			pointer to an array of strings where the resultant parts will be stored
 *
 * Returns the number of splits actually made
 */
int str_split(const STRING *sobj, const char *delimiter, int max_split, STRING **parts);

/*
 * str_split_whitespace() -	Splits a string into a number of parts using any whitespace as delimiter
 * @sobj:					the string to split
 * @max_split:				the maximum number of splits to make, use -1 to get all splits
 * @parts:					pointer to an array of strings where the resultant parts will be stored
 *
 * Returns the number of splits actually made
 */
int str_split_whitespace(const STRING *sobj, int max_split, STRING **parts);

/* 
 * zfill() -	Pads a string with zeroes on the left
 * @sobj: 		the string to pad
 * @length: 	the intended total length of the string (including the padding)
 *
 * Returns the zero-padded string
 */
STRING* str_zfill(const STRING *sobj, unsigned int length);

/*
 * swap_case() -	Changes lowercase characters to uppercase and vice-versa
 * @sobj: 			the string to modify
 *
 * Returns the modified string
 */
STRING* str_swap_case(const STRING *sobj);

/*
 * title() -	Changes the first letter of every word to uppercase
 * @sobj: 		the string to modify
 *
 * Returns the modified string in title-case
 */
STRING* str_title(const STRING *sobj);

/*
 * str_chop() -			Removes a certain number of characters from the leading and trailing edges of a string
 * @num_chars_left:		the number of characters to remove from the leading edge
 * @num_chars_right:	the number of characters to remove from the trailing edge
 *
 * Returns the modified string
 */
STRING* str_chop(const STRING *sobj, unsigned int num_chars_left, unsigned int num_chars_right);

/*
 * str_equals() -	Checks if two strings are equal (case sensitive)  or not
 * @sobj1:			the first string
 * @sobj2:			the second string
 *
 * Returns TRUE if both strings are equal else returns FALSE
 */
BOOL str_equals(const STRING *sobj1, const STRING *sobj2);

/*
 * str_equals_ignore_case() -	Checks if two strings are equal (case insensitive) or not
 * @sobj1:						the first string
 * @sobj2:						the second string
 *
 * Returns TRUE if both strings are equal (ignoring case) else returns FALSE
 */
BOOL str_equals_ignore_case(const STRING *sobj1, const STRING *sobj2);

/*
 * str_compare() -	Compares two strings (case sensitive)
 * @sobj1:			the first string
 * @sobj2:			the second string
 *
 * Returns the difference between the ASCII codes of two characters in the two strings at their first point of difference
 */
int str_compare(const STRING *sobj1, const STRING *sobj2);

/*
 * str_compare_ignore_case() -	Compares two strings (case insensitive)
 * @sobj1:						the first string
 * @sobj2:						the second string
 *
 * Returns the difference between the ASCII codes of two characters (ignoring case) in the two strings at their first point of difference
 */
int str_compare_ignore_case(const STRING *sobj1, const STRING *sobj2);

/*
 * str_is_empty() -	Checks if a string is empty, i.e. has zero length
 * @sobj:			the string to check
 *
 * Returns TRUE if the string has zero length, else returns FALSE
 */
BOOL str_is_empty(const STRING *sobj);

#ifdef __cplusplus
}
#endif

/* End of include guard */
#endif
