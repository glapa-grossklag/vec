#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define TYPE char *
#define NAME str
#include "vec.h"
#undef TYPE
#undef NAME

void test_string(void) {
	vec_str_t *v = vec_str_new();

	vec_str_push(v, "Hello");
	vec_str_push(v, "world!");

	assert(vec_str_contains(v, "Hello"));
	assert(!vec_str_contains(v, "Goodbye"));
	assert(vec_str_contains(v, "world!"));

	vec_str_pop(v);
	assert(vec_str_size(v) == 1);

	assert(!vec_str_contains(v, "world!"));

	vec_str_clear(v);
	assert(!vec_str_contains(v, "Hello"));

	vec_str_delete(v);
}

#define TYPE int
#define NAME int
#include "vec.h"
#undef TYPE
#undef NAME

void test_int(void) {
	vec_int_t *v = vec_int_from((int[]) {3, 1, 4, 1, 5}, 5);

	assert(vec_int_contains(v, 1));
	assert(vec_int_contains(v, 5));
	assert(!vec_int_contains(v, 6));
	assert(!vec_int_contains(v, 0));

	vec_int_resize(v, 30, 0);

	assert(vec_int_size(v) == 30);
	assert(vec_int_get(v, 29) == 0);
	assert(vec_int_contains(v, 0));

	vec_int_delete(v);
}

typedef struct {
	char *key;
	char *value;
} Pair;

#define TYPE Pair
#define NAME pair
#define IS_EQUAL(a, b) ((a).key == (b).key && (a).value == (b).value)
#include "vec.h"
#undef TYPE
#undef NAME
#undef IS_EQUAL

void test_pair(void) {
	vec_pair_t *v = vec_pair_new();

	vec_pair_push(v, (Pair) {"Hello", "world!"});
	vec_pair_push(v, (Pair) {"Good", "morning!"});

	assert(vec_pair_contains(v, (Pair) {"Good", "morning!"}));
	assert(!vec_pair_contains(v, (Pair) {"Goodbye", "evening!"}));

	vec_pair_delete(v);
}

int main(void) {
	test_string();
	test_int();
	test_pair();
	return EXIT_SUCCESS;
}