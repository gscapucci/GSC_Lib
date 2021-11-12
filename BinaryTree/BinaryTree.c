#include "BinaryTree.h"

void BT_init(BinaryTree *bt)
{
    bt->numberOfNodes = 0;
    bt->root = NULL;
}

bool BT_add(BinaryTree *bt, int val)
{
    bool ret;
    ret = _BT_add(&bt->root, val);
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
    _BT_printTree(bt->root);
}

void BT_clear(BinaryTree *bt)
{
    _BT_clear(&(bt->root));
    bt->numberOfNodes = 0;
    bt->root = NULL;
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

void _BT_printTree(BTNode *root)
{
    static int height = 0;
    height++;
    if(root == NULL)
    {
        return;
    }
    _BT_printTree(root->right);
    for (size_t i = 0; i < height; i++)
    {
        printf("    ");
    }
    printf("%d\n", root->data);
    height--;
    _BT_printTree(root->left);
    height--;
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