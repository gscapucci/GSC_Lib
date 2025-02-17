#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../global_allocator.h"

typedef struct Vector Vector;


struct Vector {
    void *items;
    size_t size;
    size_t capacity;
    size_t data_size;
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

#endif /* VECTOR_H */
