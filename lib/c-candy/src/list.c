/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/src/list.c
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
#include <constants.h>
#include <list.h>
#include <utils.h>

/* <------------------ private function declarations -----------------> */

/* doubles the capacity of a list */
static BOOL increase_capacity(LIST *list)
{
	void **new_data;
	unsigned int i;

	if(list == NULL) return FALSE;

	/* allocate double memory */
	new_data = (void**)calloc(list->capacity * LIST_CAPACITY_INCREASE_FACTOR, sizeof(void*));
	if(new_data == NULL) return FALSE;

	/* copy items */
	for(i = 0; i < list->length; ++i) new_data[i] = list->data[i];

	/* change data members */
	free(list->data);
	list->data = new_data;
	list->capacity *= 2;

	return TRUE;
}

/* halves the capacity of a list */
static BOOL decrease_capacity(LIST *list)
{
	void **new_data;
	unsigned int i;

	if(list == NULL) return FALSE;

	/* allocate half memory */
	new_data = (void**)calloc(list->capacity * LIST_CAPACITY_DECREASE_FACTOR, sizeof(void*));
	if(new_data == NULL) return FALSE;

	/* copy items */
	for(i = 0; i < list->length; ++i) new_data[i] = list->data[i];

	/* change data members */
	free(list->data);
	list->data = new_data;
	list->capacity /= 2;

	return TRUE;
}

/* checks if it is time to decrease the list capacity */
static BOOL should_decrease_capacity(LIST *list)
{
	return ((list != NULL) && (list->length <= list->capacity * LIST_CAPACITY_DECREASE_LOAD_FACTOR)) ? TRUE : FALSE;
}

/* checks if it is time to decrease the list capacity */
static BOOL should_increase_capacity(LIST *list)
{
	return ((list != NULL) && (list->length >= list->capacity * LIST_CAPACITY_INCREASE_LOAD_FACTOR)) ? TRUE : FALSE;
}

/* inserts an item at the specified index */
static BOOL list_insert_generic(LIST *list, int index, void *value)
{
	unsigned int i;
	
	if(list == NULL) return FALSE;
	if(index < 0) index += list->length;
	if(index < 0 || index > list->length) return FALSE;
	
	if(should_increase_capacity(list)) {
		if(!increase_capacity(list)) return FALSE;
	}
	
	if(index == list->length)
		list->data[list->length] = value;
	else {
		for(i = list->length; i > index; --i) list->data[i] = list->data[i-1];
		list->data[index] = value;
	}

	++list->length;
	return TRUE;
}

/* returns the index of where a value is found, returns -1 if not found */
static int list_find_generic(const LIST *list, void *value)
{
	unsigned int i;
	
	if(list == NULL) return -1;
	for(i = 0; i < list->length; ++i)
	{
		if(cc_generic_equals(list->type, list->data[i], value)) return i;
	}
	return -1;
}

/* returns the element at the specified index */
static void* list_at_generic(LIST *list, int index)
{
	if(list == NULL) return NULL;
	if(index < 0) index += list->length;

	if(index < 0 || index >= list->length) return NULL;
	return list->data[index];
}

/* <------------------ public function definitions -------------------> */

/* frees memory allocated for the list */
void list_dump(LIST *list)
{
	if(list != NULL)
	{
		free(list->data);
		free(list);
	}
}

/* returns a new copy of a list */
LIST* list_copy(const LIST *list, BOOL deep_copy)
{
	LIST *new_list;
	void *generic_item, *new_generic_item;
	ITEM_TYPE type;
	unsigned int i;

	char item_char;
	short item_short;
	int item_int;
	long item_long;
	long long item_long_long;
	float item_float;
	double item_double;
	long double item_long_double;

	if(list == NULL) return NULL;

	new_list = list_new(list->type, list->capacity);
	if(new_list < 0) return new_list;

	new_list->length = list->length;

	type = list->type;
	for(i = 0; i < list->length; ++i)
	{
		if(deep_copy || type == TYPE_OBJECT) 
		{
			new_list->data[i] = list->data[i];
			continue;
		}

		generic_item = list->data[i];

		if(type == TYPE_CHAR) {
			char *temp;
			item_char = *((char*)generic_item);
			temp = (char*)malloc(sizeof(char));
			if(temp == NULL) return NULL;
			*temp = item_char;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_SHORT) {
			short *temp;
			item_short = *((short*)generic_item);
			temp = (short*)malloc(sizeof(short));
			if(temp == NULL) return NULL;
			*temp = item_short;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_INT) {
			int *temp;
			item_int = *((int*)generic_item);
			temp = (int*)malloc(sizeof(int));
			if(temp == NULL) return NULL;
			*temp = item_int;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_LONG) {
			long *temp;
			item_long = *((long*)generic_item);
			temp = (long*)malloc(sizeof(long));
			if(temp == NULL) return NULL;
			*temp = item_long;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_LONG_LONG) {
			long long *temp;
			item_long_long = *((long long*)generic_item);
			temp = (long long*)malloc(sizeof(long long));
			if(temp == NULL) return NULL;
			*temp = item_long_long;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_FLOAT) {
			float *temp;
			item_float = *((float*)generic_item);
			temp = (float*)malloc(sizeof(float));
			if(temp == NULL) return NULL;
			*temp = item_float;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_DOUBLE) {
			double *temp;
			item_double = *((double*)generic_item);
			temp = (double*)malloc(sizeof(double));
			if(temp == NULL) return NULL;
			*temp = item_double;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_LONG_DOUBLE) {
			long double *temp;
			item_long_double = *((long double*)generic_item);
			temp = (long double*)malloc(sizeof(long double));
			if(temp == NULL) return NULL;
			*temp = item_long_double;
			new_list->data[i] = (void*)temp;
		}		
	}

	return new_list;
}

