#include "AVLTree.h"

void AVLT_init(AVLTree *avl)
{
    avl->numberOfNodes = 0;
    avl->root = NULL;
}

void AVLT_clear(AVLTree *avl)
{
    _AVLT_clear(&(avl->root));
    avl->numberOfNodes = 0;
    avl->root = NULL;
}

bool AVLT_add(AVLTree *avl, int val)
{
    bool ret = _AVLT_add(&avl->root, val);
    if(!ret)
    {
        printf("Value %d already exist in tree.\n", val);
    }
    return ret;
}

void _AVLT_clear(AVLNode **root)
{
    if((*root) == NULL)
    {
        return;
    }
    _AVLT_clear(&(*root)->right);
    _AVLT_clear(&(*root)->left);
    free(*root);
}

AVLNode* _AVLT_newNode(int val)
{
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = val;
    node->heightDiff = 0;
    node->left = NULL;
    node->right = NULL;
}


bool _AVLT_add(AVLNode **root, int val)
{
    if((*root) == NULL)
    {
        *root = _AVLT_newNode(val);
        return true;
    }
    if(val > (*root)->data)
    {
        return _AVLT_add(&(*root)->right, val);
    }
    if(val < (*root)->data)
    {
        return _AVL_add(&(*root)->left, val);
    }
    return false;
}