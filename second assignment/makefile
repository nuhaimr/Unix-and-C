CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = main.o terminal.o game.o undofeature.o
EXEC = maze




$(EXEC) : $(OBJ) 
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c game.h terminal.h undofeature.h
	$(CC) -c main.c $(CFLAGS)

game.o : game.c game.h terminal.h undofeature.h
	$(CC) -c game.c $(CFLAGS)

terminal.o : terminal.c terminal.h
	$(CC) -c terminal.c $(CFLAGS)

undofeature.o : undofeature.c undofeature.h
	$(CC) -c undofeature.c $(CFALGS)
clean:
	rm -f $(EXEC) $(OBJ)

