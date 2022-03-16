#include "Node.h"
#include <stdio.h>
Node *create_node(void *data, size_t size)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if(node)
    {
        //TODO: fix this
        node->size = size;
        node->data = malloc(size);
        node->data = data;
        return node;
    }
    return NULL;
}

void free_node(Node *node)
{
    if(node)
    {
        if(node->data)
        {
            free(node->data);
        }
        free(node);
    }
}