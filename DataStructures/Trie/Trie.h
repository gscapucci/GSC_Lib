#ifndef TRIE_H
#define TRIE_H

#define  _GNU_SOURCE
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
typedef struct Trie Trie;

#define ARRAY_LEN(xs) (sizeof(xs)) / sizeof((xs)[0])

struct Trie
{
    Trie *children[UCHAR_MAX];
    bool terminal;
};


#define NODE_POOL_CAP 2048
Trie node_pool[NODE_POOL_CAP] = {0};
size_t node_pool_count = 0;

Trie* Trie_newNode();
void Trie_add(Trie *root, char *string);
void Trie_dump_dot(Trie *root);
void Trie_printDot(Trie *root);

Trie* Trie_newNode()
{
    assert(node_pool_count < NODE_POOL_CAP);
    return &node_pool[node_pool_count++];
}

void Trie_add(Trie *root, char *string)
{
    if(root == NULL || *string == '\0')
    {
        return;
    }

    assert(root != NULL);
    size_t index = (size_t)*string;

    if(root->children[index] == NULL)
    {
        root->children[index] = Trie_newNode();
    }
    Trie_add(root->children[index], string + 1);
}

void Trie_dump_dot(Trie *root)
{
    size_t index = root - node_pool;
    for (size_t i = 0; i < ARRAY_LEN(root->children); i++)
    {
        if(root->children[i] != NULL)
        {
            size_t child_index = root->children[i] - node_pool;
            printf("    Node_%zu [label = \"%c\"]\n", child_index, (char)i);
            printf("    Node_%zu -> Node_%zu\n", index, child_index);
            Trie_dump_dot(root->children[i]);
        }
    }
}

void Trie_printDot(Trie *root)
{
    printf("digraph trie {\n");
    printf("    Node_%zu [label = root]\n", root - node_pool);
    Trie_dump_dot(root);
    printf("}\n");
}

#endif /* TRIE_H */