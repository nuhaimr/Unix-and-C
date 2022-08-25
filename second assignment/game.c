/*Name = Nuha Imran
  Date = 24/03/22*/

#include <stdio.h>
#include <stdlib.h>
#include "undofeature.h"
#include "game.h"
#include "terminal.h"



/*requires user input that would come from main which is a charpointer a filename*/
int GameRun(char* filename)
{
        /*pointer pointing to file,initiliased other values exit for exiting,randomptr for exitingaswell,snakeexit for exiting snakemovement*/
        FILE* file;
        int i,j,k;
        int** marray;
        char **mapBoard;
        int exit = 0;
        int *randomptr;
        char userinput = ' ';
        int column, row , metadata, amount, mapRow, mapColumn;
        int snakeexit = 0;

        /*mallocing pointer*/
        randomptr = (int *)malloc(sizeof(int));






        /*just open the file read it if it is null print error*/
        file = fopen(filename, "r");
        if(file==NULL)
        {
                perror("Can't find the source file.");

        }
        /*if it is not null then proceed getting values from it*/
        else if(file != NULL){
                fscanf(file, "%d %d %d", &metadata, &mapRow, &mapColumn);
                /*make array that will store the metadata we will get from file read store here*/
                marray = (int**)malloc( metadata * sizeof(int *));
                for (i = 0; i < metadata; i++)
                {
                        marray[i] = (int *)malloc( 3 * sizeof(int));
                }
                /*printf("%d %d %d", metadata, mapRow, mapColumn);*/


                /* fscanf(file,"%d %d %d",&row, &column, &amount)*/

                /*storing the metadata in that array that was made*/
                for(i = 0;i < metadata;i++){
                        fscanf(file,"%d %d %d",&row, &column, &amount);
                        for(j = 0;j < 3;j++){
                                if(j == 0){
                                        /*first column is row,second is columns,third is amount*/
                                        marray[i][j+0] = row;
                                        marray[i][j+1] = column;
                                        marray[i][j+2] = amount;
                                }
                        }

                }



                /* for(i = 0;i < metadata; i++){
                   for(j = 0;j < 3;j++){
                   printf("%d",marray[i][j]);

                   }
                   printf("\n");
                   }*/
                /*printf("%d", marray[14][1]);*/
                /*an 2D pointer array that is on heap memory*/
                mapBoard = (char **)malloc(mapRow * sizeof(char *));
                for (k = 0; k < mapRow; k++)
                {
                        mapBoard[k] = (char *)malloc(mapColumn * sizeof(char));
                }
                /*all these methods REFERENCE:my own assignment 1*/
                /* this function prints the borders of the map*/
                boardBorder(mapBoard, mapRow, mapColumn);
                boardObjects(marray, mapBoard, mapRow, mapColumn, metadata);
                displayBoard(mapBoard, mapRow, mapColumn);


                while (exit != 1)
                {


                        objectMovement(mapBoard, userinput, exit, mapRow, mapColumn, randomptr, snakeexit);
                        displayBoard(mapBoard, mapRow, mapColumn);

                        if (*randomptr == 1)
                        {
                                exit = 1;
                        }

                }


                for (k = 0; k < mapRow; k++)
                {
                        free(mapBoard[k]);
                }
                free(mapBoard);
                mapBoard = NULL;

                for(i = 0; i < metadata; i++)
                {
                        free(marray[i]);
                }
                free(marray);
                marray = NULL;

                free(randomptr);
                randomptr = NULL;
                fclose(file);

        }
        return 0;
}

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
                                        mapBoard[k][l] = '~';
                                }
                                else if (marray[i][j] == 2)
                                {
                                        k = marray[i][j - 2];
                                        l = marray[i][j-1];
                                        mapBoard[k][l] = 'x';
                                }
                                else if (marray[i][j] == 3){
                                        k = marray[i][j - 2];
                                        l = marray[i][j - 1];
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

void objectMovement(char **mapBoard, char userinput, int exit, int mapRow, int mapColumn, int *randomptr, int snakeexit){

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
                                        else if(mapBoard[k-1][l] == '~')
                                        {
                                                mapBoard[k][l] = '^';

                                        }

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
                                        snakeMovement(mapBoard,userinput,exit, mapRow,  mapColumn, randomptr, snakeexit, k ,l);

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
                                        else if(mapBoard[k+1][l] == '~')
                                        {
                                                mapBoard[k][l] = 'v';                                              
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
                                        snakeMovement(mapBoard,userinput,exit, mapRow,  mapColumn, randomptr, snakeexit,k ,l);
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
                                        else if(mapBoard[k][l-1] == '~')
                                        {

                                                mapBoard[k][l] = '<';

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
                                        snakeMovement(mapBoard,userinput,exit, mapRow,  mapColumn, randomptr, snakeexit, k,l);
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
                                        else if(mapBoard[k][l + 1] == '~')
                                        {
                                                mapBoard[k][l] = '>';
                                        }

                                        else
                                        {
                                                mapBoard[k][l] = ' ';
                                                l = l + 1;
                                                mapBoard[k][l] = '>';
                                        }
                                        snakeMovement(mapBoard,userinput,exit, mapRow,  mapColumn, randomptr, snakeexit,k ,l);
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
/*this method is mainly for the snake movement*/
void snakeMovement(char **mapBoard, char userinput, int exit, int mapRow, int mapColumn, int *randomptr, int snakeexit,int k, int l)
{
        /*iterating thru the mapBoard and declaring x and y as snake row and snake column*/
        int srow, scol;
        int x,y;

        for (x = 0; x < mapRow; x++)
        {
                for (y = 0; y < mapColumn; y++)
                {
                        if (mapBoard[x][y] == '~' )
                        {
                                srow = x;
                                scol = y;
                        }
                }
        }

        /*k is coming from object movement where k is rows of player so if snake row less than player row let the player move else if its a wall boundary or goal dont let the snake move*/
        if(srow < k)
        {
                if(mapBoard[srow + 1][scol] == 'o' || mapBoard[srow + 1][scol] == '-' || mapBoard[srow + 1][scol] == 'x')
                {
                        mapBoard[srow][scol] = '~';
                }
                /*if these movements come and the next thing is player then make snakeexit ans randompointer one so game can be exited is snake row snake column not these then consider empty space and let the snake move close to player*/
                else if(mapBoard[srow + 1][scol] == 'v' || mapBoard[srow + 1][scol] == '<' || mapBoard[srow + 1][scol] == '>' || mapBoard[srow + 1][scol] == '^')
                {
                        mapBoard[srow][scol] = ' ';
                        srow = srow + 1;
                        mapBoard[srow][scol] = '~';
                        snakeexit = 1;
                        *randomptr = 1;
                }
                else
                {
                        mapBoard[srow][scol] = ' ';
                        srow = srow + 1;
                        mapBoard[srow][scol] = '~';
                }
        }
        /*first basically judge that where the player is above snake below snake left to snake right to snake then move according judge for all and do the same thing*/
        else if(srow > k)
        {
                if(mapBoard[srow - 1][scol] == 'o' || mapBoard[srow - 1][scol] == '-' || mapBoard[srow - 1][scol] == 'x')
                {
                        mapBoard[srow][scol] = '~';
                }
                else if(mapBoard[srow - 1][scol] == 'v' || mapBoard[srow - 1][scol] == '<' || mapBoard[srow - 1][scol] == '>' || mapBoard[srow - 1][scol] == '^')
                {
                        mapBoard[srow][scol] = ' ';
                        srow = srow - 1;
                        mapBoard[srow][scol] = '~';
                        snakeexit = 1;
                        *randomptr = 1;
                }
                else
                {
                        mapBoard[srow][scol] = ' ';
                        srow = srow - 1;
                        mapBoard[srow][scol] = '~';
                }
        }
        else if(srow == k){
                if(scol > l){
                        if(mapBoard[srow][scol - 1] == 'o' || mapBoard[srow][scol -1] == '-' || mapBoard[srow][scol - 1] == 'x')
                        {
                                mapBoard[srow][scol] = '~';
                        }
                        else if(mapBoard[srow][scol - 1] == 'v' || mapBoard[srow][scol - 1] == '<' || mapBoard[srow][scol - 1] == '>' || mapBoard[srow][scol - 1] == '^'){
                                mapBoard[srow][scol] = ' ';
                                scol = scol - 1;
                                mapBoard[srow][scol] = '~';
                                snakeexit = 1;
                                *randomptr = 1;

                        }
                        else
                        {
                                mapBoard[srow][scol] = ' ';
                                scol = scol - 1;
                                mapBoard[srow][scol] = '~';
                        }
                }
                else if(scol < l){
                        if(mapBoard[srow][scol + 1] == 'o' || mapBoard[srow][scol +1] == '-' || mapBoard[srow][scol + 1] == 'x')
                        {
                                mapBoard[srow][scol] = '~';
                        }
                        else if(mapBoard[srow][scol + 1] == 'v' || mapBoard[srow][scol + 1] == '<' || mapBoard[srow][scol + 1] == '>' || mapBoard[srow][scol + 1] == '^'){
                                mapBoard[srow][scol] = ' ';
                                scol = scol + 1;
                                mapBoard[srow][scol] = '~';
                                snakeexit = 1;
                                *randomptr = 1;

                        }
                        else
                        {
                                mapBoard[srow][scol] = ' ';
                                scol = scol + 1;
                                mapBoard[srow][scol] = '~';
                        }

                }
        }

        /*incase next is a player then snake eats player exit becomes two prints you lose message*/
        if (snakeexit == 1)
        {

                *randomptr = 1;
                printf("You lost the game!!\n");

        }
}














