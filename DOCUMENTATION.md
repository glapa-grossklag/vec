# Macros

## `TYPE`

The macro [`TYPE`](#type) defines the type of each element in a vector. Defining [`TYPE`](#type) is **required** and will result in an error if it is not defined.

```c
#define TYPE int
#include "vec.h"
#undef TYPE
```

## `NAME`

The macro [`NAME`](#name) is required only if [`TYPE`](#type) is defined as something that could not be an identifier.

For example, if [`TYPE`](#type) is `char *`, one must define [`NAME`](#name) as well.

```c
#define TYPE char *
#define NAME str
#include "vec.h"
#undef TYPE
#undef NAME
```

## `IS_EQUAL`

```c
#define IS_EQUAL(a, b) ...
```

The macro [`IS_EQUAL`](#macro) should return `true` if `a` is the same as `b`. This macro is built-in for anything that can be compared using the `==` operator, as well `char *`s using `strcmp`.

To change the definition, define a macro that takes two arguments and returns `true` or `false`. The following is an example:

```c
struct pair {
	int first;
	int second;
};

#define IS_EQUAL(a, b) ((a).first == (b).first && (a).second == (b).second)
```

# Functions

Note, all the documentation below assumes [`TYPE`](#type) as been defined as `foo`.

```c
#define TYPE foo
```

## `new`

```c
vec_foo_t *vec_foo_new(void);
```

The function [`vec_foo_new()`](#new) dynamically creates and returns a pointer to a `vec_foo_t`. The caller is reponsible for freeing memory using [`vec_foo_delete()`](#delete). If memory cannot be allocated, `NULL` is returned.

## `delete`

```c
void vec_int_delete(vec_int_t *v);
```

The function [`vec_foo_delete()`](#delete) frees all memory associated with the vector `v`.

## `from`

```c
vec_foo_t *vec_foo_from(foo *a, size_t n);
```

The function [`vec_foo_from()`](#from) dynamically creates and returns a pointer to a `vec_foo_t`, filling the slots of the new vector with the first `n` elements of the array `a`. The caller is reponsible for freeing memory using [`vec_foo_delete()`](#delete).

## `with_capacity`

```c
vec_foo_t *vec_foo_with_capacity(size_t n);
```

The function [`vec_foo_with_capacity()`](#with_capacity) dynamically creates and returns a pointer to a `vec_foo_t` with the capacity to hold `n`. This allows you to use knowledge you may have about the future size of a vector to minimize memory allocations. The caller is reponsible for freeing memory using [`vec_foo_delete()`](#delete). If memory cannot be allocated, `NULL` is returned.

## `push`

```c
void vec_foo_push(vec_foo_t *v, foo x);
```

The function [`vec_foo_push()`](#push) appends `x` to `v`.

## `pop`

```c
foo vec_foo_pop(vec_foo_t *v);
```

The function [`vec_foo_pop()`](#pop) removes and returns the last element in `v`. It is the caller's responsibility to ensure the vector is not empty when [`vec_foo_pop()`](#pop) is called.

## `get`

```c
foo vec_foo_get(vec_foo_t *v, size_t i);
```

The function [`vec_foo_get`](#get) returns the element at index `i` of `v`. It is the caller's responsibility to ensure `i` is in-bounds.

## `set`

```c
void vec_foo_set(vec_foo_t *v, size_t i, foo x);
```

The function [`vec_foo_get`](#get) sets the element at index `i` of `v` to `x`. It is the caller's responsibility to ensure `i` is in-bounds.

## `size`

```c
size_t vec_foo_size(vec_foo_t *v);
```

The function [`vec_foo_size`](#size) returns the number of elements in `v`.

## `is_empty`

```c
bool vec_foo_is_empty(vec_foo_t *v);
```

The function [`vec_foo_is_empty`](#is_empty) returns `true` if `v` is empty, `false` otherwise.

## `resize`

```c
void vec_foo_resize(vec_foo_t *v, size_t s, foo x);
```

The function [`vec_foo_resize`](#resize) changes the size of `v` to `s`. If the new size is greater than the current size, each new slot is filled with `x`. If the new size if less than the current size, the vector is truncated and `x` is not used.

## `clear`

```c
void vec_foo_clear(vec_foo_t *v);
```

The function [`vec_foo_clear`](#clear) removes every element in `v`. This is done in constant time.

## `contains`

```c
void vec_foo_contains(vec_foo_t *v, foo x);
```

The function [`vec_foo_contains`](#contains) returns `true` if `v` contains `x`, `false` otherwise.

This relies on [`IS_EQUAL`](#is_equal), and thus is built-in for anything that can be compared using the `==` operator, as well `char *`s using `strcmp`.

## `copy`

```c
void vec_foo_copy(vec_foo_t *v);
```

The function [`vec_foo_copy`](#copy) returns a shallow copy of `v`.
