#include "LinkedList.h"

LinkedList *create_linked_list()
{
    LinkedList *ll = (LinkedList *)malloc(sizeof(LinkedList));
    if(ll)
    {
        ll->head = NULL;
        ll->length = 0;
        return ll;
    }
    return NULL;
}