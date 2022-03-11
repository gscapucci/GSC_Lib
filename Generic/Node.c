#include "Node.h"

void *get_node_data(Node *node);

void *get_node_data(Node *node)
{
    if(node)
    {
        if(node->data)
        {
            return node->data;
        }
    }
    return NULL;
}

Node *create_node(void *data, size_t size)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if(node)
    {
        node->size = size;
        node->data = (void *)malloc(size);
        memcpy(node->data, data, size);
        node->get_data = get_node_data;
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