#ifndef UINT64_VECTOR_H
#define UINT64_VECTOR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Uint64_vec Uint64_vec;

struct Uint64_vec
{
    uint64_t *vector;
    size_t capacity, size, base_capacity;
    void (*Push)(Uint64_vec *self, uint64_t number);
    void (*Pop)(Uint64_vec *self);
    uint64_t (*Get_at)(Uint64_vec *self, uint64_t index);
};

Uint64_vec create_uint64_vec(size_t start_capacity);
void clear_uint64_vec(Uint64_vec *vec);

#endif /* UINT64_VECTOR_H */