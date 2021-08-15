/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/src/str.c
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

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <regex.h>
#include <constants.h>
#include <str.h>

/* <------------------ private constant declarations -----------------> */
static const char *WHITESPACE = " \t\n\r\v\f";
static const char *WHITESPACE_REGEX = "\s";

/* <------------------ private function declarations -----------------> */
static STRING* copy(const STRING *sobj, int length, int dest_start, int src_start, int src_end, BOOL fill_left, char fill_char, BOOL end_with_null);
static STRING* exact_copy(const STRING *sobj);
static BOOL is_char_in(char c, const char *s);
static int regex_match(const char *text, const char *exp, int nmatch, regmatch_t *match_ptr);
static char* partial_strcpy(const char *text, int start, int end);
static int strcmpi(const char *s1, const char *s2);

/* <------------------ private function definitions ------------------> */

/* Copy a STRING partially/completely with provision for allocating some extra space for future use (src_end is exclusive) */
static STRING* copy(const STRING *sobj, int length, int dest_start, int src_start, int src_end, BOOL fill_left, char fill_char, BOOL end_with_null)
{
	STRING *sres;
	int i;

	if(sobj == NULL || length < 0) return NULL;
	if(src_start < 0 || src_end > sobj->length) return NULL;
	if(dest_start + (src_end - src_start) - 1 >= length) return NULL;
	
	sres = (STRING*)malloc(STR_SIZE);
	if(sres == NULL) return NULL;

	sres->data = (char*)calloc(length + 1, sizeof(char));
	if(sres->data == NULL) return NULL;

	if(fill_left) {
		for(i = 0; i < dest_start; ++i) sres->data[i] = fill_char;
	}

	for(i = src_start; i < src_end; ++i)
		sres->data[dest_start + i - src_start] = sobj->data[i];
	
	if(end_with_null) sres->data[dest_start + src_end - src_start] = '\0';

	sres->length = length;
	return sres;
}

/* Returns an exact copy of the given string */
static STRING* exact_copy(const STRING *sobj)
{
	return copy(sobj, sobj->length, 0, 0, sobj->length, FALSE, NULL, TRUE);
}

/* Returns TRUE if the given character is within a string */
static BOOL is_char_in(char c, const char *s)
{
	int i, n;
	if(s == NULL) return FALSE;
	n = strlen(s);
	for(i = 0; i < n; ++i)
	{
		if(s[i] == c) return TRUE;
	}
	return FALSE;
}

/* matches a regular expression */
static int regex_match(const char *text, const char *exp, int nmatch, regmatch_t *match_ptr)
{
	int count, i, result;
	regex_t regex;

	match_ptr = (regmatch_t*)malloc(nmatch * sizeof(regmatch_t));
	if(match_ptr == NULL) return -1;

	if(regcomp(&regex, exp, REG_EXTENDED | REG_NEWLINE)) return -1;
	
	result = regexec(&regex, text, nmatch, match_ptr, 0);
	regfree(&regex);

	if(result == REG_NOMATCH || result == REG_ESPACE) return -1;

	i = -1;
	count = 0;

	while(match_ptr[++i].rm_so >= 0) count++;
	return count;
}

/* returns a copy of a portion of a string (start inclusive, end exclusive) */
static char* partial_strcpy(const char *text, int start, int end)
{
	char *data;
	int i;

	data = (char*)calloc(end-start+1, sizeof(char));
	if(data == NULL) return NULL;

	for(i = start; i < end; ++i) data[i-start] = text[i];
	data[end-start] = '\0';

	return data;
}

/* compares two strings ignoring case */
static int strcmpi(const char *s1, const char *s2)
{
	int n1, n2, i, diff;
	char c1, c2;

	n1 = strlen(s1);
	n2 = strlen(s2);

	diff = 0;
	for(i = 0; i <= n1 && i <= n2; ++i)
	{
		c1 = s1[i];
		c2 = s2[i];
		
		if(c1 >= 97 && c1 <= 122) c1-=32;
		if(c2 >= 97 && c2 <= 122) c2-=32;

		diff = c1-c2;
		if(diff != 0) break;
	}

	return diff;
}

/* <------------------ public function definitions ------------------> */

