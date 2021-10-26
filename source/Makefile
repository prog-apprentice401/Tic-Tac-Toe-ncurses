C_FLAGS=-Wall -lncurses
all: main.o misc.o win.o
	gcc main.o misc.o win.o $(C_FLAGS) -o TicTacToe.out

main.o: main.c win.h misc.h
	gcc main.c -c $(C_FLAGS)

misc.o: misc.c misc.h
	gcc misc.c -c $(C_FLAGS)

win.o: win.c win.h misc.h
	gcc win.c -c $(C_FLAGS)

clean:
	rm *.o *.out
