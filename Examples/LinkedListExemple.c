#include "../LinkedLIst/LinkedList.h"

void addRand(LinkedList *list, int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        LL_add(list, rand()%100);
    }
}

int main()
{
    LinkedList list;
    LL_init(&list);

    printf("\nAdd 20 random number.\n");
    addRand(&list, 20);

    LL_print(&list);

    printf("\nRemove at position 0.\n");
    LL_removeAtPosition(&list, 0);
    LL_print(&list);

    printf("\nRemove at position list length - 1(last).\n");
    LL_removeAtPosition(&list, list.length - 1);
    LL_print(&list);

    printf("\nRemove at position list length / 2.\n");
    LL_removeAtPosition(&list, list.length/2);
    LL_print(&list);

    printf("\nRemove first.\n");
    LL_removeFirst(&list);
    LL_print(&list);

    printf("\nRemove last.\n");
    LL_removeLast(&list);
    LL_print(&list);

    printf("\nReverse.\n");
    LL_reverse(&list);
    LL_print(&list);

    LinkedList sub1 = LL_subList(&list, 0, list.length/2);
    LinkedList sub2 = LL_subList(&list, list.length/2, list.length);

    printf("\nSublist 1: ");
    LL_print(&sub1);
    printf("\nSublist 2: ");
    LL_print(&sub2);

    printf("\nSize in bytes: %d\nSum: %d", list.size, sizeof(LLNode)*list.length + sizeof(LinkedList));

    LL_clear(&list);
    LL_clear(&sub1);
    LL_clear(&sub2);
    return 0;
}