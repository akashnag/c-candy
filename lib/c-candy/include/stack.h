/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/include/stack.h
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
#ifndef STACK_H

#define STACK_H

#include <constants.h>
#include <utils.h>

#ifdef __cplusplus
extern "C" {
#endif

/* definition of STACK */
typedef struct {
	ITEM_TYPE type;
	SL_NODE *top;
	unsigned int length;
} STACK;

/* <------------------ function declarations -------------------> */

/* frees memory allocated for the stack */
void stack_dump(STACK *stk);

/* initializes a new empty stack */
STACK* stack(ITEM_TYPE type);

/* pushes an item onto the stack */
BOOL stack_push(STACK *stk, ...);

/* pushes multiple items onto the stack */
int stack_push_multi(unsigned int item_count, STACK *stk, ...);

/* returns the item at the top of the stack */
ITEM* stack_peek(const STACK *stk);

/* returns and removes the item at the top of the stack */
ITEM* stack_pop(STACK *stk);

/* returns the number of elements in the stack */
unsigned int stack_length(const STACK *stk);

/* returns the data type of the stack */
ITEM_TYPE stack_type(const STACK *stk);

/* returns how far (from top) is an element if present (>=0); if not present returns -1 */
int stack_find(const STACK *stk, ...);

/* returns the elements of the stack as an array */
ITEM** stack_to_array(const STACK *stk);

/* checks if a stack is empty or not */
BOOL stack_is_empty(const STACK *stk);

#ifdef __cplusplus
}
#endif

/* End of include guard */
#endif
