# vec

A silly, generic, vector for C.

```c
#define TYPE int
#include "vec.h"
#undef TYPE
```

# Configuration

```c
// The type of each element in a vector.
#define TYPE int

// The name used to define types and functions. By default, this is equal to
// TYPE. This is necessary if TYPE could not be used in an identifier, for
// example `struct foo` or `char *`.
#define NAME int

typedef struct {
	char *key;
	char *value;
} Pair;

// The macro used to determine equality of members of a vector.
//
// NOTE: This is built-in for all integral types (e.g., `int`, `size_t`).
// Likewise, this is built-in for `char *`s using `strcmp`.
#define IS_EQUAL(a, b) ((a).key == (b).key && (a).value == (b).value)
```

One can `#include` multiple times, creating multiple vector types.

```c
#define TYPE int
#include "vec.h"
#undef TYPE

#define TYPE char *
#define NAME str
#include "vec.h"
#undef TYPE
#undef NAME

#define TYPE Pair
#define NAME pair
#define IS_EQUAL(a, b) ((a).key == (b).key && (a).value == (b).value)
#include "vec.h"
#undef TYPE
#undef NAME
#undef IS_EQUAL
```

# Documentation

There is one type defined for each `#include`, e.g., `vec_int_t`. These are
created dynamically using `vec_int_new()` and freed using
`vec_int_delete()`.

```c
vec_int_t *vec_int_new(void);

void vec_int_delete(vec_int_t *);
```

A more specialized version of `new` is available, `vec_int_with_capacity`, to
create vectors with a given capacity (*not* a given size). This allows you to
use knowledge you may have about the future size of a vector to minimize memory
allocations.

```c
vec_int_t *vec_int_with_capacity(size_t);
```

To push and pop elements from a vector, there are `vec_int_push()` and
`vec_int_pop()`. Popping will fail an assertion if there are no elements in
the vector, so it's the caller's responsibility to ensure the vector is
non-empty.

```c
void vec_int_push(vec_int_t *, int);

int vec_int_pop(vec_int_t *);
```

To get and set specific elements in a vector by index, there are `vec_int_get
()` and `vec_int_set()`. These both fail an assertion if the index is out of
bounds, so it's the caller's responsibility to ensure the index is
in-bounds.

```c
void vec_int_get(vec_int_t *, size_t);

void vec_int_set(vec_int_t *, size_t, int);
```

To retrieve the number of elements in the vector, there is `vec_int_size()`.

```c
size_t vec_int_size(vec_int_t *);
```

To determine if a vector is empty, there is `vec_int_is_empty()`.

```c
bool vec_int_is_empty(vec_int_t *);
```

To resize a vector, there is `vec_int_resize()`. If the new size is greater
than the current size, each new slot is filled with `x`. If the new size if
less than the current size, the vector is truncated and `x` is not used.

```c
void vec_int_resize(vec_int_t *, size_t, int x);
```

To clear everything in a vector, there is `vec_int_clear()`. This is done in
constant time.

```c
void vec_int_clear(vec_int_t *);
```

To determine if a vector contains an element, there is `vec_int_contains
()`. This relies on `IS_EQUAL` (see configuration), and is supported for
`char *`s and anything that can be compared with `==`. You're free to redefine
equality for user-defined types.

```c
void vec_int_contains(vec_int_t *, int);
```