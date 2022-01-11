#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Stack Stack;

Stack* create_stack();
void free_stack(Stack *stack);
void pop(Stack *stack);
void push(Stack *stack, int value);
void print_stack(Stack *stack);
void print_top(Stack *stack);
void test();

#endif /* STACK_H */