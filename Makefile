CC = gcc
CFLAGS = -lncurses
OBJ = Stack.o
PROG = stack

compile: $(OBJ)
	$(CC) -o $(PROG) main.c $(OBJ) $(CFLAGS)

Stack.o: Stack.c Stack.h
	$(CC) -c Stack.c

clean:
	rm -f *.o
