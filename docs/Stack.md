Stack
=====================
Header: `c-candy/stack.h`

Version 0.1.0-alpha

&copy; Copyright 2021, Akash Nag. Distributed under GPL v2.0.

This is the documentation page for all functions and constants defined by the c-candy Stack library. The type `STACK` is an implementation of a Linked Stack.

### Struct types

The base type `STACK` is defined as follows:

```c
typedef struct {
	ITEM_TYPE type;
	SL_NODE *top;
	unsigned int length;
} STACK;
```

### Functions

| Return type | Signature | Description |
|-|-|-|
| void | stack_dump(STACK *stk) | Frees memory allocated for a stack object |
| STACK* | stack(ITEM_TYPE type) | Creates a new empty stack |
| BOOL | stack_push(STACK *stk, ...) | Appends an element to the top of the stack |
| int | stack_push_multi(unsigned int item_count, STACK *stk, ...) | Appends multiple elements to the stack |
| ITEM* | stack_peek(const STACK *stk) | Returns the top element of the stack |
| ITEM* | stack_pop(STACK *stk) | Removes and returns the top element of the stack |
| unsigned int | stack_length(const STACK *stk) | Returns the number of elements in the stack |
| ITEM_TYPE | stack_type(const STACK *stk) | Returns the data type of the stack |
| int | stack_find(const STACK *stk, ...) | Returns the index of the first occurrence of an element in the stack; returns -1 if not found |
| ITEM** | stack_to_array(const STACK *stk) | Returns an array representation of the stack |
| BOOL | stack_is_empty(const STACK *stk) | Returns TRUE if the stack is empty else returns FALSE |
