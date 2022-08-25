/*Name:Nuha Imran*/
/*Date:12/02/22*/
/*ID:20696366*/

#include <stdio.h>
#include "game.h"
#include "map.h"
#include "terminal.h"
#include <stdlib.h>

/*a function that includes all other functions and freeing the array indivisual functions are doing indivual taks that later are all called here*/
void GameRun(int check)
{
        int metadataAmount, mapRow, mapColumn;
        /*this int array is for metadata function whereas mapBoard is for the board objects*/
        char **mapBoard;
        int **marray;
        int k, i;
        char userinput = ' ';
        int exit = 0;
        int *randomptr;
        /*this pointer is made for exiting*/
        randomptr = (int *)malloc(sizeof(int));


        /*function gets metaData from the function in the other file thru forward declaration*/
        getMetadata(&marray, &metadataAmount, &mapRow, &mapColumn);

        /*an 2D pointer array that is on heap memory*/
        mapBoard = (char **)malloc(mapRow * sizeof(char *));
        for (k = 0; k < mapRow; k++)
        {
                mapBoard[k] = (char *)malloc(mapColumn * sizeof(char));
        }
        /* this function prints the borders of the map*/
        boardBorder(mapBoard, mapRow, mapColumn);
        /*this function prints objects on the board*/
        boardObjects(marray, mapBoard, mapRow, mapColumn, metadataAmount);

        /*if command line argument 0 then display the board while exit isnt true make objectmove,display board indicating movement if randomptr true just exit loop*/
        /*this is for dark in cond comp*/
        #ifdef DARK
        if(check == 0){
                displayBoard(mapBoard, mapRow, mapColumn);
                while (exit != 1)
                {
                        objectMovement(mapBoard, userinput, exit, mapRow, mapColumn, randomptr);
                        displayBoard(mapBoard, mapRow, mapColumn);
                        if (*randomptr == 1)
                        {
                                exit = 1;
                        }
                }
        }
        /*check users command line argument and keep the vision accondingly in method repeat for all possible*/
        else if(check > 0)
        {
                dark(marray, exit, mapRow, mapColumn, mapBoard, check, userinput, metadataAmount, randomptr);

        }
        else
        {
                printf("Invalid visibility distance");
        }
        /*for dark in cond comp*/
        #else
        displayBoard(mapBoard, mapRow, mapColumn);
                while (exit != 1)
                {
                        objectMovement(mapBoard, userinput, exit, mapRow, mapColumn, randomptr);
                        displayBoard(mapBoard, mapRow, mapColumn);
                        if (*randomptr == 1)
                        {
                                exit = 1;
                        }
                }
        #endif
        
        /*freeing all things on heap memory so they are unable to cause memory leaks*/
        for (k = 0; k < mapRow; k++)
        {
                free(mapBoard[k]);
        }
        free(mapBoard);
        mapBoard = NULL;

        for(i = 0; i < metadataAmount; i++)
        {
                free(marray[i]);
        }
        free(marray);
        marray = NULL;

        free(randomptr);
        randomptr = NULL;
}

/*this method basically iterate thru the 2D pointer array on heap memory and prints the borders where the are supposed to be*/
void boardBorder(char **mapBoard,int mapRow, int mapColumn)
{
        /*iterating thru*/
        int k, l;
        for (k = 0;k < mapRow; k++)
        {
                for (l = 0; l < mapColumn; l++)
                {
                /*if twos and columns are equal to so and so then print so and so borders*/
                        if ((k == 0 && l == 0) || (k == 0 && l == mapColumn - 1) || (k == mapRow - 1 && l == 0) || (k == mapRow - 1 && l == mapColumn - 1))
                        {
                                mapBoard[k][l] = '#';
                        }
                        
                        else if (k == 0 || k == mapRow - 1)
                        {
                                mapBoard[k][l] = '-';
                        }
                        
                        else if (l == 0 || l == mapColumn - 1)
                        {
                                mapBoard[k][l] = '|';
                        }
                        
                        else
                        {
                                mapBoard[k][l] = ' ';
                        }
                }
        }

}

