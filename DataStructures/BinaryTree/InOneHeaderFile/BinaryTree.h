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

void BT_init(BinaryTree *bt)
{
    bt->numberOfNodes = 0;
    bt->root = NULL;
}

bool BT_add(BinaryTree *bt, int val)
{
    bool ret = _BT_add(&bt->root, val);
    if(!ret)
    {
        printf("This value already exist in tree.\n");
        return false;
    }
    bt->numberOfNodes++;
    return true;
}

void BT_printInorder(BinaryTree *bt)
{
    if(bt->root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    _BT_printInorder(bt->root);
}

void BT_printPreorder(BinaryTree *bt)
{
    if(bt->root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    _BT_printPreorder(bt->root);
}

void BT_printPostorder(BinaryTree *bt)
{
    if(bt->root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    _BT_printPostorder(bt->root);
}

void BT_printTree(BinaryTree *bt)
{
    if(bt->root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    int height = 0;
    _BT_printTree(bt->root, &height);
}

void BT_clear(BinaryTree *bt)
{
    _BT_clear(&(bt->root));
    bt->numberOfNodes = 0;
    bt->root = NULL;
}

void BT_remove(BinaryTree *bt, int val)
{
    if(bt->root == NULL)
    {
        printf("Tree is empty.\n");
    }
    bool ret = _BT_remove(&(bt->root), val);
    if(!ret)
    {
        printf("This value do not exist in tree\n");
    }
}

BTNode* _BT_newNode(int val)
{
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    node->data = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bool _BT_add(BTNode** root, int val)
{
    if(*root == NULL)
    {
        *root = _BT_newNode(val);
        return true;
    }
    if(val == (*root)->data)
    {
        return false;
    }
    if(val > (*root)->data)
    {
        return _BT_add(&(*root)->right, val);
    }
    if(val < (*root)->data)
    {
        return _BT_add(&(*root)->left, val);
    }
}

void _BT_printInorder(BTNode *root)
{
    if(root == NULL)
    {
        return;
    }
    _BT_printInorder(root->right);
    printf("    %d", root->data);
    _BT_printInorder(root->left);
}

void _BT_printPreorder(BTNode *root)
{
    if(root == NULL)
    {
        return;
    }
    printf("    %d", root->data);
    _BT_printPreorder(root->right);
    _BT_printPreorder(root->left);
}

void _BT_printPostorder(BTNode *root)
{
    if(root == NULL)
    {
        return;
    }
    _BT_printPostorder(root->right);
    _BT_printPostorder(root->left);
    printf("    %d", root->data);
}

void _BT_printTree(BTNode *root, int *height)
{
    (*height)++;
    if(root == NULL)
    {
        return;
    }
    _BT_printTree(root->right, height);
    for (size_t i = 0; i < (*height); i++)
    {
        printf("    ");
    }
    printf("%d\n", root->data);
    (*height)--;
    _BT_printTree(root->left, height);
    (*height)--;
}

void _BT_clear(BTNode **root)
{
    if(*root == NULL)
    {
        return;
    }
    _BT_clear(&(*root)->left);
    _BT_clear(&(*root)->right);
    free(*root);
}

bool _BT_remove(BTNode **root, int val)
{
    if(*root == NULL)
    {
        return false;
    }
    if((*root)->data == val)
    {
        if((*root)->left == NULL && (*root)->right == NULL)
        {
            free(*root);
            *root = NULL;
            return true;
        }
        else
        {
            int sub = _BT_findSub(*root);
            (void)_BT_remove(root, sub);
            (*root)->data = sub;
            return true;
        }
    }
    else
    {
        bool retRight, retLeft;
        retRight = _BT_remove(&(*root)->right, val);
        retLeft = _BT_remove(&(*root)->left, val);

        return retRight || retLeft ? true : false;
    }
}

int _BT_findSub(BTNode *root)
{
    int *minRight = NULL, *maxLeft = NULL, Rdiff = 0, Ldiff = 0;
    if(root->right != NULL)
    {
        minRight = (int *)malloc(sizeof(int));
        *minRight = _BT_min(root->right);
        Rdiff = *minRight - root->data;
    }
    if(root->left != NULL)
    {
        maxLeft = (int *)malloc(sizeof(int));
        *maxLeft = _BT_max(root->left);
        Ldiff = root->data - *maxLeft;
    }
    if(minRight != NULL && maxLeft != NULL)
    {
        int max = *maxLeft, min = *minRight;
        free(minRight);
        free(maxLeft);
        return Rdiff < Ldiff ? min : max;
    }
    else if(minRight == NULL)
    {
        int max = *maxLeft;
        free(maxLeft);
        return max;
    }
    else
    {
        int min = *minRight;
        free(minRight);
        return min;
    }
}

int _BT_min(BTNode *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root->data;
}

int _BT_max(BTNode *root)
{
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root->data;
}

#endif /* BINARY_TREE_H*/