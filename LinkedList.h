#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

typedef struct LLNode{
    int val;
    struct LLNode *next;
}LLNode;

typedef struct LinkedList{
    size_t lenght;
    size_t size;//size in bytes
    struct LLNode *head;
}LinkedList;

void        LL_init(LinkedList *list);
LLNode*     LL_newNode(int val);
void        LL_add(LinkedList *list, int val);
void        LL_clear(LinkedList *list);
void        LL_print(LinkedList *list);
void        LL_deleteFirst(LinkedList *list);
void        LL_deleteLast(LinkedList *list);
void        LL_delete(LinkedList *list, int val);
int         LL_getAtPosition(LinkedList *list, int pos);//return 0 if fail
size_t      LL_getLenght(LinkedList *list);
size_t      LL_getSize(LinkedList *list);
void        LL_deleteAtPosition(LinkedList *list, int pos);
void        LL_reverse(LinkedList *list);
LinkedList  LL_subList(LinkedList *list, size_t begin_pos, size_t end_pos);//begin is inclusive, end is exclusive
LinkedList  LL_getCopy(LinkedList *list);

#endif /* LINKED_LIST_H */