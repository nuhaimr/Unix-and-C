/*Name = Nuha Imran
Date = 24/03/22*/

#ifndef GAME_H
#define GAME_H
#define TRUE 1
int GameRun(char* filename);
void boardBorder(char **mapBoard,int mapRow, int mapColumn);
void displayBoard(char** mapBoard, int mapRow, int mapColumn);
void boardObjects(int **marray, char **mapBoard, int mapRow, int mapColumn, int metadataAmount);
void objectMovement(char **mapBoard, char userinput, int exit, int mapRow, int mapColumn, int *randomptr, int snakeexit);
void snakeMovement(char **mapBoard, char userinput, int exit, int mapRow, int mapColumn, int *randomptr, int snakeexit,int k, int l);
		




#endif