/* Frees memory allocated for the string object */
void dump_str(STRING *sobj)
{
	if(sobj != NULL)
	{
		free(sobj->data);
		free(sobj);
	}
}

/* Creates an empty STRING object */
STRING* str_blank()
{
	STRING *sobj;
	
	sobj = (STRING*)malloc(STR_SIZE);
	if(sobj == NULL) return NULL;
	
	sobj->data = (char*)calloc(1, sizeof(char));
	if(sobj->data == NULL) return NULL;

	sobj->length = 0;
	return sobj;
}

/* Creates a STRING object from a C string literal */
STRING* str(const char *s)
{
	STRING *sobj;
	int n;

	sobj = (STRING*)malloc(STR_SIZE);
	if(sobj == NULL) return NULL;
	
	n = strlen(s);
	sobj->data = (char*)calloc(n + 1, sizeof(char));
	if(sobj->data == NULL) return NULL;

	sobj->length = n;
	strcpy(sobj->data, s);
	return sobj;
}

/* copies a string object */
STRING* str_copy(const STRING *s)
{
	return exact_copy(s);
}

/* Returns the number of characters in a string */
unsigned int str_len(const STRING *sobj)
{
	if(sobj == NULL) return -1;
	return sobj->length;
}

/* Converts a STRING object to a C string literal */
char* cstr(const STRING *sobj)
{
	char *scopy;

	if(sobj == NULL) return NULL;

	scopy = (char*)calloc(sobj->length + 1, sizeof(char));
	if(scopy == NULL) return NULL;

	strcpy(scopy, sobj->data);
	return scopy;
}

/* Returns the character in a string (sobj) at a particular index */
char str_char_at(const STRING *sobj, int index)
{
	if(sobj == NULL) return NULL;

	/* convert negative to positive index */
	if(index < 0) index += sobj->length;
	
	if(index < 0 || index >= sobj->length) return NULL;
	return sobj->data[index];
}

/* Returns TRUE if the given character is in the string */
BOOL str_is_char_in(const STRING *sobj, char c)
{
	return is_char_in(c, cstr(sobj));
}

/* Returns TRUE if a string (sobj) starts with another string (prefix) */
BOOL str_starts_with(const STRING *sobj, const STRING *prefix)
{
	unsigned int i, plen;

	if(sobj == NULL || prefix == NULL) return FALSE;
	if(prefix->length > sobj->length) return FALSE;

	plen = prefix->length;
	for(i = 0; i < plen; ++i)
		if(sobj->data[i] != prefix->data[i]) return FALSE;

	return TRUE;
}

/* Returns TRUE if a string (sobj) ends with another string (suffix) */
BOOL str_ends_with(const STRING *sobj, const STRING *suffix)
{
	unsigned int i, len, slen;

	if(sobj == NULL || suffix == NULL) return FALSE;
	if(suffix->length > sobj->length) return FALSE;

	len = sobj->length;
	slen = suffix->length;
	for(i = 0; i < slen; ++i)
		if(sobj->data[len-i-1] != suffix->data[slen-i-1]) return FALSE;

	return TRUE;
}

/* Converts a string to upper-case */
STRING* str_to_upper(const STRING *sobj)
{
	STRING *sres;
	unsigned int i;
	char c;

	sres = exact_copy(sobj);
	if(sres == NULL) return NULL;

	for(i = 0; i < sres->length; ++i)
	{
		c = sres->data[i];
		if(c >= 'a' && c <= 'z') c -= 32;
		sres->data[i] = c;
	}

	return sres;
}

/* Converts a string to lower-case */
STRING* str_to_lower(const STRING *sobj)
{
	STRING *sres;
	unsigned int i;
	char c;

	sres = exact_copy(sobj);
	if(sres == NULL) return NULL;

	for(i = 0; i < sres->length; ++i)
	{
		c = sres->data[i];
		if(c >= 'A' && c <= 'Z') c += 32;
		sres->data[i] = c;
	}

	return sres;
}

/* Returns a sub-string from a given string object within start (inclusive) and end (exclusive) indices */
STRING* str_substring(const STRING *sobj, int start, int end)
{
	/* convert start and end from negative to positive indices */
	if(start < 0) start += sobj->length;
	if(end < 0) end += sobj->length;

	/* check bounds */
	if(start < 0 || end < 0 || end > sobj->length) return NULL;
	if(start >= end) return str_blank();

	return copy(sobj, end - start, 0, start, end, FALSE, NULL, TRUE);
}

