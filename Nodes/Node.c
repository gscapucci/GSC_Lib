#include "Node.h"
#include "string.h"

Node *create_node(void *data, size_t size)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if(node)
    {
        node->size = size;
        node->data = malloc(size);
        memcpy(node->data, data, size);
        return node;
    }
    return NULL;
}

void clear_node(Node *node)
{
    if(node)
    {
        if(node->data)
        {
            free(node->data);
            node->data = NULL;
        }
        node->size = 0;
    }
}