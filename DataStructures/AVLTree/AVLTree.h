#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct AVLNode
{
    int data, heightDiff;
    struct AVLNode *right, *left;
}AVLNode;

typedef struct AVLTree
{
    int numberOfNodes;
    struct AVLNode *root;
}AVLTree;

void AVLT_init(AVLTree *avl);
bool AVLT_add(AVLTree *avl, int val);
void AVLT_printInorder(AVLTree *avl);//todo
void AVLT_printPreorder(AVLTree *avl);//todo
void AVLT_printPostorder(AVLTree *avl);//todo
void AVLT_printTree(AVLTree *avl);//todo
void AVLT_remove(AVLTree *avl, int val);//todo
void AVLT_clear(AVLTree *avl);//todo

//internal functions//
AVLNode* _AVLT_newNode(int val);
bool _AVLT_add(AVLNode **root, int val);
void _AVLT_printInorder(AVLNode *root);//todo
void _AVLT_printPreorder(AVLNode *root);//todo
void _AVLT_printPostorder(AVLNode *root);//todo
void _AVLT_printTree(AVLNode *root, int *height);//todo
bool _AVLT_remove(AVLNode **root, int val);//todo
int _AVLT_findSub(AVLNode *root);//todo
int _AVLT_min(AVLNode *root);//todo
int _AVLT_max(AVLNode *root);//todo
void _AVLT_clear(AVLNode **root);

#endif /* AVL_TREE_H */