#include <assert.h>
#include <stdio.h>
#include <string.h>

// We'll define a little "pair" struct to use as an example.
typedef struct {
	char *key;
	char *value;
} Pair;

// The type of the vector is defined using `#define TYPE foo`.
#define TYPE Pair

// The name of the vector (i.e., what you see in the name of all functions)
// is defined using `#define NAME foo`. This is necessary when TYPE contains
// multiple tokens. By default, `NAME` is `TYPE`. For example:
//
// #define TYPE struct foo
// #define NAME foo
#define NAME pair

#include "vec.h"
#undef TYPE
#undef NAME

int main(void) {
	// A new type is defined, `vec_pair_t`, for a vector of pairs.
	// Similarly, all functions become `vec_pair_new` or `vec_pair_push`.
	vec_pair_t *v = vec_pair_new();

	// We can push things to the end of the vector.
	vec_pair_push(v, (Pair) {"Hello", "world!"});
	vec_pair_push(v, (Pair) {"Goodbye", "world!"});

	// Let's make sure we have the right pairs at the right indices.
	Pair p1 = vec_pair_get(v, 0);
	Pair p2 = vec_pair_get(v, 1);

	assert(strcmp(p1.key, "Hello") == 0);
	assert(strcmp(p2.key, "Goodbye") == 0);

	// We can resize the vector too.
	vec_pair_resize(v, 4, (Pair) {":3", "!"});

	assert(vec_pair_size(v) == 4);
	assert(strcmp(vec_pair_get(v, 2).key, ":3") == 0);
	assert(strcmp(vec_pair_get(v, 3).value, "!") == 0);

	// The third argument here is ignored, because we're truncating the vector.
	vec_pair_resize(v, 0, (Pair) {"", ""});
	assert(vec_pair_size(v) == 0);

	// Remember to delete the vectors! Memory is allocated dynamically.
	vec_pair_delete(v);
}