/* Returns a reversed copy of the given string */
STRING* str_reverse(const STRING *sobj)
{
	STRING *sres;
	unsigned int i, n;
	char c;

	if(sobj == NULL) return NULL;

	sres = exact_copy(sobj);
	if(sres == NULL) return NULL;

	n = sobj->length;
	for(i = 0; i < n/2; ++i)
	{
		c = sres->data[i];
		sres->data[i] = sres->data[n-i-1];
		sres->data[n-i-1] = c;
	}

	return sres;
}

/* Returns TRUE if all characters in the string are alphanumeric */
BOOL str_is_alphanumeric(const STRING *sobj)
{
	unsigned int i;
	char c;

	if(sobj == NULL) return FALSE;
	for(i = 0; i < sobj->length; ++i)
	{
		c = sobj->data[i];
		if(!((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))) return FALSE;
	}
	return TRUE;
}

/* Returns TRUE if all characters in the string are alphabets */
BOOL str_is_alpha(const STRING *sobj)
{
	unsigned int i;
	char c;

	if(sobj == NULL) return FALSE;
	for(i = 0; i < sobj->length; ++i)
	{
		c = sobj->data[i];
		if(!((c >= 65 && c <= 90) || (c >= 97 && c <= 122))) return FALSE;
	}
	return TRUE;
}

/* Returns TRUE if all characters in the string are numeric */
BOOL str_is_decimal(const STRING *sobj)
{
	unsigned int i;
	char c;

	if(sobj == NULL) return FALSE;
	for(i = 0; i < sobj->length; ++i)
	{
		c = sobj->data[i];
		if(c < 48 || c > 57) return FALSE;
	}
	return TRUE;
}

/* Returns TRUE if all characters are whitespaces */
BOOL str_is_whitespace(const STRING *sobj)
{
	unsigned int i;

	if(sobj == NULL) return FALSE;
	for(i = 0; i < sobj->length; ++i)
	{
		if(!is_char_in(sobj->data[i], WHITESPACE)) return FALSE;
	}
	return TRUE;
}

/* Returns TRUE if all alphabetic characters are in uppercase */
BOOL str_is_upper(const STRING *sobj)
{
	unsigned int i;
	char c;

	if(sobj == NULL) return FALSE;
	for(i = 0; i < sobj->length; ++i)
	{
		c = sobj->data[i];
		if(c >= 97 && c <= 122) return FALSE;
	}
	return TRUE;
}

/* Returns TRUE if all alphabetic characters are in lowercase */
BOOL str_is_lower(const STRING *sobj)
{
	unsigned int i;
	char c;

	if(sobj == NULL) return FALSE;
	for(i = 0; i < sobj->length; ++i)
	{
		c = sobj->data[i];
		if(c >= 65 && c <= 90) return FALSE;
	}
	return TRUE;
}

/* Fills a string with zeroes on the left */
STRING* str_zfill(const STRING *sobj, unsigned int length)
{
	STRING *sres;

	if(sobj == NULL) {
		char *s;
		unsigned int i;

		s = (char*)calloc(length + 1, sizeof(char));
		if(s == NULL) return NULL;

		for(i = 0; i < length; ++i) s[i] = '0';
		s[length] = '\0';

		sres = str(s);
		free(s);

		return sres;
	}
	
	if(sobj->length >= length) return exact_copy(sobj);
	return copy(sobj, length, length - sobj->length, 0, sobj->length, TRUE, '0', TRUE);
}

/* Changes uppercase characters to lowercase and vice-versa */
STRING* str_swap_case(const STRING *sobj)
{
	STRING *sres;
	unsigned int i;
	char c;

	if(sobj == NULL) return NULL;
	sres = exact_copy(sobj);
	if(sres == NULL) return NULL;

	for(i = 0; i < sres->length; ++i)
	{
		c = sres->data[i];
		if(c >= 65 && c <= 90)
			c += 32;
		else if(c >= 97 && c <= 122)
			c -= 32;
		sres->data[i] = c;
	}

	return sres;
}

