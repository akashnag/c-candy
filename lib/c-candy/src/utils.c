/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/src/utils.c
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
#include <utils.h>

/* frees memory allocated for singly-linked node */
void dump_sl_node(SL_NODE *node, BOOL recursive)
{
	if(node == NULL) return;
	free(node->data);
	if(recursive) dump_sl_node(node->next, TRUE);
	free(node);
}

/* frees memory allocated for doubly-linked node */
void dump_dl_node(DL_NODE *node, BOOL recursive)
{
	if(node == NULL) return;
	free(node->data);
	
	if(node->next != NULL && recursive) dump_dl_node(node->next, TRUE);
	if(node->prev != NULL && recursive) dump_dl_node(node->prev, TRUE);

	free(node);
}

/* frees memory allocated for multi-linked node */
void dump_ml_node(ML_NODE *node, BOOL recursive)
{
	unsigned int i;
	
	if(node == NULL) return;
	free(node->data);
	
	for(i = 0; i < node->child_count; ++i)
	{
		if(node->child[i] != NULL && recursive) dump_ml_node(node->child[i], TRUE);
	}

	free(node->child);
	free(node);
}

ITEM* cc_create_item(ITEM_TYPE type, void *p)
{
	ITEM *item;

	item = (ITEM*)malloc(sizeof(ITEM));
	if(item == NULL) return NULL;

	if(type == TYPE_OBJECT) {
		item->object = p;
	} else if(type == TYPE_CHAR) {
		char *v;
		v = (char*)p;
		item->char_value = *v;
	} else if(type == TYPE_SHORT) {
		short *v;
		v = (short*)p;
		item->short_value = *v;
	} else if(type == TYPE_INT) {
		int *v;
		v = (int*)p;
		item->int_value = *v;
	} else if(type == TYPE_LONG) {
		long *v;
		v = (long*)p;
		item->long_value = *v;
	} else if(type == TYPE_FLOAT) {
		float *v;
		v = (float*)p;
		item->float_value = *v;
	} else if(type == TYPE_DOUBLE) {
		double *v;
		v = (double*)p;
		item->double_value = *v;
	} else if(type == TYPE_LONG_LONG) {
		long long *v;
		v = (long long*)p;
		item->ll_value = *v;
	} else if(type == TYPE_LONG_DOUBLE) {
		long double *v;
		v = (long double*)p;
		item->ld_value = *v;
	}

	return item;
}

/* converts a primitive type to void* pointer */
void* cc_as_generic(ITEM_TYPE type, va_list items)
{
	void *gen_p;

	if(type == TYPE_OBJECT) {
		gen_p = va_arg(items, void*);
	} else if(type == TYPE_CHAR) {
		char item = va_arg(items, char);
		char *item_p = (char*)malloc(sizeof(char));
		*item_p = item;
		gen_p = (void*)item_p;
	} else if(type == TYPE_SHORT) {
		short item = va_arg(items, short);
		short *item_p = (short*)malloc(sizeof(short));
		*item_p = item;
		gen_p = (void*)item_p;
	} else if(type == TYPE_INT) {
		int item = va_arg(items, int);
		int *item_p = (int*)malloc(sizeof(int));
		*item_p = item;
		gen_p = (void*)item_p;
	} else if(type == TYPE_LONG) {
		long item = va_arg(items, long);
		long *item_p = (long*)malloc(sizeof(long));
		*item_p = item;
		gen_p = (void*)item_p;
	} else if(type == TYPE_LONG_LONG) {
		long long item = va_arg(items, long long);
		long long *item_p = (long long*)malloc(sizeof(long long));
		*item_p = item;
		gen_p = (void*)item_p;
	} else if(type == TYPE_FLOAT) {
		float item = va_arg(items, float);
		float *item_p = (float*)malloc(sizeof(float));
		*item_p = item;
		gen_p = (void*)item_p;
	} else if(type == TYPE_DOUBLE) {
		double item = va_arg(items, double);
		double *item_p = (double*)malloc(sizeof(double));
		*item_p = item;
		gen_p = (void*)item_p;
	} else if(type == TYPE_LONG_DOUBLE) {
		long double item = va_arg(items, long double);
		long double *item_p = (long double*)malloc(sizeof(long double));
		*item_p = item;
		gen_p = (void*)item_p;
	}

	return gen_p;
}

