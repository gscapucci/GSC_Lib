#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Queue Queue;
Queue* create_queue(size_t size);
void enqueue(Queue *queue, int value);
void dequeue(Queue *queue);
int peek(Queue *queue);
bool isFull(Queue *queue);
bool isEmpty(Queue *queue);
void print_queue(Queue *queue);
void free_queue(Queue *queue);

bool test1();
bool test2();
bool test3();
bool test4();
bool test5();
bool test6();

#endif /* QUEUE_H */