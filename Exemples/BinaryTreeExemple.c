#include "../DataStructures/BinaryTree/InOneHeaderFile/BinaryTree.h"
#include <time.h>
void add(BinaryTree **bt, int n)
{
    srand(time(NULL));
    for (size_t i = 0; i < n; i++)
    {
        int num = rand()%100;
        if(!BT_add(bt, num))
        {
            i--;
        }
    }
}

int main()
{
    BinaryTree *bt;
    BT_init(&bt);
    add(&bt, 50);
    BT_printTree(bt);
    BT_clear(&bt);
    return 0;
}