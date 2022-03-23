#include "LinkedList.h"

struct LinkedList_node
{
    Node *node;
    LinkedList_node *next, *prev;
};

void *get_linked_list_node(LinkedList *self, size_t index);
LinkedList_node *create_linked_list_node(void *data, size_t size);
void insert_linked_list_node(LinkedList *self, void *data, size_t size);
void remove_linekd_list_node(LinkedList *self, size_t index);

void *get_linked_list_node(LinkedList *self, size_t index)
{
    if(self)
    {
        if(index >= self->length)
        {
            fprintf(stderr, "index out of range");
            exit(1);
        }
        if(self->head)
        {
            LinkedList_node *aux = self->head;
            if(index > self->length / 2)
            {
                for (size_t i = 0; i < self->length - index; i++)
                {
                    aux = aux->prev;
                }
            }
            else
            {
                for (size_t i = 0; i < index; i++)
                {
                    aux = aux->next;
                }
            }
            return aux->node->data;
        }
    }
    return NULL;
}

LinkedList_node *create_linked_list_node(void *data, size_t size)
{
    LinkedList_node *list_node = (LinkedList_node *)malloc(sizeof(LinkedList_node));
    if(list_node)
    {   
        list_node->node = create_node(data, size);
        list_node->next = NULL;
        list_node->prev = NULL;
        return list_node;
    }
    return NULL;
}

void insert_linked_list_node(LinkedList *self, void *data, size_t size)
{
    if(self)
    {
        if(self->length == 0)
        {
            self->head = create_linked_list_node(data, size);
            self->head->next = self->head;
            self->head->prev = self->head;
            self->length = 1;
        }
        else
        {
            LinkedList_node *aux = self->head->prev;
            LinkedList_node *new_node = create_linked_list_node(data, size);
            self->head->prev = new_node;
            new_node->next = self->head;
            aux->next = new_node;
            new_node->prev = aux;
            self->length++;
        }
    }
}

void remove_linekd_list_node(LinkedList *self, size_t index)
{
    if(self)
    {
        if(self->length == 0)
        {
            fprintf(stderr, "list is empty");
            return;
        }
        if(self->length == 1)
        {
            free(self->head);
            self->length = 0;
            self->head = NULL;
        }
        else
        {
            LinkedList_node *aux = self->head;
            for (size_t i = 0; i < index; i++)
            {
                aux = aux->next;
            }
            aux->prev->next = aux->next;
            aux->next->prev = aux->prev;
            free(aux);
            self->length--;
        }
    }
}

LinkedList create_linked_list()
{
    LinkedList ll;
    ll.head = NULL;
    ll.length = 0;
    ll.insert = insert_linked_list_node;
    ll.get = get_linked_list_node;
    ll.remove = remove_linekd_list_node;
    return ll;
}

void clear_linked_list(LinkedList *list)
{
    if(list)
    {
        if(list->head)
        {
            LinkedList_node *curr = list->head, *next = list->head->next;
            for(size_t i = 0; i < list->length; i++)
            {
                clear_node(curr->node);
                free(curr);
                curr = next;
                next = next->next;
            }
        }
        list->head = NULL;
        list->length = 0;
    }
}