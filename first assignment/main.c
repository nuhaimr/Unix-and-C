/*Name:Nuha Imran*/
/*Date:20/02/22*/

#include <stdio.h>
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "terminal.h"

/*command line argument program name and argument entered with it*/
int main(int argc, char* argv[])
{
    /*to check if user even entered the argument with it,if not dont do anything tell the user to enter it*/
    if (argc != 2)
    {
    	printf("Usage: %s <number>\n", argv[0]);
    	return 0;
    }
    /*int check is in the method that runs the game atoi because i want to convert the string to integer values my arguments can only be 0-3 so I mentioned that if not them tell the user no! else just run the game with the argument*/
    else
    {
        int check;
        check = atoi(argv[1]);
    	if(check < 0)
    	{
    	    printf("Invalid number\n");
    	    printf("Please enter the number greater than or equal to 0\n");
    	}
    	/*if its greator than and equal to zero run from game check*/
    	else if(check >= 0)
    	{
    	    
    	    GameRun(check);
    	}
    	else
    	{
    	printf("Please enter only numbers\n");
    	}
    	
    }
    return 0;
}