/*this function prints the board objects the board objects are coming from the metaData function that function table stores the rows and columns of objects if you change them there they will change here too*/
void boardObjects(int **marray, char **mapBoard, int mapRow, int mapColumn, int metadataAmount){
        int i, j, k, l;
        /*iterating thru the marray the array in metadata function*/
        for (i = 0; i < metadataAmount; i++)
        {
                for (j = 0; j < 3; j++)
                {
                        if (j == 2)
                        {
                                /*if it is the player the player will always be in the table as zero  it will be in 6th row 3rd column so in array i j for row would be 0,0 and for column they would be 0,1 thats from the metadata table and we jst repeat for each object,checking from the metaData table*/
                                if (marray[i][j] == 0)
                                {
                                        k = marray[i][j-2];
                                        l = marray[i][j-1];
                                        mapBoard[k][l] = '^';
                                }
                                else if (marray[i][j] == 1)
                                {
                                        k = marray[i][j-2];
                                        l = marray[i][j - 1];
                                        mapBoard[k][l] = 'x';
                                }
                                else if (marray[i][j] == 2)
                                {
                                        k = marray[i][j - 2];
                                        l = marray[i][j-1];
                                        mapBoard[k][l] = 'o';
                                }
                        }
                }
        }
}

/*this function simply takes in the mapboard iterates thru it and prints it*/
void displayBoard(char** mapBoard, int mapRow, int mapColumn)
{
        int k, l;
        for (k = 0; k < mapRow; k++)
        {
                for (l = 0; l < mapColumn; l++)
                {
                        printf("%c ", mapBoard[k][l]);
                }
                printf("\n");
        }


}

/*this function basically makes your player move iterate thru the board array looks for the player because only the player can move then for every user input it checks where its a border,wall,empty space and decides according on how the player would react to it*/
void objectMovement(char **mapBoard, char userinput, int exit, int mapRow, int mapColumn, int * randomptr)
{
        int k, l;
        for (k = 0; k < mapRow; k++)
        {
                for (l = 0; l < mapColumn; l++)
                {
                        if (mapBoard[k][l] == '^' || mapBoard[k][l] == 'v' || mapBoard[k][l] == '<' || mapBoard[k][l] == '>')

                        {
                                /*just disabled buffer so user input doesnt print and cleared screen*/
                                disableBuffer();
                                scanf(" %c", &userinput);
                                enableBuffer();
                                system("clear");
                                if(userinput == 'w'){
                                        /*if a wall dont let the player move*/
                                        if (mapBoard[k - 1][l] == 'o')
                                        {
                                                mapBoard[k][l] = '^';
                                        }
                                        /*if its the goal let the player touch it/take it then exit*/
                                        else if (mapBoard[k - 1][l] == 'x')
                                        {
                                                mapBoard[k][l] = ' ';
                                                k = k - 1;
                                                mapBoard[k][l] = '^';
                                                exit = 1;
                                        }
                                        /*if its a border again dont let the player move*/
                                        else if (mapBoard[k - 1][l] == '-' || mapBoard[k - 1][l] == '|' || mapBoard[k - 1][l] == '#')
                                        {
                                                mapBoard[k][l] = '^';
                                        }
                                        /*if its an empty space let the player move pointing in the same postion,its the same for all keyboard commands*/
                                        else
                                        {
                                                mapBoard[k][l] = ' ';
                                                k = k - 1;
                                                mapBoard[k][l] = '^';
                                        }
                                }

                                else if(userinput == 's'){
                                        if (mapBoard[k + 1][l] == 'o')
                                        {
                                                mapBoard[k][l] = 'v';
                                        }
                                        else if (mapBoard[k + 1][l] == 'x')
                                        {
                                                mapBoard[k][l] = ' ';
                                                k = k + 1;
                                                mapBoard[k][l] = 'v';
                                                exit = 1;
                                        }
                                        else if (mapBoard[k + 1][l] == '-' || mapBoard[k + 1][l] == '|' || mapBoard[k + 1][l] == '#')
                                        {
                                                mapBoard[k][l] = 'v';
                                        }
                                        else
                                        {
                                                mapBoard[k][l] = ' ';
                                                k = k + 1;
                                                mapBoard[k][l] = 'v';
                                        }
                                }

                                else if(userinput == 'a'){
                                        if (mapBoard[k][l - 1] == 'o')
                                        {
                                                mapBoard[k][l] = '<';
                                        }
                                        else if (mapBoard[k][l - 1] == 'x')
                                        {
                                                mapBoard[k][l] = ' ';
                                                l = l - 1;
                                                mapBoard[k][l] = '<';
                                                exit = 1;
                                        }
                                        else if (mapBoard[k][l - 1] == '-' || mapBoard[k][l - 1] == '|' || mapBoard[k][l - 1] == '#')
                                        {
                                                mapBoard[k][l] = '<';
                                        }
                                        else
                                        {
                                                mapBoard[k][l] = ' ';
                                                l = l - 1;
                                                mapBoard[k][l] = '<';
                                        }
                                }

                                else if(userinput == 'd'){
                                        if (mapBoard[k][l + 1] == 'o')
                                        {
                                                mapBoard[k][l] = '>';
                                        }
                                        else if (mapBoard[k][l + 1] == 'x')
                                        {
                                                mapBoard[k][l] = ' ';
                                                l = l + 1;
                                                mapBoard[k][l] = '>';
                                                exit = 1;
                                        }
                                        else if (mapBoard[k][l + 1] == '-' || mapBoard[k][l + 1] == '|' || mapBoard[k][l + 1] == '#')
                                        {
                                                mapBoard[k][l] = '>';
                                        }
                                        else
                                        {
                                                mapBoard[k][l] = ' ';
                                                l = l + 1;
                                                mapBoard[k][l] = '>';
                                        }
                                }

                                else{
                                        printf("Game can only be played with w-up s-down a-left d-right\n");
                                }
                                /*if exit is equavalent to one let the winning statement come and in that case the pointer is assigned 1 too because I want to use this same method in dark aswell*/
                                if (exit == 1)
                                {
                                        printf("Congratulations!!\n");
                                        *randomptr = 1;
                                }

                        }
                }
        }
}

