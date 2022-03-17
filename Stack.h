#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack;

#include "LinkedList.h"

struct Stack
{
    LinkedList list;
    size_t max_size, height;
    void *(*pop)(Stack *self);
    void *(*peak)(Stack *self);
    void (*push)(Stack *self, void *data, size_t size);
};

//if size == 0, will not have size limit
Stack create_stack(size_t size);
void clear_stack(Stack *stack);

#endif /* STACK_H */