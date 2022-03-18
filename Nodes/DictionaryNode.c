#include "DictionaryNode.h"

DictionaryNode *create_dictionary_node(void *key, size_t key_size, void *value, size_t value_size)
{
    DictionaryNode *node = (DictionaryNode *)malloc(sizeof(DictionaryNode));
    if(node)
    {
        node->key = malloc(key_size);
        memcpy(node->key, key, key_size);
        node->value = malloc(value_size);
        memcpy(node->value, value, value_size);
        return node;
    }
    return NULL;
}

void clear_dictionary_node(DictionaryNode *node)
{
    if(node)
    {
        if(node->key)
        {
            free(node->key);
            node->key = NULL;
        }
        if(node->value)
        {
            free(node->value);
            node->value = NULL;
        }
    }
}