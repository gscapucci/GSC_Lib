#include "stack.h"

const int START_CAPACITY = 10;

struct Stack
{
    int *top;
    size_t size, capacity;
    int *array;
};

Stack* create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if(stack)
    {
        stack->capacity = START_CAPACITY;
        stack->size = 0;
        stack->array = (int *)malloc(START_CAPACITY * sizeof(int));
        stack->top = NULL;
        return stack;
    }
    return NULL;
}

void free_stack(Stack *stack)
{
    if(stack)
    {
        free(stack->array);
        free(stack);
    }
}

void push(Stack *stack, int value)
{
    if(stack)
    {
        stack->array[stack->size] = value;
        stack->top = &stack->array[stack->size];
        stack->size++;
        if(stack->size == stack->capacity)
        {
            stack->array = (int *)realloc(stack->array, stack->capacity * 2);
            stack->capacity *= 2;
        }
    }
}

void pop(Stack *stack)
{
    if(stack)
    {
        stack->size--;
        stack->top = &stack->array[stack->size - 1];
        if(stack->size == stack->capacity / 2 && stack->capacity > 10)
        {
            stack->array = (int *)realloc(stack->array, stack->capacity / 2);
            stack->capacity /= 2;
        }
    }
}

void print_top(Stack *stack)
{
    if(stack)
    {
        if(stack->top)
        {
            printf("\n%d\n", *stack->top);
        }
    }
}

void print_stack(Stack *stack)
{
    if(stack)
    {
        if(stack->array)
        {
            for (size_t i = 0; i < stack->size; i++)
            {
                printf(" %d", stack->array[i]);
            }
            printf("\n");
        }
    }
}