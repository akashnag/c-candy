/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/src/tuple.c
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
#include <tuple.h>
#include <utils.h>

/* <------------------ private function declarations -----------------> */

/* frees memory allocated for the tuple */
void tuple_dump(TUPLE *tuple)
{
	unsigned int i;
	
	if(tuple == NULL) return;

	for(i = 0; i < tuple->length; ++i)	
		if(tuple->types[i] != TYPE_OBJECT) 
			free(tuple->data[i]);
	
	free(tuple->types);
	free(tuple->data);
	free(tuple);
}

/* returns the item at the specified index */
ITEM* tuple_at(const TUPLE *tuple, int index)
{
	if(tuple == NULL) return NULL;
	if(index < 0) index += tuple->length;
	if(index < 0 || index >= tuple->length) return NULL;

	return cc_create_item(tuple->types[index], tuple->data[index]);
}

/* creates a new empty tuple */
TUPLE* tuple(int count, ...)
{
	va_list args;
	ITEM_TYPE *types;
	void **data;
	TUPLE *tuple;
	int i;

	if(count <= 0) return NULL;
	
	types = (ITEM_TYPE*)calloc(count, sizeof(ITEM_TYPE));
	if(types == NULL) return NULL;

	data = (void**)calloc(count, sizeof(void*));
	if(data == NULL) return NULL;

	va_start(args, count);
	for(i = 0; i < count; ++i) types[i] = va_arg(args, ITEM_TYPE);
	for(i = 0; i < count; ++i) data[i] = cc_as_generic(types[i], args);
	va_end(args);

	tuple = (TUPLE*)malloc(sizeof(TUPLE));
	if(tuple == NULL) return NULL;

	tuple->length = count;
	tuple->types = types;
	tuple->data = data;

	return tuple;
}

/* returns the length of the tuple */
int tuple_length(const TUPLE *tuple)
{
	if(tuple == NULL) return 0;
	return tuple->length;
}

/* returns the data type of the item at the specified index */
ITEM_TYPE tuple_type_at(const TUPLE *tuple, int index)
{
	if(tuple == NULL) return NULL;
	if(index < 0) index += tuple->length;
	if(index < 0 || index >= tuple->length) return NULL;

	return tuple->types[index];
}
