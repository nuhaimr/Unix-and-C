/*Nuha Imran*/
/*16/04/2022*/

#include <stdio.h>
#include <stdlib.h>
#include "messycalc.h"
#include "terminal.h"
#include "time.h"

/*a function that runs everything altogether takes in the command line arguments of filename and the current that the user enters*/
int useCalculator(char *filename,float current_total){
       /*initialised and declared values of everything*/
	char **calcNumbers;
	int i;
	int *num_stored;
	int *randomptr;
	char userinput = ' ';
	float initial_total;
	/*creating a linked list using the linked list function further detail in that function*/
	LinkedList* the_list = createLinkedList();

	printf("\n");
	/*making some pointers on heap memory*/
	randomptr = (int *)malloc(sizeof(int));
	num_stored = (int *)malloc(sizeof(int));
	*num_stored = 0;
	/*needed for file writing*/
	initial_total = current_total;

        /*this is a 2D array on heap memory made to store the keypad of the calculator*/
	calcNumbers = (char **)malloc(8 * sizeof(char *));
	for (i = 0; i < 8; i++)
	{
		calcNumbers[i] = (char *)malloc(3 * sizeof(char));
	}
	/*this function has taken in the 2D array and has positions of all numbers on keypad in 2D array*/
	insertNumbers(calcNumbers);
	/*this functiion basically prints the whole keypad top screen and current total entered by user altogether*/
	printCalcNumbers(calcNumbers,num_stored,current_total);

        /*this functiion is for choosing  value from the keypad stores the movement of the keypad and filewriting aswell*/
	selectOption(calcNumbers,userinput,randomptr,num_stored,current_total,the_list,initial_total,filename);
	/*so number on top screen can go back to zero*/
	

        /*freeing all pointers on heap memory include the array*/
	for (i = 0; i < 8; i++)
	{
		free(calcNumbers[i]);
	}
	free(calcNumbers);
	calcNumbers = NULL;

	free(randomptr);
	randomptr = NULL;

	free(num_stored);
	num_stored = NULL;

	freeLinkedList(the_list);

	return 0;
}

/*function hardcodes on indexes all numbers on keypad*/
void insertNumbers(char **calcNumbers){
	int i,j;
	for(i = 0;i < 8;i++){
		for(j =0;j<3;j++){
			if(i == 0||i==2 ||i==4 ||i==6){
				calcNumbers[0][0] = '5';
				calcNumbers[2][0] = '=';
				calcNumbers[4][0] = '2';
				calcNumbers[6][0] = '3';
				calcNumbers[0][1] = '0';
				calcNumbers[2][1] = '8';
				calcNumbers[4][1] = '1';
				calcNumbers[6][1] = '4';
				calcNumbers[0][2] = '6';
				calcNumbers[2][2] = '7';
				calcNumbers[4][2] = '9';
				calcNumbers[6][2] = '/';

			}
			/*position where player is stored*/
			else if(i==1 && j==0){
				calcNumbers[i][j] = '^';
			}
			/*rest are empty spaces*/
			else{
				calcNumbers[i][j] = ' ';
			}
		}

	}
}

/*prints all the screens of the calculator*/
void printCalcNumbers(char **calcNumbers,int *num_stored,float current_total){
	int i, j;
	printf("---------\n");
	/*for storing 7 digits*/
	printf("|%7d|\n",*num_stored);
	printf("---------\n");

	printf("\n");
	/*printf("\n");*/
	/*iterating thru the 2D array and printing the array with numbers*/
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%c ", calcNumbers[i][j]);
		}
		printf("\n");
	}
	/*printf("\n");*/
        /*priting current total with 2 decimal places*/
	printf("current total : %.2f\n",current_total);

}

/*function to shuffle array indexes*/
void randomizeNumbers(char **calcNumbers){
	int i,j;
	/*using time to do so*/
	srand( time(NULL) );
       /*iterating thru the array*/
	for(i = 0;i < 8;i++){
		for(j = 0;j < 3;j++){
		       /*making 2 swap indexes modules 8 cause 8 rows and 3 cause three columns they are i j of swapping*/
			int swap = rand() % 8;
			int swap1 = rand() % 3;
			/*since only numbers can be randomized*/
			if(calcNumbers[i][j] != ' ' && calcNumbers[swap][swap1] != ' ' && calcNumbers[i][j] != '^' && calcNumbers[swap][swap1] != '^')
			{
			/*for swapping temporarily storing changing*/
				int temp = calcNumbers[i][j];
				calcNumbers[i][j] = calcNumbers[swap][swap1];
				calcNumbers[swap][swap1] = temp;
			}



		}
	}
}

