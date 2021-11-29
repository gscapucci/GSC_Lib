#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct BTNode BTNode;

typedef struct BinaryTree BinaryTree;

void BT_init(BinaryTree **bt);
bool BT_add(BinaryTree **bt, int val);
void BT_printInorder(BinaryTree *bt);
void BT_printPreorder(BinaryTree *bt);
void BT_printPostorder(BinaryTree *bt);
void BT_printTree(BinaryTree *bt);
void BT_clear(BinaryTree **bt);
void BT_remove(BinaryTree **bt, int val);



#endif /* BINARY_TREE_H*/