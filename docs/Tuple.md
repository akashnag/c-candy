Tuple
=====================
Header: `c-candy/tuple.h`

Version 0.1.0-alpha

&copy; Copyright 2021, Akash Nag. Distributed under GPL v2.0.

This is the documentation page for all functions and constants defined by the c-candy Tuple library. The type `TUPLE` is an implementation of an immutable list.

### Struct types

The base type `TUPLE` is defined as follows:

```c
typedef struct {
	ITEM_TYPE *types;
	void **data;
	int length;
} TUPLE;
```

### Functions

| Return type | Signature | Description |
|-|-|-|
| void | tuple_dump(TUPLE *tuple) | Frees memory allocated for a tuple |
| ITEM* | tuple_at(const TUPLE *tuple, int index) | Returns the item at the specified index |
| TUPLE* | tuple(int count, ...) | Creates a new empty tuple |
| int | tuple_length(const TUPLE *tuple) | Returns the number of items in the tuple |
| ITEM_TYPE | tuple_type_at(const TUPLE *tuple, int index) | Returns the data type of the item at the specified index |

