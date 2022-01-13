#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct Stack Stack;

Stack* create_stack(size_t capacity);
void test();
void push(Stack *stack, int64_t value);
void pop(Stack *stack);
void print_stack(Stack *stack);
void free_stack(Stack *stack);
uint64_t get_capacity(Stack *stack);
uint64_t get_size(Stack *stack);
uint64_t get_top(Stack *stack);
#endif /* STACK_H */