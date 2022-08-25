#include <stdio.h>
#include <stdlib.h>
#include "messycalc.h"
#include "terminal.h"

int main(int argc, char *argv[]){
/*error checking ensuring argument is 3 the program name filename and values*/
if(argc != 3){
printf("Usage ./calculator <filename> <initial number>\n");
printf("Please provide arguments \n");
/*else run the function use calculator first command line argument is filename second current total*/
}
else{
char* filename = argv[1];
float current_total = atof(argv[2]);
useCalculator(filename, current_total);

}
return 0;
}
