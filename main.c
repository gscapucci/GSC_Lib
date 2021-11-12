#include "DataStructures.h"

void add(LinkedList *ll, BinaryTree *bt, int n)
{
    srand(time(NULL));
    for (size_t i = 0; i < n; i++)
    {
        int val = rand()%100;
        LL_add(ll, val);
        BT_add(bt, val);
    }
}

int main()
{
    BinaryTree bt;
    LinkedList ll;
    
    BT_init(&bt);
    LL_init(&ll);

    add(&ll, &bt, 50);
    BT_printTree(&bt);
    printf("\n\n\n\n");

    LL_print(&ll);
    printf("\n\n\n\n");


    BT_clear(&bt);
    LL_clear(&ll);
}