#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "../global_allocator.h"

typedef struct Vector Vector;
typedef struct VectorIter VectorIter;


struct Vector {
    void *items;
    size_t size;
    size_t capacity;
    size_t data_size;
};

struct VectorIter {
    Vector *vec;
    size_t current_index;
};

Vector create_vector(size_t init_cap, size_t data_size);
void vector_push(Vector *vec, void *data);
void delete_vector(Vector *vec);
void vector_push(Vector *vec, void *data);
void *vector_at(Vector *vec, size_t index);
void vector_pop(Vector *vec);
void *vector_pop_copy(Vector *vec);
void clear(Vector *vec);
void delete_vector(Vector *vec);

VectorIter vector_iter_begin(Vector *vec);
bool vector_iter_end(VectorIter *iter);
void vector_iter_next(VectorIter *iter);
void *vector_iter_current(VectorIter *iter);


#endif /* VECTOR_H */
