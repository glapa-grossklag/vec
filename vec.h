#include <stdlib.h>
#include <assert.h>

#ifndef TYPE
#error "TYPE must be defined"
#endif

#define CONCATENATE2(a, b) a ## b
#define CONCATENATE3(a, b, c) a ## b ## c

#define VEC_STRUCT(T) CONCATENATE2(vec_, T)
struct VEC_STRUCT(TYPE) {
    size_t size;
    size_t capacity;
    TYPE *elements;
};

#define VEC_NEW(T) CONCATENATE3(vec_, T, _new)
struct VEC_STRUCT(TYPE) *VEC_NEW(TYPE) (void) {
    struct VEC_STRUCT(TYPE) *v = malloc(sizeof(*v));

    v->size = 0;
    v->capacity = 1;
    v->elements = malloc(sizeof(*v->elements));

    return v;
}

#define VEC_DELETE(T) CONCATENATE3(vec_, T, _delete)
void VEC_DELETE(TYPE) (struct VEC_STRUCT(TYPE) *v) {
    free(v->elements);
    free(v);
}

#define VEC_GET(T) CONCATENATE3(vec_, T, _get)
TYPE VEC_GET(TYPE) (struct VEC_STRUCT(TYPE) *v, size_t i) {
    assert(i < v->size);

    return v->elements[i];
}

#define VEC_SET(T) CONCATENATE3(vec_, T, _set)
void VEC_SET(TYPE) (struct VEC_STRUCT(TYPE) *v, size_t i, TYPE x) {
    assert(i < v->size);

    v->elements[i] = x;
}

#define VEC_PUSH(T) CONCATENATE3(vec_, T, _push)
void VEC_PUSH(TYPE) (struct VEC_STRUCT(TYPE) *v, TYPE x) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        assert((v->elements = realloc(v->elements, v->capacity * sizeof(TYPE))));
    }

    v->elements[v->size] = x;
    v->size += 1;
}

#define VEC_POP(T) CONCATENATE3(vec_, T, _pop)
TYPE VEC_POP(TYPE) (struct VEC_STRUCT(TYPE) *v) {
    assert(v->size > 0);
    if (v->size < v->capacity / 2) {
        v->capacity /= 2;
        assert((v->elements = realloc(v->elements, v->capacity * sizeof(TYPE))));
    }

    v->size -= 1;
    return v->elements[v->size];
}

#define VEC_SIZE(T) CONCATENATE3(vec_, T, _size)
inline size_t VEC_SIZE(TYPE) (struct VEC_STRUCT(TYPE) *v) {
    return v->size;
}