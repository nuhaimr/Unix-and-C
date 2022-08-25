/*Name:Nuha Imran*/
/*ID:20696366*/


#ifndef GAME_H

#define GAME_H
#define TRUE 1
void GameRun(int check);
void boardBorder(char **mapBoard,int mapRow, int mapColumn);
void boardObjects(int **marray, char **mapBoard, int mapRow, int mapColumn,  int metadataAmount);
void displayBoard(char** mapBoard, int mapRow, int mapColumn);
void objectMovement(char **mapBoard, char userinput, int exit, int mapRow, int mapColumn, int * randomptr);
void dark(int **marray,int exit,int mapRow,int mapColumn, char **mapBoard,int vision, char userinput, int metadataAmount, int *randomptr);



#endif
