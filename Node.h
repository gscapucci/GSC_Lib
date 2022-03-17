#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct Node Node;

struct Node
{
    void *data;
    size_t size;
};

Node *create_node(void *data, size_t size);
void clear_node(Node *node);

#endif /* NODE_H */