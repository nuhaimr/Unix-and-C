/*Name:Nuha Imran*/
/*ID:20696366*/
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"
#include "undofeature.h"

/*checks command line arguments theyre supposed to be two one the filename
  and the other porgram name doing error checking then taking in what filenameuser enters and running the game
so apart from file name it should have program name where the argv will be the file name*/
int main(int argc,char *argv[])
{
        if (argc != 2)
        {
                printf("Usage: %s <filename>\n", argv[0]);

        }
        else{

                char* file = argv[1];
                GameRun(file);

        }
        return 0;


}
