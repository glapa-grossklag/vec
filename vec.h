/*
 * Copyright © 2022 Miles Glapa-Grossklag
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the “Software”), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Configuration --------------------------------------------------------------

#ifndef TYPE
#error "TYPE must be defined"
#endif

#ifndef NAME
#define NAME TYPE

// NAME wasn't defined before, so it shouldn't pollute the namespace. We'll
// undefine it later.
#define UNDEF_NAME_LATER
#endif

#ifndef IS_EQUAL

// By default, `char *`s are compared using `strcmp` and everything else by
// `==`.
#define IS_EQUAL(a, b) _Generic((b),                    \
    char *:  (strcmp((char *) (a), (char *) (b)) == 0), \
    default: ((a) == (b))                               \
)

#define UNDEF_IS_EQUAL_LATER
#endif

// Macros ---------------------------------------------------------------------

#define CONCATENATE4(a, b, c, d) a ## b ## c ## d

// SUFFIX allows easier combining of tokens. E.g., if `NAME` was defined as
// `int`, then `SUFFIX(combobulate)` would evaluate to `vec_int_combobulate`.
#define SUFFIX_HELPER(S, N) CONCATENATE4(vec_, N, _, S)
#define SUFFIX(S) SUFFIX_HELPER(S, NAME)

// Implementation -------------------------------------------------------------

#define VEC() SUFFIX(t)
#define FUNCTION(S) SUFFIX(S)

typedef struct {
    size_t size;
    size_t capacity;
    TYPE *elements;
} VEC();

static inline
VEC() *
FUNCTION(new) (void) {
    VEC() *v = malloc(sizeof(*v));
    assert(v);

    v->size = 0;
    v->capacity = 1;
    v->elements = malloc(sizeof(*v->elements));
    assert(v->elements);

    return v;
}

static inline
VEC() *
FUNCTION(with_capacity) (size_t capacity) {
    VEC() *v = malloc(sizeof(*v));
    assert(v);

    v->size = 0;
    v->capacity = capacity;
    v->elements = malloc(capacity * sizeof(*v->elements));
    assert(v->elements);

    return v;
}

static inline
void
FUNCTION(delete) (VEC() *v) {
    free(v->elements);
    free(v);
}

static inline
TYPE
FUNCTION(get) (VEC() *v, size_t i) {
    assert(i < v->size);

    return v->elements[i];
}

static inline
void
FUNCTION(set) (VEC() *v, size_t i, TYPE x) {
    assert(i < v->size);

    v->elements[i] = x;
}

static inline
void
FUNCTION(push) (VEC() *v, TYPE x) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->elements = realloc(v->elements, v->capacity * sizeof(*v->elements));
        assert(v->elements);
    }

    v->elements[v->size] = x;
    v->size += 1;
}

static inline
TYPE
FUNCTION(pop) (VEC() *v) {
    assert(v->size > 0);
    v->size -= 1;
    return v->elements[v->size];
}

static inline
size_t
FUNCTION(size) (VEC() *v) {
    return v->size;
}

static inline
bool
FUNCTION(is_empty) (VEC() *v) {
    return v->size == 0;
}

static inline
void
FUNCTION(resize) (VEC() *v, size_t s, TYPE x) {
    if (s > v->capacity) {
        v->capacity = s;
        v->elements = realloc(v->elements, v->capacity * sizeof(*v->elements));
        assert(v->elements);
    }

    for (size_t i = v->size; i < s; i += 1) {
        v->elements[i] = x;
    }

    v->size = s;
}

static inline
void
FUNCTION(clear) (VEC() *v) {
    v->size = 0;
}

static inline
bool
FUNCTION(contains) (VEC() *v, TYPE x) {
    // These diagnostics have to be temporarily disabled because the
    // `_Generic` macro isn't perfect at type-checking. Trust me, it'll
    // be okay! :)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wint-to-pointer-cast"

    for (size_t i = 0; i < v->size; i += 1) {
        if (IS_EQUAL(x, v->elements[i])) {
            return true;
        }
    }

    return false;
    #pragma GCC diagnostic pop
}

// Cleanup --------------------------------------------------------------------

#undef FUNCTION
#undef VEC
#undef SUFFIX
#undef SUFFIX_HELPER
#undef CONCATENATE4

#ifdef UNDEF_NAME_LATER
#undef NAME
#endif

#ifdef UNDEF_IS_EQUAL_LATER
#undef IS_EQUAL
#endif