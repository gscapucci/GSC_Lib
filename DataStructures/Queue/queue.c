#include "queue.h"

struct Queue {
    long long capacity, rear, front;
    int *value;
};

Queue* create_queue(size_t size)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if(queue)
    {
        queue->value = (int *)malloc(size * sizeof(int));
        queue->capacity = size;
        queue->rear = -1;
        queue->front = -1;
    }
}

void enqueue(Queue *queue, int value)
{
    if(queue)
    {
        if(queue->value)
        {
            if(queue->rear == queue->capacity - 1)
            {
                printf("Queue overflow\n");
            }
            else
            {
                if(queue->front == -1)
                {
                    queue->front = 0;
                }
                queue->rear += 1;
                queue->value[queue->rear] = value;
            }
        }
    }
}

void dequeue(Queue *queue)
{
    if(queue)
    {
        if(queue->value)
        {
            if(queue->front == -1 || queue->front > queue->rear)
            {
                printf("Queue underflow.\n");
            }
            else
            {
                queue->front += 1;
            }
        }
    }
}

int peek(Queue *queue)
{
    return queue->value[queue->front];
}

bool isFull(Queue *queue)
{
    return queue->rear == queue->capacity - 1 ? true : false;
}

bool isEmpty(Queue *queue)
{
    return queue->front == -1 ? true : false;
}

void print_queue(Queue *queue)
{
    for (size_t i = 0; i < queue->rear + 1; i++)
    {
        printf("%d ", queue->value[i]);
    }
    printf("\n");
}

void free_queue(Queue *queue)
{
    if(queue)
    {
        if(queue->value)
        {
            free(queue->value);
        }
        free(queue);
    }
}


bool test1()
{
    Queue *q = create_queue(10);
    for (size_t i = 0; i < q->capacity; i++)
    {
        enqueue(q, i);
    }
    if(!isFull)
    {
        free_queue(q);
        return false;
    }
    print_queue(q);
    for (size_t i = 0; i < q->capacity; i++)
    {
        dequeue(q);
    }
    if(!isEmpty(q))
    {
        free_queue(q);
        return false;
    }
    free_queue(q);
    return true;
}
bool test2()
{
    Queue *q = create_queue(1);
    enqueue(q, 1);
    printf("%d", peek(q));

}
bool test3();
bool test4();
bool test5();
bool test6();