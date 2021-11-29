#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct AVLTNode AVLTNode;

typedef struct AVLTree AVLTree;

void AVLT_init(AVLTree **avl);
bool AVLT_add(AVLTree *avl, int val);
void AVLT_printInorder(AVLTree *avl);//todo
void AVLT_printPreorder(AVLTree *avl);//todo
void AVLT_printPostorder(AVLTree *avl);//todo
void AVLT_printTree(AVLTree *avl);
void AVLT_remove(AVLTree **avl, int val);
void AVLT_clear(AVLTree **avl);


#endif /* AVL_TREE_H */