/* creates a new empty list */
LIST* list(ITEM_TYPE type, unsigned int initial_capacity)
{
	LIST *list;

	if(initial_capacity == 0) return NULL;

	list = (LIST*)malloc(sizeof(LIST));
	if(list == NULL) return NULL;

	list->length = 0;
	list->capacity = initial_capacity;
	list->type = type;
	
	list->data = calloc(initial_capacity, sizeof(void*));
	if(list->data == NULL) return NULL;

	return list;
}

/* deletes the item at the specified index */
BOOL list_delete(LIST *list, int index)
{
	unsigned int i;
	
	if(list == NULL) return FALSE;
	if(index < 0) index += list->length;
	if(index < 0 || index >= list->length) return FALSE;

	free(list->data[index]);
	for(i = index; i < list->length - 1; ++i) list->data[i] = list->data[i+1];
	list->data[list->length-1] = FALSE;
	--list->length;

	if(should_decrease_capacity(list)) {
		decrease_capacity(list);
	}

	return TRUE;
}

/* reverses a list and returns the new list */
LIST* list_reversed(const LIST *list)
{
	LIST *rev_list;
	unsigned int i;

	if(list == NULL) return NULL;

	rev_list = list_new(list->type, list->capacity);
	if(rev_list == NULL) return NULL;

	rev_list->length = list->length;

	for(i = 0; i < list->length; ++i) rev_list->data[list->length-1-i] = list->data[i];
	return list;
}

/* concatenates two lists and returns the new list */
LIST* list_join(const LIST *list1, const LIST *list2)
{
	LIST *new_list;
	unsigned int i, k;
	
	if(list1 == NULL || list2 == NULL) return NULL;
	if(list1->type != list2->type) return NULL;
	
	/* allocate memory */
	new_list = list_new(list1->type, list1->capacity + list2->capacity);
	if(new_list == NULL) return NULL;

	/* copy items */
	k = 0;
	for(i = 0; i < list1->length; ++i) new_list->data[k++] = list1->data[i];
	for(i = 0; i < list2->length; ++i) new_list->data[k++] = list2->data[i];

	new_list->length = k;
	return new_list;
}

/* reverses a list in-place */
void list_reverse(LIST *list)
{
	unsigned int i, n;
	void *temp;
	
	if(list == NULL) return NULL;

	n = list->length;
	for(i = 0; i < n/2; ++i) cc_generic_swap(list->data, i, n-i-1);
}

/* extends a list in-place */
BOOL list_extend(LIST *list, const LIST *list_to_add)
{
	LIST *new_list;
	new_list = list_join(list, list_to_add);
	if(new_list == NULL) return FALSE;

	list_dump(list);
	list = new_list;
	return TRUE;
}

/* returns the length of the list */
int list_length(const LIST *list)
{
	if(list == NULL) return -1;
	return list->length;
}

/* returns the capacity of the list */
int list_capacity(const LIST *list)
{
	if(list == NULL) return -1;
	return list->capacity;
}

/* returns the data type of the list */
ITEM_TYPE list_type(const LIST *list)
{
	if(list == NULL) return -1;
	return list->type;
}

/* returns the index at which the item was found in the list, or -1 if not found */
int list_find(const LIST *list, ...)
{
	va_list args;
	void *item;
	int index, ret_val;

	if(list == NULL) return -1;
	
	va_start(args, list);
	
	item = cc_as_generic(list->type, args);
	index = list_find_generic(list, item);	
	va_end(args);
	
	return index;
}

