#include <stdio.h>
#include <stdlib.h>
#include "undofeature.h"

/*creating linked list head is always null initially*/
LinkedList *createLinkedList()
{
        LinkedList *linked_list = (LinkedList *)malloc(sizeof(LinkedList));
        linked_list->head = NULL;

        return linked_list;
}

/*insert first function of linked list where you add a new node,the head will point to new node and also takes in struct*/
void insertFirst(LinkedList *list, Coordinates *coord)
{
        ListNode *newNode;
        newNode = (ListNode *)malloc(sizeof(ListNode));

        newNode->data = coord;
        newNode->next = list->head;
        list->head = newNode;
}

/*remove values from linked list just frees one node that has been removed*/
Coordinates* removeFirst(LinkedList *list)
{

        Coordinates* rndom = NULL;
        ListNode *node;

        node = list->head;
        rndom = node->data;
        list->head = list->head->next;

        free(node);

        return rndom;
}

/*freeing the llist*/
void freeLinkedList(LinkedList* list) {
        ListNode *node, *next;
        node = (*list).head;
        while(node != NULL) {
                next = (*node).next;
                free((*node).data); 
                free(node);
                node = next;
        }
        free(list);
}



