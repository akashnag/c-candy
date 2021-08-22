/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/include/list.h
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
#ifndef LIST_H

#define LIST_H

#include <constants.h>
#include <utils.h>

#ifdef __cplusplus
extern "C" {
#endif

/* constant declarations */
#define LIST_CAPACITY_INIT_BUFFER_FACTOR		2
#define LIST_CAPACITY_INCREASE_LOAD_FACTOR		1
#define LIST_CAPACITY_INCREASE_FACTOR			2
#define LIST_CAPACITY_DECREASE_LOAD_FACTOR		0.25
#define LIST_CAPACITY_DECREASE_FACTOR			0.5

/* definition of LIST */
typedef struct {
	ITEM_TYPE type;
	void **data;
	int length;
	int capacity;
} LIST;

/* <------------------ function declarations -------------------> */

/* frees memory allocated for the list */
void list_dump(LIST *list);

/* returns a new copy of a list */
LIST* list_copy(const LIST *list, BOOL deep_copy);

/* creates a new empty list */
LIST* list(ITEM_TYPE type, unsigned int initial_capacity);

/* deletes the item at the specified index */
BOOL list_delete(LIST *list, int index);

/* reverses a list and returns the new list */
LIST* list_reversed(const LIST *list);

/* reverses a list in-place */
void list_reverse(LIST *list);

/* concatenates two lists and returns the new list */
LIST* list_join(const LIST *list1, const LIST *list2);

/* extends a list in-place */
BOOL list_extend(LIST *list, const LIST *list_to_add);

/* returns the length of the list */
int list_length(const LIST *list);

/* returns the capacity of the list */
int list_capacity(const LIST *list);

/* returns the data type of the list */
ITEM_TYPE list_type(const LIST *list);

/* returns the index at which the item was found in the list, or -1 if not found */
int list_find(const LIST *list, ...);

/* appends an item to the end of the list */
BOOL list_append(LIST *list, ...);

/* checks if an item exists in the list */
BOOL list_has_item(const LIST *list, ...);

/* inserts an item at the specified index in the list */
BOOL list_insert(LIST *list, int index, ...);

/* form a list from the elements passed as arguments */
LIST* list_from_elements(unsigned int argc, ITEM_TYPE type, ...);

/* returns a sorted shallow-copy of the list */
LIST* list_sorted(const LIST *list, BOOL reverse, int (*comparator)(void *item));

/* sorts a list in-place */
void list_sort(LIST *list, BOOL reverse, int (*comparator)(void *item));

/* returns the object at the specified index */
ITEM* list_get(const LIST *list, int index);

/* sets an item at the specified index */
BOOL list_set(const LIST *list, int index, ...);

/* returns a portion of a list as another list */
LIST* list_get_sublist(const LIST *list, int start, int end, BOOL deep_copy);

/* returns the elements of the list as an array */
ITEM** list_to_array(const LIST *list);

#ifdef __cplusplus
}
#endif

/* End of include guard */
#endif