/*this method basically breaks down the players vision so if command line argument is 1 he can see map as 3*3 if 2 5*5 and if 3 7*7*/
void dark(int **marray,int exit,int mapRow,int mapColumn, char **mapBoard,int vision, char userinput, int metadataAmount, int *randomptr)
{
        int strt, strt1, fin, fin1;
        int m, n;
        int k, l;
        /*calling to print board and objects*/
        boardBorder(mapBoard, mapRow, mapColumn);
        boardObjects(marray, mapBoard, mapRow, mapColumn, metadataAmount);
        /*only while exit is not true because if exit is true you should exit the loop */
        while(exit != TRUE)
        {
                for (k = 0; k < mapRow; k++)
                {
                        for(l = 0; l < mapColumn; l++)
                        {
                                if (mapBoard[k][l] == '^' || mapBoard[k][l] == 'v' || mapBoard[k][l] == '<' || mapBoard[k][l] == '>')
                                {
                                /* this is basically the players vision so if the row is starting then the row - the vision the user enters and then so on for where the row ends and then same process for column so its 3*3 or whatever the case is for both*/
                                        strt = k - vision;
                                        strt1 = k + vision;
                                        fin = l - vision;
                                        fin1 = l + vision;

                                        /*if the starting row is less than zero then its zero*/
                                        if(strt < 0)
                                        {
                                                strt = 0;
                                        }
                                        /*if starting column is less than zero than its zero*/
                                        if(fin < 0)
                                        {
                                                fin = 0;
                                        }
                                        /*if ending column is greator than the mapColumn then map column is equal to that amount same for map row aswell*/
                                        if(fin1 > mapColumn - 1)
                                        {
                                                fin1 = mapColumn - 1;
                                        }
                                        if(strt1 > mapRow - 1)
                                        {
                                                strt1 = mapRow - 1;
                                        }
                                        /*just priting the map we would get in dark through the variables we just set*/
                                        for (m = strt; m <= strt1; m++)
                                        {
                                                for(n = fin; n <= fin1; n++){
                                                        printf(" %c", mapBoard[m][n]);
                                                }
                                                printf("\n");

                                        }



                                        /*call the method so the object can move*/
                                        objectMovement(mapBoard, userinput, exit, mapRow, mapColumn,  randomptr);
                                        
                                        /*if pointer equals 1 exit is true exit*/
                                        if (*randomptr == 1)
                                        {
                                        	exit = TRUE;
                                        }

                                        /*samw thing again for object movement*/
                                        if(strt < 0)
                                        {
                                                strt = 0;
                                        }
                                        if(fin < 0)
                                        {
                                                fin = 0;
                                        }
                                        if(fin1 > mapColumn - 1)
                                        {
                                                fin1 = mapColumn - 1;
                                        } 
                                        if(strt1 > mapRow - 1)
                                        { 
                                                strt1 = mapRow - 1;
                                        }


                                }
                        }
                }
        }
}


















