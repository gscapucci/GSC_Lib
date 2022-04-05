#include "Dictionary.h"

int (*comapre_node)(void *data1, void *data2);

int _compare(void *data1, void *data2);

void insert_dict(Dictionary *self, void *key, size_t key_size, void *value, size_t value_size);
bool search_dict_node(Dictionary *self, void *data);
void *get_dict_node_value(Dictionary *self, void *data);
size_t get_lengh(Dictionary *self);
DictionaryNode *take_next(Dictionary *self);
void *get_at(Dictionary *self, size_t index);


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
        clear_dictionary_node(node);
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

size_t get_lengh(Dictionary *self)
{
    if(self)
    {
        return self->_tree.number_of_nodes;
    }
    fprintf(stderr, "invalid input");
    exit(1);
}

void *get_at(Dictionary *self, size_t index)
{
    if(self)
    {
        DictionaryNode *data = (DictionaryNode *)self->_tree.get_at(&self->_tree, index);
        if(data == NULL)
        {
            fprintf(stderr, "error in get_at function");
            exit(1);
        }
        return data;
    }
    fprintf(stderr, "invalid input");
    exit(1);
}

DictionaryNode *take_next(Dictionary *self)
{
    if(self)
    {
        if(self->lengh(self) == 0)
        {
            fprintf(stderr, "dictonary is empty");
            exit(1);
        }
        if(self->ite.pos == DICT_BEG)
        {
            self->ite.index = 0;
        }
        void *data = self->get_at(self, self->ite.index);
        self->ite.index++;
        if(self->ite.index == self->lengh(self))
        {
            self->ite.pos = DICT_END;
        }
        return (DictionaryNode *)data;
    }
    fprintf(stderr, "invalif input");
    exit(1);
}

Dictionary create_dictionary(int (*compare_key)(void *key1, void *key2))
{
    Dictionary dict;
    comapre_node = compare_key;
    dict.get = get_dict_node_value;
    dict.search = search_dict_node;
    dict.insert = insert_dict;
    dict._tree = create_avltree(_compare);
    dict.lengh = get_lengh;
    dict.get_at = get_at;
    dict.take_next = take_next;
    dict.ite.pos = DICT_BEG;
    dict.ite.index = 0;
    return dict;
}

void clear_dictionary(Dictionary *dict)
{
    if(dict)
    {
        clear_avltree(&(dict->_tree));
    }
}