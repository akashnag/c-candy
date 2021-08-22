Global Constants / Functions
=============================
Headers: `c-candy/constants.h` and `c-candy/utils.h`

Version 0.1.0-alpha

&copy; Copyright 2021, Akash Nag. Distributed under GPL v2.0.

This is the documentation page for all constants defined globally by the c-candy library.

### Constants (`constants.h`)

| Name | Value |
|-|-|
| C_CANDY_VERSION | "0.1.0-alpha" |


### Enumerated types (`constants.h`)

The base type `BOOL` is defined as follows:

```c
typedef enum {
	FALSE = 0, TRUE = 1
} BOOL;
```

The base type `ITEM_TYPE` is defined as follows:

```c
typedef enum {
	TYPE_CHAR, TYPE_SHORT, TYPE_INT, 
	TYPE_LONG, TYPE_LONG_LONG, TYPE_FLOAT, 
	TYPE_DOUBLE, TYPE_LONG_DOUBLE, TYPE_OBJECT
} ITEM_TYPE;
```

### Structures and Unions (`utils.h`)

The base type `ITEM` is defined as follows:

```c
typedef union {
	char char_value;
	short short_value;
	int int_value;
	long long_value;
	long long ll_value;
	float float_value;
	double double_value;
	long double ld_value;
	void *object;
} ITEM;
```

### Functions (`utils.h`)

| Return type | Signature | Description |
|-|-|-|
| ITEM* | cc_create_item(ITEM_TYPE type, void *p) | Creates a generic item from a void pointer |
| void* | cc_as_generic(ITEM_TYPE type, va_list items) | Creates a void pointer from a list of variable arguments |
| BOOL | cc_generic_equals(ITEM_TYPE type, void *item1, void *item2) | Checks if two generic values are equal |
| void | cc_generic_swap(void **list, int index1, int index2) | Swaps two values in a list |
| void | cc_generic_sort(unsigned int length, void **items, BOOL reverse, int (*comparator)(void *item)) | Sorts a list of generic items |
