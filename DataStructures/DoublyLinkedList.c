#include "DoublyLinkedList.h"


DoublyLinkedList create_doubly_linked_list(size_t data_size) {
    DoublyLinkedList list;
    list.data_size = data_size;
    list.head = NULL;
    list.tail = NULL;
    list.length = 0;
    return list;
}

DoublyLinkedList delete_doubly_linked_list(DoublyLinkedList *list) {
    DoublyLinkedListNode *aux = list->head;
    while(aux) {
        DoublyLinkedListNode *curr = aux;
        aux = aux->next;
        deallocate(curr);
    }
    *list = create_doubly_linked_list(0);
}

DoublyLinkedList *create_doubly_linked_list_heap(size_t data_size) {
    DoublyLinkedList *list = allocate(sizeof(DoublyLinkedList));
    list->data_size = data_size;
    list->head = NULL;
    list->tail = NULL;
    list->length = NULL;
    return list;
}

DoublyLinkedList *delete_doubly_linked_list_heap(DoublyLinkedList *list) {
    delete_doubly_linked_list(list);
    deallocate(list);
}