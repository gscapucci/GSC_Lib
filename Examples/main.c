#include "../LinkedList.h"

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

    addRand(&list, 50);

    LL_print(&list);

    LL_removeAtPosition(&list, 0);
    LL_print(&list);

    LL_removeAtPosition(&list, list.lenght);
    LL_print(&list);

    LL_removeAtPosition(&list, list.lenght/2);
    LL_print(&list);

    LL_removeFirst(&list);
    LL_print(&list);

    LL_removeLast(&list);
    LL_print(&list);

    LL_clear(&list);
}