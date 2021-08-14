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
#include <constants.h>
#include <list.h>
#include <str.h>

/* <------------------ private function declarations -----------------> */

/* doubles the capacity of a list */
static BOOL increase_capacity(LIST *list)
{
	void **new_data;
	unsigned int i;

	if(list == NULL) return FALSE;

	/* allocate double memory */
	new_data = (void**)calloc(list->capacity * 2, sizeof(void*));
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
	new_data = (void**)calloc(list->capacity / 2, sizeof(void*));
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
	return ((list != NULL) && (list->length <= list->capacity/4)) ? TRUE : FALSE;
}

/* inserts an item at the specified index */
static int list_insert(LIST *list, int index, void *item)
{
	unsigned int i;
	
	if(list == NULL) return ERR_NULL_OBJECT;
	if(index < 0) index += list->length;
	if(index < 0 || index > list->length) return ERR_INDEX_OUT_OF_BOUNDS;
	
	if(index == list->length && list->length == list->capacity) {
		if(!increase_capacity(list)) return ERR_MEM_ALLOC;
	}

	if(index == list->length)
		list->data[list->length] = item;
	else {
		for(i = list->length; i > index; --i) list->data[i] = list->data[i-1];
		list->data[index] = item;
	}

	return ++list->length;
}

/* <------------------ public function definitions -------------------> */

/* <------ generic function definitions -----> */

/* frees memory allocated for the list */
void dump_list(LIST *list)
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
	STRING *item_string;
	short item_short;
	int item_int;
	long item_long;
	long long item_long_long;
	float item_float;
	double item_double;
	long double item_long_double;

	if(list == NULL) return ERR_NULL_OBJECT;

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
			if(temp == NULL) return ERR_MEM_ALLOC;
			*temp = item_char;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_STR) {
			item_string = str_copy((STRING*)generic_item);
			if(item_string < 0) return item_string;
			new_list->data[i] = (void*)item_string;
		}

		if(type == TYPE_SHORT) {
			short *temp;
			item_short = *((short*)generic_item);
			temp = (short*)malloc(sizeof(short));
			if(temp == NULL) return ERR_MEM_ALLOC;
			*temp = item_short;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_INT) {
			int *temp;
			item_int = *((int*)generic_item);
			temp = (int*)malloc(sizeof(int));
			if(temp == NULL) return ERR_MEM_ALLOC;
			*temp = item_int;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_LONG) {
			long *temp;
			item_long = *((long*)generic_item);
			temp = (long*)malloc(sizeof(long));
			if(temp == NULL) return ERR_MEM_ALLOC;
			*temp = item_long;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_LONG_LONG) {
			long long *temp;
			item_long_long = *((long long*)generic_item);
			temp = (long long*)malloc(sizeof(long long));
			if(temp == NULL) return ERR_MEM_ALLOC;
			*temp = item_long_long;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_FLOAT) {
			float *temp;
			item_float = *((float*)generic_item);
			temp = (float*)malloc(sizeof(float));
			if(temp == NULL) return ERR_MEM_ALLOC;
			*temp = item_float;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_DOUBLE) {
			double *temp;
			item_double = *((double*)generic_item);
			temp = (double*)malloc(sizeof(double));
			if(temp == NULL) return ERR_MEM_ALLOC;
			*temp = item_double;
			new_list->data[i] = (void*)temp;
		}

		if(type == TYPE_LONG_DOUBLE) {
			long double *temp;
			item_long_double = *((long double*)generic_item);
			temp = (long double*)malloc(sizeof(long double));
			if(temp == NULL) return ERR_MEM_ALLOC;
			*temp = item_long_double;
			new_list->data[i] = (void*)temp;
		}		
	}

	return new_list;
}

/* creates a new empty list */
LIST* list_new(ITEM_TYPE type, unsigned int initial_capacity)
{
	LIST *list;

	if(initial_capacity == 0) return ERR_INDEX_OUT_OF_BOUNDS;

	list = (LIST*)malloc(LIST_SIZE);
	if(list == NULL) return ERR_MEM_ALLOC;

	list->length = 0;
	list->capacity = initial_capacity;
	list->type = type;
	
	list->data = calloc(initial_capacity, sizeof(void*));
	if(list->data == NULL) return ERR_MEM_ALLOC;

	return list;
}

/* deletes the item at the specified index */
int list_delete(LIST *list, int index)
{
	unsigned int i;
	
	if(list == NULL) return ERR_NULL_OBJECT;
	if(index < 0) index += list->length;
	if(index < 0 || index >= list->length) return ERR_INDEX_OUT_OF_BOUNDS;

	free(list->data[index]);
	for(i = index; i < list->length - 1; ++i) list->data[i] = list->data[i+1];
	list->data[list->length-1] = NULL;
	--list->length;

	if(should_decrease_capacity(list)) {
		if(!decrease_capacity(list)) return ERR_MEM_ALLOC;
	}

	return list->length;
}

/* TODO: not implemented 
LIST* list_sorted(const LIST *list, int (*comparator)(void *item)); */