/* Converts first letter of every word to uppercase */
STRING* str_title(const STRING *sobj)
{
	STRING *sres;
	unsigned int i;
	char c;

	if(sobj == NULL) return NULL;
	sres = exact_copy(sobj);
	if(sres == NULL) return NULL;

	for(i = 0; i < sres->length; ++i)
	{
		c = sres->data[i];
		if(c >= 97 && c <= 122) {
			if(i == 0 || is_char_in(sres->data[i-1], WHITESPACE)) sres->data[i] = c - 32;				
		}
	}

	return sres;
}

/* Replaces each tab with spaces */
STRING* str_expand_tabs(const STRING *sobj, unsigned int tab_size)
{
	STRING *sres;
	unsigned int i, j, k, tab_count;
	char *s;
	
	if(sobj == NULL) return NULL;

	tab_count = 0;
	for(i = 0; i < sobj->length; ++i)
	{
		if(sobj->data[i] == '\t') ++tab_count;
	}

	s = (char*)calloc(sobj->length - tab_count + (tab_size * tab_count) + 1, sizeof(char));
	if(s == NULL) return NULL;

	for(i = 0, j = -1; i < sobj->length; ++i)
	{
		if(sobj->data[i] == '\t') {
			for(k = 0; k < tab_size; ++k) s[++j] = ' ';
		} else {
			s[++j] = sobj->data[i];
		}
	}
	s[++j] = '\0';

	return str(s);
}

/* append another string to the end of this string */
BOOL str_append(STRING *sobj, const STRING *suffix)
{
	STRING *sres;
	unsigned int i;

	if(sobj == NULL || suffix == NULL) return FALSE;
	
	sres = copy(sobj, sobj->length + suffix->length, 0, 0, sobj->length, FALSE, NULL, FALSE);
	if(sres == NULL) return FALSE;

	for(i = 0; i < suffix->length; ++i)
		sres->data[sobj->length + i] = suffix->data[i];

	sres->data[sobj->length + suffix->length] = '\0';

	free(sobj);
	sobj = sres;
	return TRUE;
}

BOOL str_insert(STRING *sobj, int index, const STRING *ins_str)
{
	STRING *sres;
	unsigned int i;

	if(sobj == NULL || ins_str == NULL) return FALSE;

	/* convert negative to positive index */
	if(index < 0) index += sobj->length;

	if(index > sobj->length) return FALSE;
	if(index == sobj->length) return str_append(sobj, ins_str);
	
	sres = copy(sobj, sobj->length + ins_str->length, 0, 0, index, FALSE, NULL, FALSE);
	if(sres == NULL) return FALSE;

	for(i = 0; i < ins_str->length; ++i) sres->data[index + i] = ins_str->data[i];
	for(i = index; i < sobj->length; ++i) sres->data[ins_str->length + i] = sobj->data[i];
	sres->data[sobj->length + ins_str->length] = '\0';

	free(sobj);
	sobj = sres;

	return TRUE;
}

/* replaces a part of a string with another string */
BOOL str_replace_part(STRING *sobj, int start, int end, const STRING *ins_str)
{
	unsigned int i;

	if(sobj == NULL) return FALSE;

	/* convert negative to positive indices */
	if(start < 0) start += sobj->length;
	if(end < 0) end += sobj->length;

	if(start < 0 || end < 0 || start >= sobj->length || end > sobj->length || start >= end) return FALSE;

	/* 
	 	if ins_str is longer than portion (i.e. end-start) then replace only till the length of the portion
		if ins_str is shorter than portion, then replace till ins_str's length
	 */
	for(i = 0; i < end-start && i < ins_str->length; ++i) sobj->data[start + i] = ins_str->data[i];
	return TRUE;
}

/* justifies a string to the center within a certain width, pads with pad_char; more padding on right if padding is not evenly divisible  */
STRING* str_center(const STRING *sobj, unsigned int length, char pad_char)
{
	STRING *sres;
	unsigned int i, left_pad_length;

	if(sobj == NULL) return NULL;
	if(sobj->length >= length) return exact_copy(sobj);

	left_pad_length = (length - sobj->length) / 2;
	sres = copy(sobj, length, left_pad_length, 0, sobj->length, TRUE, pad_char, FALSE);
	if(sres == NULL) return NULL;

	for(i = left_pad_length + sobj->length; i < length; ++i) sres->data[i] = ' ';
	sres->data[length] = '\0';

	return sres;
}

