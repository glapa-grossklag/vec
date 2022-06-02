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

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#ifndef TYPE
#error "TYPE must be defined"
#endif

#ifndef NAME
#define NAME TYPE
#endif

#define CONCATENATE3(a, b, c) a ## b ## c
#define CONCATENATE4(a, b, c, d) a ## b ## c ## d

#define VEC_FUNCTION_HELPER(N, F) CONCATENATE4(vec_, N, _, F)
#define VEC_FUNCTION(F) VEC_FUNCTION_HELPER(NAME, F)

#define VEC_T_HELPER(N) CONCATENATE3(vec_, N, _t)
#define VEC_T() VEC_T_HELPER(NAME)

typedef struct {
    size_t size;
    size_t capacity;
    TYPE *elements;
} VEC_T();

static inline
VEC_T() *
VEC_FUNCTION(new) (void) {
    VEC_T() *v = malloc(sizeof(*v));

    v->size = 0;
    v->capacity = 1;
    v->elements = malloc(sizeof(*v->elements));

    return v;
}

static inline
void
VEC_FUNCTION(delete) (VEC_T() *v) {
    free(v->elements);
    free(v);
}

static inline
TYPE
VEC_FUNCTION(get) (VEC_T() *v, size_t i) {
    assert(i < v->size);

    return v->elements[i];
}

static inline
void
VEC_FUNCTION(set) (VEC_T() *v, size_t i, TYPE x) {
    assert(i < v->size);

    v->elements[i] = x;
}

static inline
void
VEC_FUNCTION(push) (VEC_T() *v, TYPE x) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        assert((v->elements = realloc(v->elements, v->capacity * sizeof(*v->elements))));
    }

    v->elements[v->size] = x;
    v->size += 1;
}

static inline
TYPE
VEC_FUNCTION(pop) (VEC_T() *v) {
    assert(v->size > 0);
    if (v->size < v->capacity / 2) {
        v->capacity /= 2;
        assert((v->elements = realloc(v->elements, v->capacity * sizeof(*v->elements))));
    }

    v->size -= 1;
    return v->elements[v->size];
}

static inline
size_t
VEC_FUNCTION(size) (VEC_T() *v) {
    return v->size;
}

static inline
bool
VEC_FUNCTION(is_empty) (VEC_T() *v) {
    return v->size == 0;
}

// We don't want to pollute the namespace.
#undef VEC_FUNCTION
#undef VEC_FUNCTION_HELPER
#undef VEC_T
#undef VEC_T_HELPER
#undef CONCATENATE4
#undef CONCATENATE3