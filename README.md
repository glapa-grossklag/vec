# vec

A silly, generic, vector for C. Please read [the documentation](./DOCUMENTATION.md)!

```c
#define TYPE int
#include "vec.h"
#undef TYPE
```

# Example

```c
#define TYPE int
#include "vec.h"
#undef TYPE

int main(void) {
	vec_int_t *v = vec_int_from((int[]) {3, 1, 4, 1, 5}, 5);

	assert(vec_int_contains(v, 1));
	assert(!vec_int_contains(v, 9));

	vec_int_push(v, 9);

	assert(vec_int_size(v) == 6);
	assert(vec_int_get(v, 5) == 9);
	assert(vec_int_contains(v, 9));

	vec_int_delete(v);
}
```