/* justifies a string to the left within a certain width, pads with pad_char */
STRING* str_ljust(const STRING *sobj, unsigned int length, char pad_char)
{
	STRING *sres;
	unsigned int i, right_pad_length;

	if(sobj == NULL) return NULL;
	if(sobj->length >= length) return exact_copy(sobj);

	right_pad_length = length - sobj->length;
	sres = copy(sobj, length, 0, 0, sobj->length, FALSE, NULL, FALSE);
	if(sres == NULL) return sres;

	for(i = sobj->length; i < length; ++i) sres->data[i] = ' ';
	sres->data[length] = '\0';

	return sres;
}

/* justifies a string to the right within a certain width, pads with pad_char */
STRING* str_rjust(const STRING *sobj, unsigned int length, char pad_char)
{
	STRING *sres;
	unsigned int i, left_pad_length;

	if(sobj == NULL) return NULL;
	if(sobj->length >= length) return exact_copy(sobj);

	left_pad_length = length - sobj->length;
	sres = copy(sobj, length, left_pad_length, 0, sobj->length, TRUE, ' ', TRUE);
	
	return sres;
}

/* chops off certain number of characters from the left and right */
STRING* str_chop(const STRING *sobj, unsigned int num_chars_left, unsigned int num_chars_right)
{
	if(sobj == NULL) return NULL;
	if(num_chars_left + num_chars_right > sobj->length) return NULL;

	if(num_chars_left + num_chars_right == sobj->length) return str_blank();
	return str_substring(sobj, num_chars_left, -num_chars_right);
}

/* checks if a string is blank / empty */
BOOL str_is_empty(const STRING *sobj)
{
	if(sobj == NULL) return TRUE;
	return sobj->length == 0 ? TRUE : FALSE;
}

/* removes any leading / trailing whitespaces from a string */
STRING* str_strip(const STRING *sobj)
{
	unsigned int start, end;

	if(sobj == NULL) return NULL;
	
	for(start = 0; start < sobj->length && is_char_in(sobj->data[start], WHITESPACE); ++start);
	for(end = sobj->length; end > 0 && is_char_in(sobj->data[end-1], WHITESPACE); --end);

	if(start == end) return str_blank();
	return str_substring(sobj, start, end);
}

/* removes any leading whitespaces from a string */
STRING* str_lstrip(const STRING *sobj)
{
	unsigned int start;

	if(sobj == NULL) return NULL;
	
	for(start = 0; start < sobj->length && is_char_in(sobj->data[start], WHITESPACE); ++start);

	if(start == sobj->length-1) return str_blank();
	return str_substring(sobj, start, sobj->length);
}

/* removes any trailing whitespaces from a string */
STRING* str_rstrip(const STRING *sobj)
{
	unsigned int end;

	if(sobj == NULL) return NULL;
	
	for(end = sobj->length; end > 0 && is_char_in(sobj->data[end-1], WHITESPACE); --end);

	if(end == 0) return str_blank();
	return str_substring(sobj, 0, end);
}

/* checks if two strings are equal or not */
BOOL str_equals(const STRING *sobj1, const STRING *sobj2)
{
	if(sobj1 == NULL && sobj2 == NULL) return TRUE;
	if(sobj1 == NULL || sobj2 == NULL) return FALSE;
	return strcmp(sobj1->data, sobj2->data) == 0 ? TRUE : FALSE;
}

/* checks if two strings are equal or not ignoring case */
BOOL str_equals_ignore_case(const STRING *sobj1, const STRING *sobj2)
{
	if(sobj1 == NULL && sobj2 == NULL) return TRUE;
	if(sobj1 == NULL || sobj2 == NULL) return FALSE;
	return strcmpi(sobj1->data, sobj2->data) == 0 ? TRUE : FALSE;
}

/* compares two strings */
int str_compare(const STRING *sobj1, const STRING *sobj2)
{
	if(sobj1 == NULL && sobj2 == NULL) return 0;
	if(sobj1 == NULL) return (int)sobj2->data[0];
	if(sobj2 == NULL) return (int)sobj1->data[0];
	return strcmp(sobj1->data, sobj2->data);
}

