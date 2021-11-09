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

    addRand(&list, 20);

    LL_print(&list);

    LL_removeAtPosition(&list, 0);
    LL_print(&list);

    LL_removeAtPosition(&list, list.lenght - 1);
    LL_print(&list);

    LL_removeAtPosition(&list, list.lenght/2);
    LL_print(&list);

    LL_removeFirst(&list);
    LL_print(&list);

    LL_removeLast(&list);
    LL_print(&list);

    LL_reverse(&list);
    LL_print(&list);

    LinkedList tsil = LL_subList(&list, 0, list.lenght/2);
    LinkedList tsil2 = LL_subList(&list, list.lenght/2, list.lenght);

    LL_print(&tsil);
    LL_print(&tsil2);


    LL_clear(&list);
    LL_clear(&tsil2);
    LL_clear(&tsil);
    return 0;
}