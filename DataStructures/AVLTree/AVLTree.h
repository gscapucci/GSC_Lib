#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct AVLTNode
{
    int data, balance;
    struct AVLTNode *right, *left;
}AVLTNode;

typedef struct AVLTree
{
    int numberOfNodes;
    struct AVLTNode *root;
}AVLTree;

void AVLT_init(AVLTree *avl);
bool AVLT_add(AVLTree *avl, int val);
void AVLT_printInorder(AVLTree *avl);//todo
void AVLT_printPreorder(AVLTree *avl);//todo
void AVLT_printPostorder(AVLTree *avl);//todo
void AVLT_printTree(AVLTree *avl);
void AVLT_remove(AVLTree *avl, int val);
void AVLT_clear(AVLTree *avl);

//internal functions//
AVLTNode* _AVLT_newNode(int val);
bool _AVLT_add(AVLTNode **root, int val);
void _AVLT_printInorder(AVLTNode *root);//todo
void _AVLT_printPreorder(AVLTNode *root);//todo
void _AVLT_printPostorder(AVLTNode *root);//todo
void _AVLT_printTree(AVLTNode *root, int *height);
bool _AVLT_remove(AVLTNode **root, int val);
int _AVLT_findSub(AVLTNode *root);
int _AVLT_min(AVLTNode *root);
int _AVLT_max(AVLTNode *root);
void _AVLT_clear(AVLTNode **root);
void _AVLT_rotate(AVLTNode **root);
AVLTNode* _AVLT_rotateRight(AVLTNode *root);
AVLTNode* _AVLT_rotateLeft(AVLTNode *root);
int _AVLT_correctBalance(AVLTNode *root);

#endif /* AVL_TREE_H */