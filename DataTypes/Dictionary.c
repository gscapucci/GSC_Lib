#include "Dictionary.h"

void insert_dict(Dictionary *self, void *key, size_t key_size, void *value, size_t value_size)
{
    if(self)
    {
        DictionaryNode *node = create_dictionary_node(key, key_size, value, value_size);
        self->_tree.insert(&self->_tree, node, sizeof(DictionaryNode) + sizeof(key) + sizeof(value));
        free(node);
    }
}

Dictionary create_dictionary(int (*compare_function)(void *data1, void *data2), void (*print_function)(void *data))
{
    Dictionary dict;
    dict.insert = insert_dict;
    dict._tree = create_avltree(compare_function, print_function);
    return dict;
}

void clear_dictionary(Dictionary *dict)
{
    if(dict)
    {
        clear_avltree(&(dict->_tree));
    }
}