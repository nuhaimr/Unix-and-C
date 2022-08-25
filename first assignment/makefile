CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = main.o map.o terminal.o game.o
EXEC = maze

ifdef DARK
CFLAGS += -D DARK
DARK : clean $(EXEC)
endif

$(EXEC) : $(OBJ) 
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c game.h map.h terminal.h
	$(CC) -c main.c $(CFLAGS)

map.o : map.c map.h
	$(CC) -c map.c $(CFLAGS)

game.o : game.c game.h map.h terminal.h
	$(CC) -c game.c $(CFLAGS)

terminal.o : terminal.c terminal.h
	$(CC) -c terminal.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)

