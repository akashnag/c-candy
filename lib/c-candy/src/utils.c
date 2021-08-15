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
#include <list.h>
#include <str.h>
#include <utils.h>

/* converts a primitive type to void* pointer */
void* cc_as_generic(ITEM_TYPE type, va_list items)
{
	void *gen_p;

	if(type == TYPE_STR || type == TYPE_OBJECT) {
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
	} else if(type == TYPE_STR) {
		STRING *v1, *v2;
		v1 = (STRING*)item1;
		v2 = (STRING*)item2;
		return str_equals(v1, v2);
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

void cc_generic_sort(unsigned int length, void **items, BOOL reverse, int (*comparator)(void *item))
{
	unsigned int i, j;
	int comp_val1, comp_val2;
	void *temp;

	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < length - i - 1; ++j)
		{
			comp_val1 = comparator(items[j]);
			comp_val2 = comparator(items[j+1]);

			if((reverse && comp_val2 > comp_val1) || (!reverse && comp_val1 > comp_val2))
				cc_generic_swap(items, j, j+1);
		}
	}
}

int cc_int_comparator(void *item)
{
	int *vp;
	vp = (int*)item;
	return *vp;
}
