#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>


void LL_init(LinkedList *list)
{
    list->size = sizeof(size_t) + sizeof(int) + sizeof(LLNode*);
    list->head = NULL;
    list->lenght = 0;
}

LLNode* LL_newNode(int val)
{
    LLNode* node = (LLNode*)malloc(sizeof(LLNode));
    node->val = val;
    node->next = NULL;
}

void LL_add(LinkedList *list, int val)
{
    if(list->head == NULL)
    {
        list->head = LL_newNode(val);
        list->size += sizeof(LLNode);
        list->lenght++;
        return;
    }
    LLNode* aux = list->head;
    while (aux->next != NULL)
    {
        aux = aux->next;
    }
    aux->next = LL_newNode(val);
    list->size += sizeof(LLNode);
    list->lenght++;
}

void LL_clear(LinkedList *list)
{
    if(list->head == NULL)
    {
        return;
    }
    LLNode *aux;
    while(list->head != NULL)
    {
        aux = list->head;
        list->head = list->head->next;
        free(aux);
    }
    list->lenght = 0;
    list->size = sizeof(size_t) + sizeof(int) + sizeof(LLNode*);
}

void LL_print(LinkedList *list)
{
    if(list->head == NULL)
    {
        printf("List in empty.\n");
    }
    else
    {
        LLNode* aux = list->head;
        while (aux != NULL)
        {
            printf("%d->", aux->val);
            aux = aux->next;
        }
        printf("NULL\n");
    }
}

void LL_removeFirst(LinkedList *list)
{
    if(list->head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    else if(list->lenght == 1)
    {
        free(list->head);
        list->head = NULL;
    }
    LLNode* aux = list->head;
    list->head = list->head->next;
    free(aux);
    list->lenght--;
    list->size -= sizeof(LLNode);
}

void LL_removeLast(LinkedList *list)
{
    if(list->head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    else if(list->lenght == 1)
    {
        free(list->head);
        list->head = NULL;
        list->lenght = 0;
        return;
    }
    LLNode* aux = list->head;
    while (aux->next->next != NULL)
    {
        aux = aux->next;
    }
    LLNode *aux2 = aux->next;
    aux->next = NULL;
    free(aux2);
    list->lenght--;
    list->size -= sizeof(LLNode);
}

void LL_remove(LinkedList *list, int val)
{
    if(list->head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    
    LLNode *aux = list->head;
    while (aux->next->val != val)
    {
        aux = aux->next;
        if(aux->next == NULL)
        {
            printf("%d was not found.\n", val);
            return;
        }
    }
    LLNode *tmp = aux->next->next;
    free(aux->next);
    aux->next = tmp;
    list->lenght--;
    list->size -= sizeof(LLNode);
}

int LL_getAtPosition(LinkedList *list, int pos)
{
    if(list->head == NULL)
    {
        printf("List is empty.\n");
        return 0;
    }
    LLNode *aux = list->head;
    int position = 0;
    while (aux != NULL)
    {
        if(pos == position)
        {
            return aux->val;
        }
        aux = aux->next;
        position++;
    }
    printf("Position index out of range.\n");
    return 0;
}

size_t LL_getLenght(LinkedList *list)
{
    return list->lenght;
}

size_t LL_getSize(LinkedList *list)
{
    return list->size;
}

void LL_removeAtPosition(LinkedList *list, int pos)
{
    if(list->head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    if (pos == 0)
    {
        LL_removeFirst(list);
        return;
    }
    if(pos == list->lenght - 1)
    {
        LL_removeLast(list);
        return;
    }
    LLNode *aux = list->head;
    int position = 1;
    while (position < pos)
    {
        aux = aux->next;
        position++;
    }
    LLNode* tmp = aux->next->next;
    free(aux->next);
    aux->next = tmp;
    list->lenght--;
    list->size -= sizeof(LLNode);
}

void LL_reverse(LinkedList *list)
{
    LLNode *cur_node, *next_node, *prev_node;
    cur_node = list->head;
    next_node = cur_node->next;
    cur_node->next = NULL;
    while (next_node != NULL)
    {
        prev_node = cur_node;
        cur_node = next_node;
        next_node = next_node->next;
        cur_node->next = prev_node;
    }
    list->head = cur_node;
}

LinkedList LL_subList(LinkedList *list, size_t begin_pos, size_t end_pos)
{
    LinkedList newLL;
    LL_init(&newLL);
    if(begin_pos > list->size || end_pos > list->size || begin_pos > end_pos)
    {
        return newLL;
    }
    LLNode *aux = list->head;
    for (size_t i = 0; i < begin_pos; i++)
    {
        aux = aux->next;
    }
    for (size_t i = begin_pos; i < end_pos; i++)
    {
        LL_add(&newLL, aux->val);
        aux = aux->next;
    }
    return newLL;
}

LinkedList LL_getCopy(LinkedList *ll)
{
    LinkedList newLL;
    LL_init(&newLL);
    LLNode *aux = ll->head;
    for (size_t i = 0; i < ll->lenght; i++)
    {
        LL_add(&newLL, aux->val);
        aux = aux->next;
    }
    return newLL;
}