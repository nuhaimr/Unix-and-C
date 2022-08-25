CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = main.o messycalc.o terminal.o
EXEC = calculator


$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c messycalc.h terminal.h
	$(CC) -c main.c $(CFLAGS)

messycalc.o : messycalc.c messycalc.h terminal.h
	$(CC) -c messycalc.c $(CFLAGS)

terminal.o : terminal.c terminal.h
	$(CC) -c terminal.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)
