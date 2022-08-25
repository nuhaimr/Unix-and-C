/*Nuha Imran*/
/*16/04/2022*/

#ifndef MESSYCALC
#define MESSYCALC
 
 typedef struct ListNode
    {
        void* data;
        struct ListNode* next;
        struct ListNode* prev;
    } ListNode;
    
      typedef struct
    {
        ListNode* head;
        ListNode* tail;
        int size;
    } LinkedList;


int useCalculator(char *filename,float current_total);
void insertNumbers(char **calcNumbers);
void printCalcNumbers(char **calcNumbers,int *num_stored,float current_total);
void randomizeNumbers(char **calcNumbers);
void selectOption(char **calcNumbers, char userinput,int *randomptr,int *num_stored,float current_total,LinkedList* list,float initial_total, char *filename);
LinkedList *createLinkedList();
void insertFirst( LinkedList* list, void* inData );
void* removeLast( LinkedList* list );
void freeLinkedList( LinkedList* list);
#endif
