#ifndef STACK_TEST_H
#define STACK_TEST_H

#include <assert.h>
#include <stdio.h>
#include "../GSC_Lib.h"

void test_create_stack() {
    Stack stack = create_stack(10, sizeof(int), STACK_COPY);
    assert(stack.size == 0);
    assert(stack.capacity == 10);
    assert(stack.data_size == sizeof(int));
    delete_stack(&stack);
    printf("test_create_stack passed!\n");
}

void test_stack_push() {
    Stack stack = create_stack(2, sizeof(int), STACK_COPY);
    int data1 = 10, data2 = 20, data3 = 30;

    stack_push(&stack, &data1);
    stack_push(&stack, &data2);
    stack_push(&stack, &data3);

    assert(stack.size == 3);
    assert(stack.capacity == 4); // Capacidade dobrou
    
    int top;
    stack_peek(&stack, &top);
    assert(top == 30);

    delete_stack(&stack);
    printf("test_stack_push passed!\n");
}

void test_stack_pop() {
    Stack stack = create_stack(5, sizeof(int), STACK_COPY);
    int data1 = 100, data2 = 200;

    stack_push(&stack, &data1);
    stack_push(&stack, &data2);

    int popped;
    stack_pop(&stack, &popped);
    assert(popped == 200);
    assert(stack.size == 1);

    stack_pop(&stack, &popped);
    assert(popped == 100);
    assert(stack.size == 0);

    stack_pop(&stack, &popped); // Pop em pilha vazia
    assert(stack.size == 0);

    delete_stack(&stack);
    printf("test_stack_pop passed!\n");
}

void test_stack_peek() {
    Stack stack = create_stack(5, sizeof(int), STACK_COPY);
    int data1 = 50;

    stack_push(&stack, &data1);

    int peeked;
    stack_peek(&stack, &peeked);
    assert(peeked == 50);
    assert(stack.size == 1);

    delete_stack(&stack);
    printf("test_stack_peek passed!\n");
}

void test_stack_clear() {
    Stack stack = create_stack(5, sizeof(int), STACK_COPY);
    int data = 42;

    stack_push(&stack, &data);
    stack_push(&stack, &data);

    stack_clear(&stack);
    assert(stack.size == 0);
    assert(stack.capacity == 5); // Capacidade não muda

    delete_stack(&stack);
    printf("test_stack_clear passed!\n");
}

void test_delete_stack() {
    Stack stack = create_stack(5, sizeof(int), STACK_COPY);
    int data = 123;
    stack_push(&stack, &data);

    delete_stack(&stack);
    assert(stack.items == NULL);
    assert(stack.size == 0);
    assert(stack.capacity == 0);

    printf("test_delete_stack passed!\n");
}

void stack_test() {
    test_create_stack();
    test_stack_push();
    test_stack_pop();
    test_stack_peek();
    test_stack_clear();
    test_delete_stack();
}

#endif /* STACK_TEST_H */