/* comparing two strings by ignoring case */
int str_compare_ignore_case(const STRING *sobj1, const STRING *sobj2)
{
	if(sobj1 == NULL && sobj2 == NULL) return 0;
	if(sobj1 == NULL) return (int)sobj2->data[0];
	if(sobj2 == NULL) return (int)sobj1->data[0];
	return strcmpi(sobj1->data, sobj2->data);
}

/* counts the number of occurrences of a string within another string */
int str_count(const STRING *sobj, const STRING *match)
{
	regmatch_t *match_ptr;
	if(sobj == NULL || match == NULL) return -1;
	
	return regex_match(sobj->data, match->data, sobj->length, match_ptr);
}

/* finds the index of the first occurrence of a string within another string */
int str_find(const STRING *sobj, const STRING *match)
{
	int num_matches;
	regmatch_t *match_ptr;

	if(sobj == NULL || match == NULL) return -1;
	num_matches = regex_match(sobj->data, match->data, sobj->length, match_ptr);
	
	if(num_matches <= 0) 
		return -1;
	else
		return match_ptr[0].rm_so;
}

/* finds indices of all occurrences of a string within another string */
int str_find_all(const STRING *sobj, const STRING *match, unsigned int *indices)
{
	int num_matches;
	unsigned int i;
	regmatch_t *match_ptr;

	indices = NULL;
	if(sobj == NULL || match == NULL) return -1;
	num_matches = regex_match(sobj->data, match->data, sobj->length, match_ptr);
	
	if(num_matches > 0) {
		indices = (unsigned int*)calloc(num_matches, sizeof(unsigned int));
		for(i = 0; i < num_matches; ++i) indices[i] = match_ptr[i].rm_so;
	}

	return num_matches;
}

/* finds the index of the first occurrence of a string within another string starting within a range */
int str_find_within(const STRING *sobj, const STRING *match, int start, int end)
{
	int num_matches;
	regmatch_t *match_ptr;

	if(sobj == NULL || match == NULL) return -1;
	num_matches = regex_match(partial_strcpy(sobj->data, start, end), match->data, sobj->length, match_ptr);
	
	if(num_matches <= 0) 
		return -1;
	else
		return start + match_ptr[0].rm_so;
}

/* finds the index of the last occurrence of a string within another string */
int str_rfind(const STRING *sobj, const STRING *match)
{
	int num_matches;
	regmatch_t *match_ptr;

	if(sobj == NULL || match == NULL) return -1;
	num_matches = regex_match(sobj->data, match->data, sobj->length, match_ptr);
	
	if(num_matches <= 0) 
		return -1;
	else
		return match_ptr[num_matches-1].rm_so;
}

/* finds the index of the last occurrence of a string within another string within a range */
int str_rfind_within(const STRING *sobj, const STRING *match, int start, int end)
{
	int num_matches;
	regmatch_t *match_ptr;

	if(sobj == NULL || match == NULL) return -1;
	num_matches = regex_match(partial_strcpy(sobj->data, start, end), match->data, sobj->length, match_ptr);
	
	if(num_matches <= 0) 
		return -1;
	else
		return start + match_ptr[num_matches-1].rm_so;
}

/* replaces the first occurrence of a string with another string in a given string */
STRING* str_replace_first(const STRING *sobj, const STRING *find, const STRING *replace_with)
{
	unsigned int i;
	int num_matches, start, end, total_length;
	STRING *sres;
	regmatch_t *match_ptr;

	if(sobj == NULL || find == NULL || replace_with == NULL) return NULL;
	num_matches = regex_match(sobj->data, find->data, sobj->length, match_ptr);
	
	if(num_matches < 0) 
		return NULL;
	else if(num_matches == 0)
		return exact_copy(sobj);
	else {
		start = match_ptr[0].rm_so;
		end = match_ptr[0].rm_eo;
		total_length = sobj->length - (end - start) + replace_with->length;
		sres = copy(sobj, total_length, 0, 0, start, FALSE, NULL, FALSE);
		if(sres == NULL) return NULL;

		for(i = 0; i < replace_with->length; ++i) sres->data[i + start] = replace_with->data[i];
		for(i = end; i < sobj->length; ++i) sres->data[i + start + replace_with->length] = sobj->data[i];
		sres->data[total_length] = '\0';

		return sres;
	}
}

