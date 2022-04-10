#include "uint64_vector.h"

//-----------------------//
void set_uint64_vec_functions(Uint64_vec *vec);

void uint64_vec_push(Uint64_vec *self, uint64_t number);
void uint64_vec_pop(Uint64_vec *self);
uint64_t uint64_get_at(Uint64_vec *self, uint64_t index);
//-----------------------//

void set_uint64_vec_functions(Uint64_vec *vec)
{
    if(vec)
    {
        vec->Push = uint64_vec_push;
        vec->Pop = uint64_vec_pop;
        vec->Get_at = uint64_get_at;
        return;
    }
    fprintf(stderr, "invalid input function set_uint64_vec_functions");
    exit(1);
}

void uint64_vec_push(Uint64_vec *self, uint64_t number)
{
    if(self)
    {
        if(self->size >= self->capacity)
        {
            self->capacity += self->capacity;
            self->vector = (uint64_t *)realloc(self->vector, self->capacity);
        }
        self->vector[self->size] = number;
        return;
    }
    fprintf(stderr, "invalid input function uint64_vec_push");
    exit(1);
}

void uint64_vec_pop(Uint64_vec *self)
{
    if(self)
    {
        if(self->size == 0)
        {
            fprintf(stderr, "vector is empty");
            exit(1);
        }
        self->vector[self->size--];
        if((self->size <= self->capacity / 2) && (self->capacity > self->base_capacity))
        {
            self->capacity -= self->capacity;
            self->vector = (uint64_t *)realloc(self->vector, self->capacity);
        }
    }
    fprintf(stderr, "invalid input function uint64_vec_pop");
    exit(1);
}

uint64_t uint64_get_at(Uint64_vec *self, uint64_t index)
{
    if(self)
    {
        if(index >= self->size)
        {
            fprintf(stderr, "index out of range, max is %zu, your input: %zu", self->size - 1, index);
            exit(1);
        }
        return self->vector[index];
    }
    fprintf(stderr, "invalif input function uint64_get_at");
    exit(1);
}

Uint64_vec create_uint64_vec(size_t start_capacity)
{
    Uint64_vec vec;
    vec.capacity = start_capacity;
    vec.base_capacity = start_capacity;
    vec.size = 0;
    set_uint64_vec_functions(&vec);
    vec.vector = (uint64_t *)malloc(sizeof(uint64_t));
    return vec;
}

void clear_uint64_vec(Uint64_vec *vec)
{
    if(vec)
    {
        free(vec->vector);
        vec->vector = NULL;
        vec->size = 0;
        vec->capacity = vec->base_capacity;
        return;
    }
    fprintf(stderr, "invalid input");
    exit(1);
}