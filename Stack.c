#include "Stack.h"

void push_stack(Stack *self, void *data, size_t size)
{
    if(self)
    {
        if(self->max_size != 0 && self->height == self->max_size)
        {
            fprintf(stderr, "stack overflow");
            return;
        }
        self->list.insert(&(self->list), data, size);
        self->height++;
    }
}

void *pop_stack(Stack *self)
{
    if(self)
    {
        if(self->height == 0)
        {
            fprintf(stderr, "stack underflow");
            return NULL;
        }
        void *data = self->list.get(&(self->list), self->list.length - 1);
        self->list.remove(&self->list, self->list.length - 1);
        return data;
    }
    return NULL;
}

void *peak_stack(Stack *self)
{
    if(self)
    {
        if(self->height == 0)
        {
            fprintf(stderr, "stack underflow");
            return NULL;
        }
        return self->list.get(&(self->list), self->list.length - 1);
    }
        return NULL;
}

Stack create_stack(size_t max_size)
{
    Stack stack;
    stack.height = 0;
    stack.max_size = max_size;
    stack.list = create_linked_list();
    stack.peak = peak_stack;
    stack.push = push_stack;
    stack.pop = pop_stack;
    return stack;
}

void clear_stack(Stack *stack)
{
    if(stack)
    {
        clear_linked_list(&(stack->list));
        stack->height = 0;
        stack->max_size = 0;
    }
}