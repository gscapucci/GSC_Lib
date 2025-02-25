#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "../global_allocator.h"

typedef struct Vector Vector;
typedef struct VectorIter VectorIter;


struct Vector {
    void *items;
    size_t size;
    size_t capacity;
    size_t data_size;
    void (*delete_data)(void*);
    void (*copy_data)(void*, void*);
};

struct VectorIter {
    Vector *vec;
    size_t current_index;
};

/**
 * Creates a new vector with the specified initial capacity and data size.
 *
 * @param init_cap Initial capacity of the vector.
 * @param data_size Size of each element stored in the vector.
 * @param destructor Destruction function to free memory associated with the elements.
 *                  - Use NULL if the elements do not contain dynamically allocated memory.
 *                  - If the elements are pointers, the destructor should free the memory they point to.
 *                  - If the elements are structs, the destructor should only free memory allocated inside them.
 *                  - The destructor MUST NOT free the vector itself (i.e., do not call `deallocate` on the vector pointer).
 * @param copy_data Custom copy function for the elements.
 *                  - Use NULL to use the default copy (memcpy).
 *                  - Useful for deep copies of complex elements.
 * @return A new initialized vector.
 */
Vector create_vector(size_t init_cap, size_t data_size, void (*destructor)(void* vector), void (*copy_data)(void *dest, void *src));
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

void vector_sort(Vector *vec, int (*compare)(const void *, const void *));
Vector vector_filter(Vector *vec, bool (*predicate)(const void *));

#endif /* VECTOR_H */
