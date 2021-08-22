List
=====================
Header: `c-candy/list.h`

Version 0.1.0-alpha

&copy; Copyright 2021, Akash Nag. Distributed under GPL v2.0.

This is the documentation page for all functions and constants defined by the c-candy List library. The type `LIST` is an implementation of a Dynamic Array.

### Struct types

The base type `LIST` is defined as follows:

```c
typedef struct {
	ITEM_TYPE type;
	void **data;
	int length;
	int capacity;
} LIST;
```

### Constants

| Constant | Value | Description |
|-|-|-|
| LIST_CAPACITY_INIT_BUFFER_FACTOR | 2 | The factor of extra space to allocate when the list is initialized with a list of elements |
| LIST_CAPACITY_INCREASE_LOAD_FACTOR | 1 | The load-factor threshold at which the capacity of the list is increased |
| LIST_CAPACITY_INCREASE_FACTOR | 2 | The factor by which the capacity of the list is increased |
| LIST_CAPACITY_DECREASE_LOAD_FACTOR | 0.25 | The load-factor threshold at which the capacity of the list is decreased |
| LIST_CAPACITY_DECREASE_FACTOR | 0.5 | The factor by which the capacity of the list is decreased |


### Functions

| Return type | Signature | Description |
|-|-|-|
| void | list_dump(LIST *list) | Frees memory allocated for the list |
| LIST* | list_copy(const LIST *list, BOOL deep_copy) | Returns a new copy of an existing list |
| LIST* | list(ITEM_TYPE type, unsigned int initial_capacity) | Creates a new empty list |
| BOOL | list_delete(LIST *list, int index) | Deletes the item at the specified index |
| LIST* | list_reversed(const LIST *list) | Returns a copy of the given list with the order of its items reversed |
| void | list_reverse(LIST *list) | Reverses a list in-place |
| LIST* | list_join(const LIST *list1, const LIST *list2) | Concatenates two lists and returns the new list |
| BOOL | list_extend(LIST *list, const LIST *list_to_add) | Appends a list to the end of another list |
| int | list_length(const LIST *list) | Returns the number of elements in the list |
| int | list_capacity(const LIST *list) | Returns the capacity of the list |
| ITEM_TYPE | list_type(const LIST *list) | Returns the data type of the list |
| int | list_find(const LIST *list, ...) | Returns the index at which the item was found in the list, or -1 if not found |
| BOOL | list_append(LIST *list, ...) | Appends an item to the end of the list |
| BOOL | list_has_item(const LIST *list, ...) | Checks if an item exists in the list |
| BOOL | list_insert(LIST *list, int index, ...) | Inserts an item at the specified index in the list |
| LIST* | list_from_elements(unsigned int argc, ITEM_TYPE type, ...) | Creates a new list from the elements passed as arguments |
| LIST* | list_sorted(const LIST *list, BOOL reverse, int (*comparator)(void *item)) | Returns a sorted shallow-copy of the list |
| void | list_sort(LIST *list, BOOL reverse, int (*comparator)(void *item)) | Sorts a list in-place |
| ITEM* | list_get(const LIST *list, int index) | Returns the item at the specified index in the list |
| BOOL | list_set(const LIST *list, int index, ...) | Replaces the item at the specified index with a new item |
| LIST* | list_get_sublist(const LIST *list, int start, int end, BOOL deep_copy) | Returns a portion of a list as another list |
| ITEM** | list_to_array(const LIST *list) | Returns the elements of the list as an array |