/* appends an item to the end of the list */
BOOL list_append(LIST *list, ...)
{
	va_list args;
	void *item;
	BOOL ret_val;

	if(list == NULL) return FALSE;
	
	va_start(args, list);
	
	item = cc_as_generic(list->type, args);	
	ret_val = list_insert_generic(list, list->length, item);

	va_end(args);
	return ret_val;
}

/* checks if an item exists in the list */
BOOL list_has_item(const LIST *list, ...)
{
	va_list args;
	void *item;
	int index, ret_val;

	if(list == NULL) return FALSE;
	
	va_start(args, list);
	
	item = cc_as_generic(list->type, args);
	index = list_find_generic(list, item);	
	va_end(args);
	return (index < 0 ? FALSE : TRUE);
}

/* inserts an item at the specified index in the list */
BOOL list_insert(LIST *list, int index, ...)
{
	va_list args;
	void *item;
	BOOL ret_val;

	if(list == NULL) return FALSE;
	
	va_start(args, index);
	
	item = cc_as_generic(list->type, args);
	ret_val = list_insert_generic(list, index, item);
	va_end(args);
	return ret_val;
}

/* form a list from the elements passed as arguments */
LIST* list_from_elements(unsigned int argc, ITEM_TYPE type, ...)
{
	LIST *list;
	va_list args;
	void *item;
	unsigned int i;

	va_start(args, type);
	
	list = list_new(type, argc * LIST_CAPACITY_INIT_BUFFER_FACTOR);
	if(list == NULL) return NULL;

	for(i = 0; i < argc; ++i)
	{
		item = cc_as_generic(list->type, args);
		list_insert_generic(list, i, item);		
	}
	
	va_end(args);
	return list;
}

/* returns a new sorted list (shallow copy) */
LIST* list_sorted(const LIST *list, BOOL reverse, int (*comparator)(void *item))
{
	LIST *sorted_list;
	
	if(list == NULL) return NULL;
	if(comparator == NULL) return NULL;
	
	sorted_list = list_copy(list, FALSE);
	if(sorted_list == NULL) return NULL;

	cc_generic_sort(sorted_list->length, sorted_list->data, reverse, comparator);
	return sorted_list;
}

/* sorts a list in-place */
void list_sort(LIST *list, BOOL reverse, int (*comparator)(void *item))
{
	if(list != NULL && comparator != NULL)
		cc_generic_sort(list->length, list->data, reverse, comparator);
}

/* returns the object at the specified index as an integer */
ITEM* list_get(const LIST *list, int index)
{
	ITEM *item;
	void *p;

	if(list == NULL || index < 0 || index >= list->length) return NULL;

	p = list_at_generic(list, index);
	return cc_create_item(list->type, p);
}

/* sets an item at the specified index */
BOOL list_set(const LIST *list, int index, ...)
{
	va_list args;
	void *item;
	BOOL ret_val;

	if(list == NULL) return FALSE;
	if(index < 0) index += list->length;
	if(index < 0 || index >= list->length) return FALSE;
	
	va_start(args, index);
	
	item = cc_as_generic(list->type, args);
	list->data[index] = item;

	va_end(args);
	return TRUE;
}

/* returns a portion of a list as another list */
LIST* list_get_sublist(const LIST *list, int start, int end, BOOL deep_copy)
{
	LIST *sublist, *result;
	unsigned int i;

	if(list == NULL) return NULL;

	if(start < 0) start += list->length;
	if(end < 0) end += list->length;

	if(start < 0 || start >= list->length) return NULL;
	if(end < 0 || end > list->length) return NULL;
	if(start > end) return NULL;

	sublist = list_new(list->type, (end - start + 1) * LIST_CAPACITY_INIT_BUFFER_FACTOR);
	if(start == end) return sublist;

	for(i = start; i < end; ++i) sublist->data[i-start] = list->data[i];
	sublist->length = (end - start + 1);

	result = list_copy(sublist, deep_copy);
	list_dump(sublist);
	return result;
}

/* returns the elements of the list as an array */
ITEM** list_to_array(const LIST *list)
{
	ITEM **items;
	unsigned int i;

	if(list == NULL) return NULL;
	if(list->length == 0) return NULL;

	items = (ITEM**)calloc(list->length, sizeof(ITEM*));
	for(i = 0; i < list->length; ++i) items[i] = cc_create_item(list->type, list->data[i]);

	return items;
}
