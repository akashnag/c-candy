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
#include <str.h>
#include <utils.h>
#include <stack.h>

/* <------------------ private function declarations -----------------> */

/* creates a new stack node */
static SL_NODE* make_stack_node(void *value, SL_NODE *link)
{
	SL_NODE *node;

	node = (SL_NODE*)malloc(sizeof(SL_NODE));
	if(node == NULL) return NULL;

	node->data = value;
	node->next = link;

	return node;
}

/* <------------------ public function definitions -------------------> */

/* frees memory allocated for the stack */
void stack_dump(STACK *stk)
{
	if(stk != NULL)
	{
		dump_sl_node(stk->top, TRUE);
		free(stk);
	}
}

/* initializes a new empty stack */
STACK* stack(ITEM_TYPE type)
{
	STACK *stk;

	stk = (STACK*)malloc(sizeof(STACK));
	if(stk == NULL) return NULL;

	stk->type = type;
	stk->top = NULL;
	stk->length = 0;

	return stk;
}

/* pushes an item onto the stack */
BOOL stack_push(STACK *stk, ...)
{
	va_list args;
	void *item;
	SL_NODE *node;
	
	if(stk == NULL) return FALSE;
	
	va_start(args, stk);
	
	item = cc_as_generic(stk->type, args);
	node = make_stack_node(item, stk->top);
	if(node == NULL) return FALSE;

	stk->top = node;
	++stk->length;

	va_end(args);
	return TRUE;
}

/* pushes multiple items onto the stack */
int stack_push_multi(unsigned int item_count, STACK *stk, ...)
{
	va_list args;
	void *item;
	SL_NODE *node;
	unsigned int i;
	
	if(stk == NULL || item_count <= 0) return 0;
	
	va_start(args, stk);
	for(i = 0; i < item_count; ++i)
	{
		item = cc_as_generic(stk->type, args);
		node = make_stack_node(item, stk->top);
		if(node == NULL) break;

		stk->top = node;
		++stk->length;
	}

	va_end(args);
	return i;
}

/* returns the item at the top of the stack */
ITEM* stack_peek(const STACK *stk)
{
	if(stk == NULL) return NULL;
	if(stk->top->next == NULL) return NULL;

	return cc_create_item(stk->type, stk->top->next->data);
}

/* returns and removes the item at the top of the stack */
ITEM* stack_pop(STACK *stk)
{
	ITEM *item;
	SL_NODE *temp;

	if(stk == NULL) return NULL;
	if(stk->top == NULL) return NULL;

	item = cc_create_item(stk->type, stk->top->data);
	if(item != NULL)
	{
		temp = stk->top;
		stk->top = stk->top->next;
		dump_sl_node(temp, FALSE);
		--stk->length;
	}

	return item;
}

/* returns the number of elements in the stack */
unsigned int stack_length(const STACK *stk)
{
	if(stk == NULL) return -1;
	return stk->length;
}

/* returns the data type of the stack */
ITEM_TYPE stack_type(const STACK *stk)
{
	if(stk == NULL) return -1;
	return stk->type;
}

/* checks if an item is present in the stack */
int stack_find(const STACK *stk, ...)
{
	SL_NODE *temp;
	int pos;
	void *item;
	va_list args;

	if(stk == NULL) return -1;
	if(stk->top == NULL) return -1;

	va_start(args, stk);
	item = cc_as_generic(stk->type, args);
	va_end(args);
	if(item == NULL) return -1;

	pos = 0;
	temp = stk->top;
	while(temp != NULL)
	{
		if(cc_generic_equals(stk->type, temp->data, item)) return pos;

		temp = temp->next;
		++pos;
	}

	return -1;
}

/* returns the elements of the stack as an array */
ITEM** stack_to_array(const STACK *stk)
{
	SL_NODE *temp;
	ITEM **array;
	unsigned int i;

	if(stk == NULL) return NULL;

	array = (ITEM**)calloc(stk->length, sizeof(ITEM*));
	if(array == NULL) return NULL;

	i = stk->length;
	temp = stk->top;
	while(i > 0)
	{
		array[--i] = cc_create_item(stk->type, temp->data);
		temp = temp->next;
	}

	return array;
}

/* checks if a stack is empty */
BOOL stack_is_empty(const STACK *stk)
{
	if(stk == NULL) return TRUE;
	return(stk->length == 0 ? TRUE : FALSE);
}