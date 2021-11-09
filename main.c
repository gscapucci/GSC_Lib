#include "LinkedList.h"

void addRand(LinkedList *list, int n)
{
    for (int i = 0; i < n; i++)
    {
        LL_add(list, rand()%100);
    }
}

int main()
{
    LinkedList list;
    LL_init(&list);
    addRand(&list, 50);
    LinkedList list2 = LL_getCopy(&list);
    LL_print(&list);
    LL_print(&list2);
    LL_clear(&list);
    LL_clear(&list2);
}