/* replaces all occurrences of a string with another string in a given string */
STRING* str_replace_all(const STRING *sobj, const STRING *find, const STRING *replace_with)
{
	unsigned int i, j, k;
	int num_matches, start, end, total_matched, total_length, rep_upto;
	regmatch_t *match_ptr;
	STRING *sres;

	if(sobj == NULL || find == NULL || replace_with == NULL) return NULL;
	num_matches = regex_match(sobj->data, find->data, sobj->length, match_ptr);
	
	if(num_matches < 0) 
		return NULL;
	else if(num_matches == 0)
		return exact_copy(sobj);
	else {
		/* count the total length of matched substrings */
		total_matched = 0;
		for(i = 0; i < num_matches; ++i) total_matched += (match_ptr[i].rm_eo - match_ptr[i].rm_so);

		/* compute total length of resulting string and allocate space for it */
		total_length = sobj->length - total_matched + (num_matches * replace_with->length);
		char *s = (char*)calloc(total_length + 1, sizeof(char));
		if(s == NULL) return NULL;

		/* start the replacement */
		k = -1;					/* store pointer to resulting string */
		rep_upto = -1;			/* store the last index (of the original string) upto which replacement/copying is done */
		for(i = 0; i < num_matches; ++i)
		{
			start = match_ptr[i].rm_so;
			end = match_ptr[i].rm_eo;

			if(start <= rep_upto) continue;		/* ignore overlapping matches */
			
			if(rep_upto < start) {
				/* there is a substring which needs to be copied without changes */
				for(j = rep_upto + 1; j < start; ++j) s[++k] = sobj->data[j];
			}

			/* copy the replacement string */
			for(j = 0; j < replace_with->length; ++j) s[++k] = replace_with->data[j];

			/* update position */
			rep_upto = end-1;
		}

		/* copy any remaining characters, and end with null */
		while(rep_upto < sobj->length - 1) s[++k] = sobj->data[++rep_upto];
		s[++k] = '\0';

		sres = str(s);
		free(s);
		return sres;
	}
}

/* splits a string based on a delimiter (regex) */
int str_split(const STRING *sobj, const char *delimiter, int max_split, STRING **parts)
{
	int num_matches, i, processed_upto;
	regmatch_t *match_ptr;
	
	parts = NULL;
	if(max_split < 0) return NULL;
	if(sobj == NULL || delimiter == NULL) return -1;
	if(sobj->length == 0 || strlen(delimiter) == 0 || max_split == 0) return exact_copy(sobj);

	num_matches = regex_match(sobj->data, delimiter, sobj->length, match_ptr);
	
	if(num_matches < 0) 		
		return -1;
	else if(num_matches == 0) {
		parts = (STRING**)calloc(1, sizeof(STRING*));
		parts[0] = exact_copy(sobj);
		return 1;
	} else {
		num_matches = (num_matches <= max_split) ? num_matches : max_split;
		parts = (STRING**)calloc(num_matches + 1, sizeof(STRING*));
		
		processed_upto = 0;		/* stores last_index_copied + 1 of the original string */
		for(i = 0; i < num_matches; ++i)
		{
			parts[i] = str_substring(sobj, processed_upto, match_ptr[i].rm_so);
			processed_upto = match_ptr[i].rm_eo;
		}

		parts[num_matches] = str_substring(sobj, processed_upto, sobj->length);
		return num_matches + 1;
	}
}

/* splits a string based on whitespace characters */
int str_split_whitespace(const STRING *sobj, int max_split, STRING **parts)
{
	return str_split(sobj, WHITESPACE_REGEX, max_split, parts);
}

/* returns a string based on a format string and arguments */
STRING* str_cfmt(int max_len, const char *format, ...)
{
	va_list args;
	char *data;
	STRING *result;

	data = (char*)calloc(max_len + 1, sizeof(char));
	if(data == NULL) return NULL;

	va_start(args, format);
	snprintf(data, max_len + 1, format, args);
	va_end(args);

	result = str(data);
	free(data);
	return result;
}
