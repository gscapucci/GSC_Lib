#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../AVLTree.h"
#include "../Nodes/DictionaryNode.h"
#include <stdbool.h>

typedef struct Dictionary Dictionary;
typedef struct DictionaryIterator DictionaryIterator;

typedef enum IteratorPos
{
    DICT_BEG,
    DICT_CUR,
    DICT_END
}IteratorPos;
struct DictionaryIterator
{
    size_t index;
    IteratorPos pos;
};
struct Dictionary
{
    AVLTree _tree;
    DictionaryIterator ite;
    size_t (*lengh)(Dictionary *self);
    DictionaryNode *(*take_next)(Dictionary *self);
    void (*insert)(Dictionary *self, void *key, size_t key_size, void *value, size_t value_size);
    bool (*search)(Dictionary *self, void *data);
    void *(*get)(Dictionary *self, void *data);
    void *(*get_at)(Dictionary *self, size_t index);
    void (*remove)(Dictionary *self, void *data);//TODO: remove function
};

Dictionary create_dictionary(int (*compare_function)(void *data1, void *data2));
void clear_dictionary(Dictionary *dict);

#endif /* DICTIONARY_H */