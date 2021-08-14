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

#ifdef __cplusplus
extern "C" {
#endif

/* other constants */
#define LIST_SIZE 						sizeof(LIST)

/* definition of LIST */
typedef struct {
	ITEM_TYPE type;
	void **data;
	int length;
	int capacity;
} LIST;

/* <--------------------------- function declarations -----------------------------> */

/* <-------------------- int specific functions --------------------> */

/* TODO: not implemented */
LIST* list_from_int_array(BOOL deep_copy, const int *array, unsigned int start, unsigned int end);

/* TODO: not implemented */
int list_insert_int(LIST *list, int index, int item);

/* TODO: not implemented */
int list_get_int(const LIST *list, int index, int error_value);

/* TODO: not implemented */
int list_find_int(const LIST *list, int item);

/* TODO: not implemented */
int list_append_int(LIST *list, int item);

/* TODO: not implemented */
BOOL list_has_int(const LIST *list, int item);

/* <-------------------- generic functions --------------------> */

/* TODO: not implemented */
void dump_list(LIST *list);

/* TODO: not implemented */
LIST* list_copy(const LIST *list, BOOL deep_copy);

/* TODO: not implemented */
LIST* list_new(ITEM_TYPE list_type, unsigned int initial_capacity);

/* TODO: not implemented */
int list_delete(LIST *list, int index);

/* TODO: not implemented */
LIST* list_sorted(const LIST *list, int (*comparator)(void *item));

/* TODO: not implemented */
LIST* list_reversed(const LIST *list);

/* TODO: not implemented */
void list_sort(LIST *list, int (*comparator)(void *item));

/* TODO: not implemented */
void list_reverse(LIST *list);

/* TODO: not implemented */
LIST* list_join(const LIST *list1, const LIST *list2);

/* TODO: not implemented */
void list_extend(LIST *list, const LIST *list_to_add);

/* TODO: not implemented */
int list_length(const LIST *list);

/* TODO: not implemented */
int list_capacity(const LIST *list);

#ifdef __cplusplus
}
#endif

/* End of include guard */
#endif
