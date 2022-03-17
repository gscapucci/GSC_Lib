#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Node.h"
#include <stdio.h>

typedef struct AVLTree AVLTree;
typedef struct AVLTree_node AVLTree_node;
struct AVLTree
{
    AVLTree_node *root;
    void (*insert)(AVLTree *self, void *data, size_t size);
    void (*remove)(AVLTree *self, void *data);
    void (*print)(AVLTree *self);
};
/*
*your compare_function:
*   new nodes wil be at right if return value is 1
*   left if -1
*   ignored if 0
*/
AVLTree create_avltree(int (*compare_function)(void *data1, void *data2));
void clear_avltree(AVLTree *tree);


#endif /* AVL_TREE_H */