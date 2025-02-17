#ifndef VECTOR_TEST_H
#define VECTOR_TEST_H

#include <assert.h>
#include "../GSC_Lib.h"

void test_create_vector() {
    Vector vec = create_vector(10, sizeof(int));
    assert(vec.size == 0);
    assert(vec.capacity == 10);
    assert(vec.data_size == sizeof(int));
    delete_vector(&vec);
    printf("test_create_vector passed!\n");
}

void test_vector_push() {
    Vector vec = create_vector(2, sizeof(int));
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;

    vector_push(&vec, &data1);
    vector_push(&vec, &data2);
    vector_push(&vec, &data3);

    assert(vec.size == 3);
    assert(vec.capacity == 4); // Capacidade dobrou
    assert(*(int *)vector_at(&vec, 0) == 10);
    assert(*(int *)vector_at(&vec, 1) == 20);
    assert(*(int *)vector_at(&vec, 2) == 30);

    delete_vector(&vec);
    printf("test_vector_push passed!\n");
}

void test_vector_at() {
    Vector vec = create_vector(5, sizeof(int));
    int data1 = 100;
    int data2 = 200;

    vector_push(&vec, &data1);
    vector_push(&vec, &data2);

    assert(*(int *)vector_at(&vec, 0) == 100);
    assert(*(int *)vector_at(&vec, 1) == 200);
    assert(vector_at(&vec, 2) == NULL); // Fora dos limites

    delete_vector(&vec);
    printf("test_vector_at passed!\n");
}

void test_vector_pop() {
    Vector vec = create_vector(5, sizeof(int));
    int data1 = 100;
    int data2 = 200;

    vector_push(&vec, &data1);
    vector_push(&vec, &data2);

    vector_pop(&vec);
    assert(vec.size == 1);
    assert(*(int *)vector_at(&vec, 0) == 100);

    vector_pop(&vec);
    assert(vec.size == 0);

    vector_pop(&vec); // Pop em um vetor vazio
    assert(vec.size == 0);

    delete_vector(&vec);
    printf("test_vector_pop passed!\n");
}

void test_vector_pop_copy() {
    Vector vec = create_vector(5, sizeof(int));
    int data1 = 100;
    int data2 = 200;

    vector_push(&vec, &data1);
    vector_push(&vec, &data2);

    int *popped_data = (int *)vector_pop_copy(&vec);
    assert(*popped_data == 200);
    assert(vec.size == 1);
    dealloc(popped_data);

    popped_data = (int *)vector_pop_copy(&vec);
    assert(*popped_data == 100);
    assert(vec.size == 0);
    dealloc(popped_data);

    popped_data = (int *)vector_pop_copy(&vec); // Pop em um vetor vazio
    assert(popped_data == NULL);

    delete_vector(&vec);
    printf("test_vector_pop_copy passed!\n");
}

void test_clear() {
    Vector vec = create_vector(5, sizeof(int));
    int data1 = 100;
    int data2 = 200;

    vector_push(&vec, &data1);
    vector_push(&vec, &data2);

    clear(&vec);
    assert(vec.size == 0);
    assert(vec.capacity == 5); // Capacidade não muda

    delete_vector(&vec);
    printf("test_clear passed!\n");
}

void test_delete_vector() {
    Vector vec = create_vector(5, sizeof(int));
    int data1 = 100;
    int data2 = 200;

    vector_push(&vec, &data1);
    vector_push(&vec, &data2);

    delete_vector(&vec);
    assert(vec.items == NULL);
    assert(vec.size == 0);
    assert(vec.capacity == 0);

    printf("test_delete_vector passed!\n");
}


void vector_test() {
    test_create_vector();
    test_vector_push();
    test_vector_at();
    test_vector_pop();
    test_vector_pop_copy();
    test_clear();
    test_delete_vector();
}

#endif /* VECTOR_TEST_H */