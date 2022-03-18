#ifndef DICTIONARY_NODE_H
#define DICTIONARY_NODE_H

#include <stdlib.h>
#include <string.h>

typedef struct DictionaryNode DictionaryNode;

struct DictionaryNode
{
    void *key;
    void *value;
};

DictionaryNode *create_dictionary_node(void *key, size_t key_size, void *value, size_t value_size);
void clear_dictionary_node(DictionaryNode *node);

#endif /* DICTIONARY_NODE_H */