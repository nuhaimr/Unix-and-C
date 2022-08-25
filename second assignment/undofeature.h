/*Nuha Imran*/
/*20696366*/

#ifndef UNDOFEATURE_H
#define UNDOFEATURE_H
/*struct for linkedlist containing data and pointer to next*/
typedef struct ListNode
{
    void *data;
    struct ListNode *next;

} ListNode;

/*listNodes head for linked list*/
typedef struct
{
    ListNode *head;

} LinkedList;

/*struct storing player and snake coordinates*/
typedef struct Coordinates
{
    int pRow;
    int pCol;
    int sRow;
    int sCol;
    /*mark = ~,^,<,>,v*/
    char mark;

} Coordinates;

LinkedList *createLinkedList();
void insertFirst(LinkedList *list, Coordinates *coord);
Coordinates* removeFirst(LinkedList *list);
void freeLinkedList(LinkedList* list);



#endif
