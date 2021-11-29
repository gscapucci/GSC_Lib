#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct BTNode
{
    int data;
    struct BTNode *left, *right;
}BTNode;

typedef struct BinaryTree
{
    int numberOfNodes;
    struct BTNode* root;
}BinaryTree;

void BT_init(BinaryTree *bt);
bool BT_add(BinaryTree *bt, int val);
void BT_printInorder(BinaryTree *bt);
void BT_printPreorder(BinaryTree *bt);
void BT_printPostorder(BinaryTree *bt);
void BT_printTree(BinaryTree *bt);
void BT_clear(BinaryTree *bt);
void BT_remove(BinaryTree *bt, int val);


//internal functions//
BTNode* _BT_newNode(int val);
bool _BT_add(BTNode **root, int val);
void _BT_printInorder(BTNode *root);
void _BT_printPreorder(BTNode *root);
void _BT_printPostorder(BTNode *root);
void _BT_printTree(BTNode *root, int *height);
void _BT_clear(BTNode **root);
bool _BT_remove(BTNode **root, int val);
int _BT_findSub(BTNode *root);
int _BT_min(BTNode *root);
int _BT_max(BTNode *root);

#endif /* BINARY_TREE_H*/