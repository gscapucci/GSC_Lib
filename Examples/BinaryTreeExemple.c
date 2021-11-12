#include "../BinaryTree/BinaryTree.h"
#include <time.h>
void add(BinaryTree *bt, int n)
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
    BinaryTree bt;
    BT_init(&bt);

    BT_add(&bt,4);
    BT_add(&bt,2);
    BT_add(&bt,6);
    BT_add(&bt,1);
    BT_add(&bt,3);
    BT_add(&bt,5);
    BT_add(&bt,7);
    
    printf("Tree:\n");
    BT_printTree(&bt);
    printf("\n\n");
    printf("Inorder: ");
    BT_printInorder(&bt);
    printf("\n\n");
    printf("Postorder: ");
    BT_printPostorder(&bt);
    printf("\n\n");
    printf("Preorder: ");
    BT_printPreorder(&bt);


    BT_clear(&bt);
    return 0;
}