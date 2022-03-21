#include "Dictionary.h"

int (*comapre_node)(void *data1, void *data2);

int _compare(void *data1, void *data2);

void insert_dict(Dictionary *self, void *key, size_t key_size, void *value, size_t value_size);
bool search_dict_node(Dictionary *self, void *data);
void *get_dict_node_value(Dictionary *self, void *data);

int _compare(void *data1, void *data2)
{
    return comapre_node(data1, (*(DictionaryNode *)data2).key);
}

void insert_dict(Dictionary *self, void *key, size_t key_size, void *value, size_t value_size)
{
    if(self)
    {
        DictionaryNode *node = create_dictionary_node(key, key_size, value, value_size);
        self->_tree.insert(&self->_tree, node, sizeof(DictionaryNode) + key_size + value_size);
        free(node);
    }
}

bool search_dict_node(Dictionary *self, void *data)
{
    if(self)
    {
        if(self->_tree.get(&self->_tree, data))
        {
            return true;
        }
    }
    return false;
}

void *get_dict_node_value(Dictionary *self, void *data)
{
    if(self)
    {
        return (*(DictionaryNode *)self->_tree.get(&self->_tree, data)).value;
    }
    fprintf(stderr, "not found");
    return NULL;
}


Dictionary create_dictionary(int (*compare_key)(void *key1, void *key2))
{
    Dictionary dict;
    comapre_node = compare_key;
    dict.get = get_dict_node_value;
    dict.search = search_dict_node;
    dict.insert = insert_dict;
    dict._tree = create_avltree(_compare);
    return dict;
}

void clear_dictionary(Dictionary *dict)
{
    if(dict)
    {
        clear_avltree(&(dict->_tree));
    }
}