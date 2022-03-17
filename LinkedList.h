#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"
#include <errno.h>
#include <stdio.h>

typedef struct LinkedList_node LinkedList_node;
typedef struct LinkedList LinkedList;

struct LinkedList
{
    LinkedList_node *head;
    size_t length;
    void (*insert)(LinkedList *self, void *data, size_t size);
    void *(*get)(LinkedList *self, size_t index);
    void (*remove)(LinkedList *Self, size_t index);//TODO: remove function
};

LinkedList create_linked_list();
void clear_linked_list(LinkedList *list);

#endif /* LINKED_LIST_H */