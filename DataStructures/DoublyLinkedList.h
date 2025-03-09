#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "../global_allocator.h"
#include <stdlib.h>

typedef struct DoublyLinkedList DoublyLinkedList;
typedef struct DoublyLinkedListNode DoublyLinkedListNode;

struct DoublyLinkedListNode {
    void *data;
    DoublyLinkedListNode *prev;
    DoublyLinkedListNode *next;
};

struct DoublyLinkedList {
    size_t data_size;
    size_t length;
    DoublyLinkedListNode *head;
    DoublyLinkedListNode *tail;
};

DoublyLinkedList create_doubly_linked_list(size_t data_size);
DoublyLinkedList delete_doubly_linked_list(DoublyLinkedList *list);

DoublyLinkedList *create_doubly_linked_list_heap(size_t data_size);
DoublyLinkedList *delete_doubly_linked_list_heap(DoublyLinkedList *list);




#endif /* DOUBLY_LINKED_LIST_H */