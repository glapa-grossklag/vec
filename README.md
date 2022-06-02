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
```

# Documentation

There is one type defined for each `#include`, e.g., `vec_int_t`. These are
created dynamically using `vec_int_new()` and freed using
`vec_int_delete()`.

```c
vec_int_t *vec_int_new(void);

void vec_int_delete(vec_int_t *);
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