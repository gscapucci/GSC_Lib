#include "AVLTree.h"

int (*compare)(void *data1, void *data2);

struct AVLTree_node
{
    Node *data;
    int height_diff;
    AVLTree_node *left, *right;
};

AVLTree_node *create_avltree_node(void *data, size_t size);
void clear_avltree_node(AVLTree_node *root);

//void insert_avltree();

AVLTree_node *create_avltree_node(void *data, size_t size)
{
    AVLTree_node *node = (AVLTree_node *)malloc(sizeof(AVLTree_node));
    if(node)
    {
        node->data = create_node(data, size);
        node->height_diff = 0;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    return NULL;
}

void clear_avltree_node(AVLTree_node *root)
{
    if(root)
    {
        clear_avltree_node(root->left);
        clear_avltree_node(root->right);
        clear_node(root->data);
        free(root->data);
    }
}

AVLTree create_avltree(int (*compare_function)(void *data1, void *data2))
{
    AVLTree tree;
    if(!compare_function)
    {
        fprintf(stderr, "Error: somethng is wrong with compare_function");
        exit(1);
    }
    compare = compare_function;
    tree.root = NULL;
    return tree;
}

void clear_avltree(AVLTree *tree)
{
    if(tree)
    {
        if(tree->root)
        {
            clear_avltree_node(tree->root);
            free(tree->root);
            tree->root = NULL;
        }
    }
}
