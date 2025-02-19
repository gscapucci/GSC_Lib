#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../global_allocator.h"

typedef struct Stack Stack;

typedef enum {
    STACK_COPY,
    STACK_MOVE
} StackMode;

struct Stack {
    void *items;
    size_t capacity;
    size_t data_size;
    size_t size;
    StackMode mode;
};


Stack create_stack(size_t init_size, size_t data_size, StackMode mode);
void delete_stack(Stack *stack);

void stack_push(Stack *stack, void *data);

void stack_pop(Stack *stack, void *out);
void stack_peek(Stack *stack, void *out);
bool stack_is_empty(const Stack *stack);
bool stack_reserve(Stack *stack, size_t new_capacity);
void stack_clear(Stack *stack);
void stack_shrink_to_fit(Stack *stack);


#endif /* STACK_H */