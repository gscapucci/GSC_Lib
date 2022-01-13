#include "stack.h"

struct Stack
{
    int64_t *value, *top;
    uint64_t size, capacity;
};

Stack* create_stack(size_t capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if(stack)
    {
        stack->value = (int64_t *)malloc(capacity * sizeof(int64_t));
        if(!stack->value)
        {
            printf("could not allocate for value.\n");
        }
        stack->size = 0;
        stack->top = NULL;
        stack->capacity = capacity;
        return stack;
    }
    else
    {
        printf("could not allocate for stack.\n");
    }
    return NULL;
}

void push(Stack *stack, int64_t value)
{
    if(stack)
    {
        if(stack->size == stack->capacity)
        {
            printf("Stack is full.\n");
            return;
        }
        stack->value[stack->size] = value;
        stack->top = &stack->value[stack->size];
        stack->size++;
    }
}

void pop(Stack *stack)
{
    if(stack)
    {
        if(stack->size != 0)
        {
            stack->size--;
        }
    }
}

void print_stack(Stack *stack)
{
    if(stack)
    {
        if(stack->size == 0)
        {
            printf("Stack is empty.\n");
        }
        for (size_t i = 0; i < stack->size; i++)
        {
            printf(" %ld", stack->value[i]);
        }
    }
}

void free_stack(Stack *stack)
{
    if(stack)
    {
        free(stack->value);
        free(stack);
    }
}

uint64_t sizeof_stack(Stack *stack)
{
    uint64_t size = sizeof(stack);
    size += stack->size * sizeof(int64_t);
    return size;
}

uint64_t get_capacity(Stack *stack)
{
    if(stack)
    {
        return stack->capacity;
    }
    return 0;
}

uint64_t get_size(Stack *stack)
{
    if(stack)
    {
        return stack->size;
    }
    return 0;
}

uint64_t get_top(Stack *stack)
{
    if(stack)
    {
        if(stack->top)
        {
            return *stack->top;
        }
    }
    return 0;
}