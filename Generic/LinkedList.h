#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"

typedef struct LinkedList LinkedList;
typedef struct LinkedList_node LinkedList_node;

struct LinkedList_node
{
    Node *node;
    LinkedList_node *next, *prev;
};

struct LinkedList
{
    LinkedList_node *head;
    size_t length;
};

LinkedList *create_linked_list()

#endif /* LINKED_LIST_H */