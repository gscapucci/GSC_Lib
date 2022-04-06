#include "AVLTree.h"

#include <string.h>
typedef struct FunctionPointers
{
    int (*compare)(void *data1, void *data2);
}FP;

FP fp;



AVLTree_node *_create_avltree_node(void *data, size_t size);
void _clear_avltree_node(AVLTree_node *root);
int _insert_avltree_node(AVLTree_node *root, void *data, size_t size);
void *_search_node(AVLTree_node *root, void *data);
void _insert_avltree(AVLTree *self, void *data, size_t size);
void *_get_avltree_node(AVLTree *self, void *data);
void _print_tree_node(AVLTree_node *root, int height);
void _print_tree(AVLTree *self);
void *_get_at(AVLTree *self, size_t index);
void *_get_at_node(AVLTree_node *root, size_t *cur, size_t index);

AVLTree_node *_create_avltree_node(void *data, size_t size)
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
    fprintf(stderr, "node not created");
    return NULL;
}

void _clear_avltree_node(AVLTree_node *root)
{
    if(root)
    {
        _clear_avltree_node(root->left);
        _clear_avltree_node(root->right);
        clear_node(root->node_data);
        free(root->node_data);
    }
}

int _insert_avltree_node(AVLTree_node *root, void *data, size_t size)
{
    switch (fp.compare(data, root->node_data->data))
    {
    case 1:
        if(root->right == NULL)
        {
            root->right = _create_avltree_node(data, size);
            root->height_diff++;
            return 1;
        }
        else
        {
            int ret = _insert_avltree_node(root->right, data, size);
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
            root->left = _create_avltree_node(data, size);
            root->height_diff--;
            return -1;
        }
        else
        {
            int ret = _insert_avltree_node(root->left, data, size);
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

void *_search_node(AVLTree_node *root, void *data)
{
    if(root)
    {
        if(root->node_data)
        {
            if(root->node_data->data)
            {
                if(!fp.compare(data, root->node_data->data))
                {
                    return root->node_data->data;
                }
                void *p1 = NULL, *p2 = NULL;
                if(root->left)
                {
                    p1 = _search_node(root->left, data);
                }
                if(root->right)
                {
                    p2 = _search_node(root->right, data);
                }
                if(p1 != NULL)
                {
                    return p1;
                }
                else if(p2 != NULL)
                {
                    return p2;
                }
            }
        }
    }
    return NULL;
}

void *_get_avltree_node(AVLTree *self, void *data)
{
    if(self)
    {
        return _search_node(self->root, data);
    }
    return NULL;
}

void _insert_avltree(AVLTree *self, void *data, size_t size)
{
    if(!self->root)
    {
        self->root = _create_avltree_node(data, size);
        self->number_of_nodes++;
        return;
    }
    if(_insert_avltree_node(self->root, data, size) != 0)
    {
        self->number_of_nodes++;
    }
}

void *_get_at(AVLTree *self, size_t index)
{
    if(self)
    {
        if(index >= self->number_of_nodes)
        {
            fprintf(stderr, "index out of range");
            exit(1);
        }
        size_t cur = 0;
        return _get_at_node(self->root, &cur, index);
    }
    fprintf (stderr, "invalid input");
    exit(1);
}

void *_get_at_node(AVLTree_node *root, size_t *cur, size_t index)
{
    if(root)
    {
        if(root->left)
        {
            void *ret = _get_at_node(root->left, cur, index);
            (*cur)++;
            if(ret)
            {
                return ret;
            }
        }
        if((*cur) == index)
        {
            return root->node_data->data; 
        }
        if(root->right)
        {
            (*cur)++;
            void *ret = _get_at_node(root->right, cur, index);
            if(ret)
            {
                return ret;
            }
        }
    }
    return NULL;
}

AVLTree create_avltree(int (*compare_function)(void *data1, void *data2))
{
    AVLTree tree;
    if(!compare_function)
    {
        fprintf(stderr, "Error: somethng is wrong with compare_function");
        exit(1);
    }
    fp.compare = compare_function;
    tree.get = _get_avltree_node;
    tree.insert = _insert_avltree;
    tree.number_of_nodes = 0;
    tree.get_at = _get_at;
    tree.root = NULL;
    return tree;
}

void clear_avltree(AVLTree *tree)
{
    if(tree)
    {
        if(tree->root)
        {
            _clear_avltree_node(tree->root);
            free(tree->root);
            tree->root = NULL;
        }
    }
}
