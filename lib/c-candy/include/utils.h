/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/include/utils.h
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
#ifndef UTILS_H

#define UTILS_H

#include <constants.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* <--------------------------- function declarations -----------------------------> */

/*
 * as_generic() -	Converts a primitive data type to void*
 * @type:			the type of the primitive variable
 * @items:			the list of items to iterate over, takes the first one
 *
 * Returns a void* pointer to the newly reserved generic pointer
 */
void* cc_as_generic(ITEM_TYPE type, va_list items);

/* TODO: not implemented */
BOOL cc_generic_equals(ITEM_TYPE type, void *item1, void *item2);

/* TODO: not implemented */
void cc_generic_swap(void **list, int index1, int index2);

/* TODO: not implemented */
void cc_generic_sort(unsigned int length, void **items, BOOL reverse, int (*comparator)(void *item));

/* TODO: not implemented */
int cc_int_comparator(void *item);

#ifdef __cplusplus
}
#endif

/* End of include guard */
#endif