/*function for selecting an option from the keypad*/
void selectOption(char **calcNumbers, char userinput,int *randomptr,int *num_stored,float current_total,LinkedList* list,float initial_total, char *filename){
	int i,j;
	/*keep the loop going till = not pressed*/
	while(*randomptr != 1){

               int n;
               /*to hide user input*/
		disableBuffer();
		scanf(" %c", &userinput);
		enableBuffer();
               /*iterate thru thr array and find the player move accordingly*/
		for(i = 0;i < 8;i++){
			for(j = 0; j < 3; j++){
			
				if(calcNumbers[i][j] == '^'){
					if(userinput == 'w'){
						if(i-1 == 0){/*if equated to this row and empty space then move down by 6 since its end*/
							calcNumbers[i][j] = ' ';
							i = i + 6;
							calcNumbers[i][j] = '^';
						}
						/*if this posotion is empty space then move up two only on empty space*/
						else if(calcNumbers[i-2][j] == ' '){
							calcNumbers[i][j] = ' ';
							i = i - 2;
							calcNumbers[i][j] = '^';
						}
					}
					/*similar for all movement keep doing things accordingly*/
					else if(userinput == 's'){
						if(i+1 == 8){
							calcNumbers[i][j] = ' ';
							i = i - 6;
							calcNumbers[i][j] = '^';
						}
						else if(calcNumbers[i+2][j] == ' '){
							calcNumbers[i][j] = ' ';
							i = i + 2;
							calcNumbers[i][j] = '^';
						}
					}
					else if(userinput == 'a'){
						if(j-1 == -1){
							calcNumbers[i][j] = ' ';
							j = j + 2;
							calcNumbers[i][j] = '^';
						}
						else if(calcNumbers[i][j - 1] == ' '){
							calcNumbers[i][j] = ' ';
							j = j - 1;
							calcNumbers[i][j] = '^';
						}
					}
					else if(userinput == 'd'){
						if(j+1 == 3){
							calcNumbers[i][j] = ' ';
							j = j - 2;
							calcNumbers[i][j] = '^';
						}
						else if(calcNumbers[i][j + 1] == ' '){
							calcNumbers[i][j] = ' ';
							j = j + 1;
							calcNumbers[i][j] = '^';
						}
					}
					else if(userinput == 'e'){
					/*if its not a / and = because those one divides one ends the program*/
						if(calcNumbers[i - 1][j] != '/' && calcNumbers[i -1][j] != '='){
						/*finding what number using ASCII after multiplication addition done randomise the movement since an option was chosen*/
							int temp_var = calcNumbers[i-1][j] - '0';
							*num_stored = (*num_stored * 10) + temp_var;
							randomizeNumbers(calcNumbers);
						}
						/*if it is a / then divide current total by the number that was stored to give a result only do so if number is not zero as zero gives error*/
						else if(calcNumbers[i-1][j] == '/'){
						int *stored_data;
						stored_data = (int *)malloc(sizeof(int));
						/*a pointer that will contain stored data which will be inserted to a list*/
						*stored_data = *num_stored;
						/*insert all the stored data into a list*/
						insertFirst(list, stored_data);
							if(*num_stored != 0){
								current_total = current_total/(*num_stored);
								*num_stored = 0;
							}
							/*after option used randomise again*/
							randomizeNumbers(calcNumbers);
						}
						else{
						/*file writing open file write to file while less than n print that many (*/
						        FILE *fp;
						        fp = fopen(filename, "w");
						        
						        for(n = 0;n < list->size;n++){
						        fprintf(fp,"(");
						        }
						        /*print value that was given initially*/
						        fprintf(fp,"%f",initial_total);
						        while(list->size != 0){
						        int *emptyptr = (int*)removeLast(list);
						        /*because pointer cannot be printed like that*/
						        int randomly = *emptyptr;
						        fprintf(fp,"/");
						        fprintf(fp,"%d",randomly);
						        fprintf(fp, ")");
								free(emptyptr);
						        }
						        fprintf(fp,"=%.2f", current_total);
						        /*after doing everything close the file we were writing to*/
						        fclose(fp);
						        /*since = was pressed end the loop*/
							*randomptr = 1;
						}


					}
					/*just commands on not to press any other alphabet*/
					else
					{
						printf("\nYou can only use w-up s-down a-left d-right e-enter\n");
					}

				}
			}
		}
		system("clear");   
		/*clear screen and reprint maps with modified movement each time*/
		printCalcNumbers(calcNumbers,num_stored,current_total);
	}
}

/*creating linked list head and tail is always null initially*/
LinkedList* createLinkedList()
{
	LinkedList* list = (LinkedList*)malloc( sizeof(LinkedList) );

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return list;
}

/*insert first of a linked list taking in list and value to store*/
void insertFirst( LinkedList* list, void* inData )
{
       /*initlaising and declaring values*/
	ListNode* newNode = (ListNode*)malloc( sizeof(ListNode) );
	ListNode* temp_head;
	newNode->data = inData;
	newNode->next = NULL;
	newNode->prev = NULL;
        
        /*empty list indicating the new node is the head and the tail*/
	if( list->head == NULL )
	{
		list->head = newNode;
		list->tail = newNode;
	}
	/*if it has one value tell the new head normal linked list insertFirst logic used*/
	else
	{
		newNode->next = list->head;
		temp_head = newNode->next;
		temp_head->prev = newNode;
		list->head = newNode;
	}
       /*increment side on each node*/
	list->size++;
}

void* removeLast( LinkedList* list )
{
	void* nodeData;
	ListNode* temp_tail;

	nodeData = (list->tail)->data;
	temp_tail = list->tail;

        /* if list empty nothing to remove*/
	if( list->size == 0 )
	{
		nodeData = NULL;
	}
	/*the list is of size 1*/
	else if( list->size == 1 )
	{
		list->head = NULL;
		list->tail = NULL;
	}
	/*list stores multiple nodes*/
	else
	{
		list->tail = (list->tail)->prev;
		list->tail->next = NULL;	
	}

	free(temp_tail);
	list->size--;

	return nodeData;
}

/*freeing the linked list since made on malloc*/
void freeLinkedList(LinkedList* list)
{
    ListNode *node, *nextNode;
    node = list->head;
    while (node != NULL)
    {
        nextNode = node->next;
        free(node);
        node = nextNode;
    }
    free(list);
}