/* reverses a list and returns the new list */
LIST* list_reversed(const LIST *list)
{
	LIST *rev_list;
	unsigned int i;

	if(list == NULL) return ERR_NULL_OBJECT;

	rev_list = list_new(list->type, list->capacity);
	if(rev_list < 0) return rev_list;

	rev_list->length = list->length;

	for(i = 0; i < list->length; ++i) rev_list->data[list->length-1-i] = list->data[i];
	return list;
}

/* concatenates two lists and returns the new list */
LIST* list_join(const LIST *list1, const LIST *list2)
{
	LIST *new_list;
	unsigned int i, k;
	
	if(list1 == NULL || list2 == NULL) return ERR_NULL_OBJECT;
	if(list1->type != list2->type) return ERR_TYPE_MISMATCH;
	
	/* allocate memory */
	new_list = list_new(list1->type, list1->capacity + list2->capacity);
	if(new_list < 0) return new_list;

	/* copy items */
	k = 0;
	for(i = 0; i < list1->length; ++i) new_list->data[k++] = list1->data[i];
	for(i = 0; i < list2->length; ++i) new_list->data[k++] = list2->data[i];

	new_list->length = k;
	return new_list;
}

/* sorts a list in-place 
void list_sort(LIST *list, int (*comparator)(void *item))
{
	LIST *sorted_list;
	sorted_list = list_sorted(list, comparator);
	if(sorted_list >= 0) 
	{
		dump_list(list);
		list = sorted_list;
	}
}
*/
/* reverses a list in-place */
void list_reverse(LIST *list)
{
	unsigned int i, n;
	void *temp;
	
	if(list == NULL) return ERR_NULL_OBJECT;

	n = list->length;
	for(i = 0; i < n/2; ++i)
	{
		temp = list->data[i];
		list->data[i] = list->data[n-i-1];
		list->data[n-i-1] = temp;
	}
}

/* extends a list in-place */
void list_extend(LIST *list, const LIST *list_to_add)
{
	LIST *new_list;
	new_list = list_join(list, list_to_add);
	if(new_list >= 0)
	{
		dump_list(list);
		list = new_list;
	}
}

/* returns the length of the list */
int list_length(const LIST *list)
{
	if(list == NULL) return ERR_NULL_OBJECT;
	return list->length;
}

/* returns the capacity of the list */
int list_capacity(const LIST *list)
{
	if(list == NULL) return ERR_NULL_OBJECT;
	return list->capacity;
}

/* <------ int specific function definitions -----> */

LIST* list_from_int_array(BOOL deep_copy, const int *array, unsigned int start, unsigned int end)
{
	LIST *new_list;
	unsigned int i;
	int *item_p;

	if(array == NULL || array == NULL || end <= start) return ERR_NULL_OBJECT;
	
	new_list = list_new(TYPE_INT, (end-start+1) * 1.5);
	if(new_list < 0) return ERR_MEM_ALLOC;

	for(i = start; i < end; ++i)
	{
		if(deep_copy)
			new_list->data[i-start] = (void*)(&array[i]);
		else {
			item_p = (int*)malloc(sizeof(int));
			if(item_p == NULL) return ERR_MEM_ALLOC;
			*item_p = array[i];
			new_list->data[i-start] = (void*)item_p;
		}
	}

	new_list->length = end - start + 1;
	return new_list;
}

/* inserts an integer at the specified index in the list */
int list_insert_int(LIST *list, int index, int item)
{
	int *item_p;
	int ret_val;

	if(list == NULL) return ERR_NULL_OBJECT;
	if(list->type != TYPE_INT) return ERR_TYPE_MISMATCH;

	item_p = (int*)malloc(sizeof(int));
	if(item_p == NULL) return ERR_MEM_ALLOC;

	*item_p = item;

	ret_val = list_insert(list, index, (void*)item_p);
	if(ret_val <= 0) free(item_p);
	return (ret_val > 0 ? item : ret_val);
}

/* returns the object at the specified index as an integer */
int list_get_int(const LIST *list, int index, int error_value)
{
	int *item;
	
	if(list == NULL) return error_value;
	if(list->type != TYPE_INT) return error_value;

	if(index < 0) index += list->length;
	if(index < 0 || index >= list->length) return error_value;

	item = (int*)list->data[index];
	return *item;
}

/* returns the index at which the item was found in the list, or -1 if not found */
int list_find_int(const LIST *list, int item)
{
	int *data_item;
	unsigned int i;

	if(list == NULL) return ERR_NULL_OBJECT;
	if(list->type != TYPE_INT) return ERR_TYPE_MISMATCH;

	for(i = 0; i < list->length; ++i)
	{
		data_item = (int*)list->data[i];
		if(*data_item == item) return i;
	}

	return -1;
}

/* appends an integer to the end of the list */
int list_append_int(LIST *list, int item)
{
	return list_insert_int(list, list->length, item);
}

/* checks if an item exists in the list */
BOOL list_has_int(const LIST *list, int item)
{
	int index;

	index = list_find_int(list, item);
	return (index >= 0 ? TRUE : FALSE);
}