/* checks if two values are equal */
BOOL cc_generic_equals(ITEM_TYPE type, void *item1, void *item2)
{
	if(item1 == NULL && item2 == NULL) return TRUE;
	if(item1 == NULL && item2 != NULL) return FALSE;
	if(item2 == NULL && item1 != NULL) return FALSE;

	if(type == TYPE_OBJECT) {
		return (item1 == item2 ? TRUE : FALSE);
	} else if(type == TYPE_CHAR) {
		char *v1, *v2;
		v1 = (char*)item1;
		v2 = (char*)item2;
		return (*v1 == *v2 ? TRUE : FALSE);
	} else if(type == TYPE_SHORT) {
		short *v1, *v2;
		v1 = (short*)item1;
		v2 = (short*)item2;
		return (*v1 == *v2 ? TRUE : FALSE);
	} else if(type == TYPE_INT) {
		int *v1, *v2;
		v1 = (int*)item1;
		v2 = (int*)item2;
		return (*v1 == *v2 ? TRUE : FALSE);
	} else if(type == TYPE_LONG) {
		long *v1, *v2;
		v1 = (long*)item1;
		v2 = (long*)item2;
		return (*v1 == *v2 ? TRUE : FALSE);
	} else if(type == TYPE_FLOAT) {
		float *v1, *v2;
		v1 = (float*)item1;
		v2 = (float*)item2;
		return (*v1 == *v2 ? TRUE : FALSE);
	} else if(type == TYPE_DOUBLE) {
		double *v1, *v2;
		v1 = (double*)item1;
		v2 = (double*)item2;
		return (*v1 == *v2 ? TRUE : FALSE);
	} else if(type == TYPE_LONG_LONG) {
		long long *v1, *v2;
		v1 = (long long*)item1;
		v2 = (long long*)item2;
		return (*v1 == *v2 ? TRUE : FALSE);
	} else if(type == TYPE_LONG_DOUBLE) {
		long double *v1, *v2;
		v1 = (long double*)item1;
		v2 = (long double*)item2;
		return (*v1 == *v2 ? TRUE : FALSE);
	}

	return FALSE;
}

/* swaps two positions in an array */
void cc_generic_swap(void **list, int index1, int index2)
{
	void *temp;

	temp = list[index1];
	list[index1] = list[index2];
	list[index2] = temp;
}

/* sorts a list */
/* TODO: replace with quicksort */
void cc_generic_sort(unsigned int length, void **items, BOOL reverse, int (*comparator)(void *item))
{
	unsigned int i, j;
	int comp_val1, comp_val2;
	void *temp;
	BOOL flag;

	for(i = 0; i < length; ++i)
	{
		flag = FALSE;
		for(j = 0; j < length - i - 1; ++j)
		{
			comp_val1 = comparator(items[j]);
			comp_val2 = comparator(items[j+1]);

			if((reverse && comp_val2 > comp_val1) || (!reverse && comp_val1 > comp_val2))
			{
				cc_generic_swap(items, j, j+1);
				flag = TRUE;
			}
		}
		if(!flag) return;
	}
}

int cc_int_comparator(void *item)
{
	int *vp;
	vp = (int*)item;
	return *vp;
}

int cc_short_comparator(void *item)
{
	short *vp;
	vp = (short*)item;
	return (int)(*vp);
}

int cc_char_comparator(void *item)
{
	char *vp;
	vp = (char*)item;
	return (int)(*vp);
}
