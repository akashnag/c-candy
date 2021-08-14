/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/src/striterator.c
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
#include <constants.h>
#include <str.h>
#include <striterator.h>

/* <----------------------- public function definitions -------------------------> */

/* frees memory allocated for the string iterator object */
void dump_str_iterator(STRING_ITERATOR *s)
{
	if(s != NULL)
	{
		dump_str(s->data);
		free(s);
	}
}

/* returns a new string iterator object from a given string */
STRING_ITERATOR* stri(const STRING *s)
{
	STRING_ITERATOR *result;

	if(s == NULL) return ERR_NULL_OBJECT;
	if(s->length == 0) return ERR_INDEX_OUT_OF_BOUNDS;

	result = (STRING_ITERATOR*)malloc(sizeof(STRING_ITERATOR));
	if(result == NULL) return ERR_MEM_ALLOC;

	result->data = str_copy(s);
	result->marker = 0;
	return result;
}

/* returns a new string iterator object from a given C-style string */
STRING_ITERATOR* stri_cs(const char *s)
{
	return stri(str(s));
}

/* returns the character at the current marker position */
char stri_this(const STRING_ITERATOR *s)
{
	if(s == NULL) return ERR_NULL_OBJECT;
	if(s->marker == s->data->length) return NULL;
	return s->data->data[s->marker];
}

/* returns the character to the right of the current marker position */
char stri_next(const STRING_ITERATOR *s)
{
	if(s == NULL) return ERR_NULL_OBJECT;
	if(s->marker >= s->data->length) return NULL;
	return s->data->data[s->marker + 1];
}

/* returns the character to the left of the current marker position */
char stri_prev(const STRING_ITERATOR *s)
{
	if(s == NULL) return ERR_NULL_OBJECT;
	if(s->marker <= 0) return NULL;
	return s->data->data[s->marker - 1];
}

/* returns the current marker position */
int stri_pos(const STRING_ITERATOR *s)
{
	if(s == NULL) return ERR_NULL_OBJECT;
	return(s->marker == s->data->length ? STRI_EOS : s->marker);
}

/* moves the marker to a certain number of characters, positive for right, negative for left */
int stri_move(STRING_ITERATOR *s, int num_chars)
{
	int new_pos;
	
	if(s == NULL) return ERR_NULL_OBJECT;

	new_pos = s->marker + num_chars;
	if(new_pos < 0) new_pos = 0;
	if(new_pos > s->data->length) new_pos = s->data->length;
	s->marker = new_pos;
	return s->marker;
}

/* moves the marker 1 character to the right */
int stri_move_next(STRING_ITERATOR *s)
{
	return stri_move(s, 1);
}

/* moves the marker 1 character to the left */
int stri_move_prev(STRING_ITERATOR *s)
{
	return stri_move(s, -1);
}

/* moves the marker to the right skipping over a certain number of characters */
int stri_skip(STRING_ITERATOR *s, unsigned int num_chars)
{
	return stri_move(s, num_chars + 1);
}

/* moves the marker to the beginning of the string */
int stri_reset(STRING_ITERATOR *s)
{
	if(s == NULL) return ERR_NULL_OBJECT;
	s->marker = 0;
	return s->marker;
}

/* moves the marker to the beginning of the string */
int stri_move_bos(STRING_ITERATOR *s)
{
	return stri_reset(s);
}

/* moves the marker to the end of the string */
int stri_move_eos(STRING_ITERATOR *s)
{
	if(s == NULL) return ERR_NULL_OBJECT;
	s->marker = s->data->length;
	return s->marker;
}

/* return TRUE if the marker is at the end of the string */
BOOL stri_is_at_eos(const STRING_ITERATOR *s)
{
	if(s == NULL) return ERR_NULL_OBJECT;
	return (s->marker == s->data->length ? TRUE : FALSE);
}

/* return TRUE if the marker is at the beginning of the string */
BOOL stri_is_at_bos(const STRING_ITERATOR *s)
{
	if(s == NULL) return ERR_NULL_OBJECT;
	return (s->marker == 0 ? TRUE : FALSE);
}

/* return TRUE if the marker is at the given position */
BOOL stri_is_at(const STRING_ITERATOR *s, int position)
{
	if(s == NULL) return ERR_NULL_OBJECT;
	return (s->marker == position ? TRUE : FALSE);
}

/* moves the marker until the given character is found */
int stri_move_until(STRING_ITERATOR *s, const char *chars, int step)
{
	STRING *schars;

	if(s == NULL) return ERR_NULL_OBJECT;
	schars = str(chars);
	if(schars == NULL) return ERR_MEM_ALLOC;
	
	while(s->marker < s->data->length && !str_is_char_in(schars, s->data->data[s->marker]))
		s->marker += step;

	if(s->marker < 0)
		s->marker = 0;
	else if(s->marker > s->data->length)
		s->marker = s->data->length;

	free(schars);
	return s->marker;
}

/* moves the marker until any character other than the given character is found */
int stri_move_while(STRING_ITERATOR *s, const char *chars, int step)
{
	STRING *schars;

	if(s == NULL) return ERR_NULL_OBJECT;
	schars = str(chars);
	if(schars == NULL) return ERR_MEM_ALLOC;
	
	while(s->marker < s->data->length && str_is_char_in(schars, s->data->data[s->marker]))
		s->marker += step;

	if(s->marker < 0)
		s->marker = 0;
	else if(s->marker > s->data->length)
		s->marker = s->data->length;

	free(schars);
	return s->marker;
}
