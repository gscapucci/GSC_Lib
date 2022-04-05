#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../AVLTree.h"
#include "../Nodes/DictionaryNode.h"
#include <stdbool.h>
typedef struct Dictionary Dictionary;

struct Dictionary
{
    AVLTree _tree;
    size_t (*lengh)(Dictionary *self);
    void (*insert)(Dictionary *self, void *key, size_t key_size, void *value, size_t value_size);
    bool (*search)(Dictionary *self, void *data);
    void *(*get)(Dictionary *self, void *data);
    void (*remove)(Dictionary *self, void *data);//TODO: remove function
};

Dictionary create_dictionary(int (*compare_function)(void *data1, void *data2));
void clear_dictionary(Dictionary *dict);

#endif /* DICTIONARY_H */