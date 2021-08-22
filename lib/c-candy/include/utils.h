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

/* definition of item value */
typedef union {
	char char_value;
	short short_value;
	int int_value;
	long long_value;
	long long ll_value;
	float float_value;
	double double_value;
	long double ld_value;
	void *object;
} ITEM;

/* structure declarations */
typedef struct SL_NODE {
	void *data;
	struct SL_NODE *next;
} SL_NODE;

typedef struct DL_NODE {
	void *data;
	struct DL_NODE *next;
	struct DL_NODE *prev;
} DL_NODE;

typedef struct ML_NODE {
	void *data;
	unsigned int child_count;
	struct ML_NODE **child;
	struct ML_NODE *parent;
} ML_NODE;

/* <--------------------------- function declarations -----------------------------> */

void dump_sl_node(SL_NODE *node, BOOL recursive);
void dump_dl_node(DL_NODE *node, BOOL recursive);
void dump_ml_node(ML_NODE *node, BOOL recursive);

ITEM* cc_create_item(ITEM_TYPE type, void *p);

/*
 * cc_as_generic() -	Converts a primitive data type to void*
 * @type:				the type of the primitive variable
 * @items:				the list of items to iterate over, takes the first one
 *
 * Returns a void* pointer to the newly reserved generic pointer
 */
void* cc_as_generic(ITEM_TYPE type, va_list items);

/*
 * cc_generic_equals() -	Checks if two items are equal
 * @type:					the type of the items
 * @item1:					the first item
 * @item2:					the second item
 *
 * Returns TRUE if the items are equal else returns FALSE
 */
BOOL cc_generic_equals(ITEM_TYPE type, void *item1, void *item2);

/*
 * cc_generic_swap() -	Swaps the position of two elements in an array
 * @list:				the array to swap in
 * @index1:				the position of the first element
 * @index2:				the position of the second element
 */
void cc_generic_swap(void **list, int index1, int index2);

/*
 * cc_generic_sort() -	Sorts an array in-place
 * @length:				the length of the array
 * @items:				the array to sort
 * @reverse:			if TRUE, sorts in descending order else in ascending order
 * @comparator:			the comparator function to use for sorting
 */
void cc_generic_sort(unsigned int length, void **items, BOOL reverse, int (*comparator)(void *item));

/*
 * cc_xxx_comparator() -	Standard comparators to use in sorting
 * @item:					pointer to the item to map
 *
 * Returns the integer passed as argument
 */
int cc_char_comparator(void *item);
int cc_short_comparator(void *item);
int cc_int_comparator(void *item);

#ifdef __cplusplus
}
#endif

/* End of include guard */
#endif
