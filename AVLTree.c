#include "AVLTree.h"

#include <string.h>
typedef struct FunctionPointers
{
    int (*compare)(void *data1, void *data2);
    void (*print)(void *data);
}FP;

FP fp;

struct AVLTree_node
{
    Node *node_data;
    int height_diff;
    AVLTree_node *left, *right;
};

AVLTree_node *create_avltree_node(void *data, size_t size);
void clear_avltree_node(AVLTree_node *root);
int insert_avltree_node(AVLTree_node *root, void *data, size_t size);
void *search_node(AVLTree_node *root, void *data, size_t size);
void insert_avltree(AVLTree *self, void *data, size_t size);
void *get_avltree_node(AVLTree *self, void *data, size_t size);
void print_tree_node(AVLTree_node *root, int height);
void print_tree(AVLTree *self);

AVLTree_node *create_avltree_node(void *data, size_t size)
{
    AVLTree_node *node = (AVLTree_node *)malloc(sizeof(AVLTree_node));
    if(node)
    {
        node->node_data = create_node(data, size);
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
        clear_node(root->node_data);
        free(root->node_data);
    }
}

int insert_avltree_node(AVLTree_node *root, void *data, size_t size)
{
    switch (fp.compare(data, root->node_data->data))
    {
    case 1:
        if(root->right == NULL)
        {
            root->right = create_avltree_node(data, size);
            root->height_diff++;
            return 1;
        }
        else
        {
            int ret = insert_avltree_node(root->right, data, size);
            if(ret != 0)
            {
                root->height_diff++;
            }
            return ret;
        }

        break;
    case -1:
        if(root->left == NULL)
        {
            root->left = create_avltree_node(data, size);
            root->height_diff--;
            return -1;
        }
        else
        {
            int ret = insert_avltree_node(root->left, data, size);
            if(ret != 0)
            {
                root->height_diff--;
            }
            return ret;
        }
        break;
    case 0:
        memcpy(root->node_data->data, data, size);
        return 0;
        break;
    default:
        fprintf(stderr, "Error: compare function error!");
        exit(1);
        break;
    }
}

void *search_node(AVLTree_node *root, void *data, size_t size)
{
    if(root)
    {
        if(root->node_data)
        {
            if(root->node_data->data)
            {
                if(root->node_data->size > size)
                {
                    if(memcmp(root->node_data->data, data, root->node_data->size))
                    {
                        return root->node_data->data;
                    }
                }
                else if(memcmp(root->node_data->data, data, size))
                {
                    return root->node_data->data;
                }
                else
                {
                    void *p1 = NULL, *p2 = NULL;
                    if(root->left)
                    {
                        p1 = search_node(root->left, data, size);
                    }
                    if(root->right)
                    {
                        p2 = search_node(root->right, data, size);
                    }
                    if(p1 != NULL)
                    {
                        return p1;
                    }
                    else if(p2 != NULL)
                    {
                        return p1;
                    }
                }
            }
        }
    }
    return NULL;
}

void *get_avltree_node(AVLTree *self, void *data, size_t size)
{
    if(self)
    {
        return search_node(self->root, data, size);
    }
    return NULL;
}

void print_tree_node(AVLTree_node *root, int height)
{
    if(root->left)
    {
        print_tree_node(root->left, height + 1);
    }
    for (int i = 0; i < height; i++)
    {
        printf("    ");
    }
    fp.print(root->node_data->data);
    printf("\n");
    if(root->right)
    {
        print_tree_node(root->right, height + 1);
    }
}

void print_tree(AVLTree *self)
{
    if(self)
    {
        print_tree_node(self->root, 0);
    }
}

void insert_avltree(AVLTree *self, void *data, size_t size)
{
    if(!self->root)
    {
        self->root = create_avltree_node(data, size);
        return;
    }
    insert_avltree_node(self->root, data, size);
}

AVLTree create_avltree(int (*compare_function)(void *data1, void *data2), void (*print_function)(void *data))
{
    AVLTree tree;
    if(!compare_function)
    {
        fprintf(stderr, "Error: somethng is wrong with compare_function");
        exit(1);
    }
    if(!print_function)
    {
        fprintf(stderr, "Error: somethng is wrong with print_function");
        exit(1);
    }
    fp.compare = compare_function;
    fp.print = print_function;
    tree.get = get_avltree_node;
    tree.insert = insert_avltree;
    tree.print = print_tree;
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
