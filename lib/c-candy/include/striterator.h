/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/include/striterator.h
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
#ifndef STRITERATOR_H

#define STRITERATOR_H

#include <constants.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STRI_BOS				  0
#define STRI_EOS				-10

/* definition of STRING_ITERATOR object */
typedef struct {
	STRING *data;
	int marker;
} STRING_ITERATOR;

/* <------------------------------ function declarations --------------------------------> */

/*
 * dump_str_iterator() -	Frees memory allocated for the iterator
 * @s:						the iterator object to free
 */
void dump_str_iterator(STRING_ITERATOR *s);

/*
 * stri_cs() -	Creates an iterator over a C-style string
 * @s:			the C-style string to iterate over
 *
 * Returns an iterator
 */
STRING_ITERATOR* stri_cs(const char *s);

/*
 * stri() -	Creates an iterator over a C-Candy String object
 * @s:		the C-style string to iterate over
 *
 * Returns an iterator
 */
STRING_ITERATOR* stri(const STRING *s);

/*
 * stri_this() -	Returns the character at the current marker position
 * @s:				the iterator object
 *
 * Returns the character at the current marker position
 */
char stri_this(const STRING_ITERATOR *s);

/*
 * stri_next() -	Returns the character to the right of the current marker position
 * @s:				the iterator object
 *
 * Returns the character to the right of the current marker position
 */
char stri_next(const STRING_ITERATOR *s);

/*
 * stri_prev() -	Returns the character to the left of the current marker position
 * @s:				the iterator object
 *
 * Returns the character to the left of the current marker position
 */
char stri_prev(const STRING_ITERATOR *s);

/*
 * stri_pos() -	Returns the current marker position
 * @s:			the iterator object
 *
 * Returns the current marker position
 */
int stri_pos(const STRING_ITERATOR *s);

/*
 * stri_move_next() -	Shifts the marker one character to the right
 * @s:					the iterator object
 *
 * Returns the marker position after the shift
 */
int stri_move_next(STRING_ITERATOR *s);

/*
 * stri_move_prev() -	Shifts the marker one character to the left
 * @s:					the iterator object
 *
 * Returns the marker position after the shift
 */
int stri_move_prev(STRING_ITERATOR *s);

/*
 * stri_move() -	Shifts the marker certain number of characters to the left/right
 * @s:				the iterator object
 * @num_chars:		the number of characters to move (negative: left, positive: right)
 *
 * Returns the marker position after the shift
 */
int stri_move(STRING_ITERATOR *s, int num_chars);

/*
 * stri_skip() -	Shifts the marker to jump a certain number of characters to the right
 * @s:				the iterator object
 * @num_chars:		the number of characters to skip while moving right
 *
 * Returns the marker position after the shift
 */
int stri_skip(STRING_ITERATOR *s, unsigned int num_chars);

/*
 * stri_reset() -	Brings the marker back to the beginning of the string
 * @s:				the iterator object
 *
 * Returns the marker position after the shift
 */
int stri_reset(STRING_ITERATOR *s);

/*
 * stri_move_bos() -	(Same as stri_reset) Brings the marker back to the beginning of the string
 * @s:					the iterator object
 *
 * Returns the marker position after the shift
 */
int stri_move_bos(STRING_ITERATOR *s);

/*
 * stri_move_eos() -	Shifts the marker to the end of the string
 * @s:					the iterator object
 *
 * Returns the marker position after the shift
 */
int stri_move_eos(STRING_ITERATOR *s);

/*
 * stri_move_until() -	Shifts the marker till a given character is found
 * @s:					the iterator object
 * @chars:				the list of characters among which to find (stop at)
 * @step:				the number of characters to move the marker at a time during each check
 *
 * Returns the marker position after the shift
 */
int stri_move_until(STRING_ITERATOR *s, const char *chars, int step);

/*
 * stri_move_while() -	Shifts the marker until a character not among the given characters is found
 * @s:					the iterator object
 * @chars:				the list of characters to skip over
 * @step:				the number of characters to move the marker at a time during each check
 *
 * Returns the marker position after the shift
 */
int stri_move_while(STRING_ITERATOR *s, const char *chars, int step);

/*
 * stri_is_at_eos() -	Checks if the marker is at the end of the string
 * @s:					the iterator object
 *
 * Returns TRUE if the marker is at the end else returns FALSE
 */
BOOL stri_is_at_eos(const STRING_ITERATOR *s);

/*
 * stri_is_at_bos() -	Checks if the marker is at the beginning of the string
 * @s:					the iterator object
 *
 * Returns TRUE if the marker is at the beginning else returns FALSE
 */
BOOL stri_is_at_bos(const STRING_ITERATOR *s);

/*
 * stri_is_at() -	Checks if the marker is at the given position
 * @s:				the iterator object
 * @position:		the position to compare the marker against
 *
 * Returns TRUE if the marker is at the given position else returns FALSE
 */
BOOL stri_is_at(const STRING_ITERATOR *s, int position);

#ifdef __cplusplus
}
#endif

/* End of include guard */
#endif
