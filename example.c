#include <assert.h>
#include <stdio.h>
#include <string.h>

// We'll define a little "pair" struct to use as an example.
typedef struct {
	char *key;
	char *value;
} pair;

// Note how we define the type of the vector. Multiple vectors of different
// types are possible as well -- simply include the file twice!
#define TYPE pair
#include "vec.h"
#undef TYPE

int main(void) {
	// A new struct is defined, `struct vec_pair`, for a vector of pairs.
	// Similarly, all functions become `vec_pair_new` or `vec_pair_push`.
	struct vec_pair *v = vec_pair_new();

	// We can push things to the end of the vector.
	vec_pair_push(v, (pair) {"Hello", "world!"});
	vec_pair_push(v, (pair) {"Goodbye", "world!"});

	// Let's make sure we have the right pairs at the right indices.
	pair p1 = vec_pair_get(v, 0);
	pair p2 = vec_pair_get(v, 1);

	assert(strcmp(p1.key, "Hello") == 0);
	assert(strcmp(p2.key, "Goodbye") == 0);

	// Remember to delete the vectors! Memory is allocated dynamically.
	vec_pair_delete(v);
}