/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/include/tuple.h
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
#ifndef TUPLE_H

#define TUPLE_H

#include <constants.h>
#include <utils.h>

#ifdef __cplusplus
extern "C" {
#endif

/* definition of LIST */
typedef struct {
	ITEM_TYPE *types;
	void **data;
	int length;
} TUPLE;

/* <------------------ function declarations -------------------> */

/* frees memory allocated for the tuple */
void tuple_dump(TUPLE *tuple);

/* returns the length of the tuple */
int tuple_length(const TUPLE *tuple);

/* returns the data type of the item at the specified index */
ITEM_TYPE tuple_type_at(const TUPLE *tuple, int index);

/* returns the item at the specified index */
ITEM* tuple_at(const TUPLE *tuple, int index);

/* creates a new empty tuple */
TUPLE* tuple(int count, ...);

#ifdef __cplusplus
}
#endif

/* End of include guard */
#endif
