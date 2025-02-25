#include "Vector.h"


Vector create_vector(size_t init_cap, size_t data_size, void (*destructor)(void*), void (*copy_data)(void *,void *)) {
    Vector vec;
    if(init_cap == 0) {
        fprintf(stderr, "in '%s' init_cap must be greater than zero.\n", __func__);
        exit(1);
    }
    if(data_size == 0) {
        fprintf(stderr, "in '%s' data_size must be greater than zero.\n", __func__);
        exit(1);
    }
    vec.capacity = init_cap;
    vec.data_size = data_size;
    vec.size = 0;
    vec.items = allocate(data_size * init_cap);
    memset(vec.items, 0, data_size * init_cap);
    vec.delete_data = destructor;
    vec.copy_data = copy_data;
    return vec;
}

//vector uses memcpy to copy, TODO: change to user define copy function
void vector_push(Vector *vec, void *data) {
    if(!vec) return;
    if(vec->size >= vec->capacity) {
        vec->capacity *= 2;
        vec->items = reallocate(vec->items, vec->capacity * vec->data_size);
        if(!vec->items) {
            fprintf(stderr, "reallocation fail in '%s'", __func__);
            exit(1);
        }
    }
    if(vec->copy_data) {
        vec->copy_data((uint8_t*)vec->items + (vec->size * vec->data_size), data);
    } else {
        memcpy((uint8_t*)vec->items + (vec->size * vec->data_size), data, vec->data_size);
    }
    vec->size++;
}

void *vector_at(Vector *vec, size_t index) {
    if(!vec || index >= vec->size) return NULL;
    return (uint8_t*)vec->items + (index * vec->data_size);
}

void vector_pop(Vector *vec) {
    if(!vec || vec->size == 0) return;
    vec->size--;
    if(vec->delete_data) vec->delete_data((char *)vec->items + (vec->size * vec->data_size));
}

//TODO: Change memcpy to user define copy function
void *vector_pop_copy(Vector *vec) {
    if(!vec || vec->size == 0) return NULL;
    vec->size--;
    void *data = allocate(vec->data_size);
    if(vec->copy_data) {
        vec->copy_data(data, (uint8_t*)vec->items + (vec->size * vec->data_size));
    } else {
        memcpy(data, (uint8_t*)vec->items + (vec->size * vec->data_size), vec->data_size);
    }
    return data;
}


void clear(Vector *vec) {
    if(!vec || !vec->items) return;
    deallocate(vec->items);
    *vec = create_vector(vec->capacity, vec->data_size, vec->delete_data, vec->copy_data);
}

void delete_vector(Vector *vec) {
    if(!vec || !vec->items) return;
    deallocate(vec->items);
    vec->items = NULL;
    vec->capacity = 0;
    vec->data_size = 0;
    vec->size = 0;
}

VectorIter vector_iter_begin(Vector *vec) {
    VectorIter iter;
    iter.vec = vec;
    iter.current_index = 0;
    return iter;
}


bool vector_iter_end(VectorIter *iter) {
    return iter->current_index >= iter->vec->size;
}
void vector_iter_next(VectorIter *iter) {
    if (!vector_iter_end(iter)) {
        iter->current_index++;
    }
}
void *vector_iter_current(VectorIter *iter) {
    if (vector_iter_end(iter)) {
        return NULL; // Fim da iteração
    }
    return (uint8_t *)iter->vec->items + (iter->current_index * iter->vec->data_size);
}

void vector_sort(Vector *vec, int (*compare)(const void *, const void *)) {
    if (!vec || !compare) return;
    qsort(vec->items, vec->size, vec->data_size, compare);
}

Vector vector_filter(Vector *vec, bool (*predicate)(const void *)) {
    Vector result = create_vector(vec->size, vec->data_size, vec->delete_data, vec->copy_data);
    for(size_t i = 0; i < vec->size; i++) {
        void *item = vector_at(vec, i);
        if(predicate(item)) {
            vector_push(&result, item);
        }
    }
    return result;
}