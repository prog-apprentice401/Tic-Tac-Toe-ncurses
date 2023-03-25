C_FLAGS=-Wall -lncurses
all: main.o misc.o win.o colorPairs.o
	gcc main.o misc.o win.o colorPairs.o $(C_FLAGS) -o ttt

main.o: main.c win.o misc.o colorPairs.o
	gcc main.c -c $(C_FLAGS)

misc.o: misc.c misc.h colorPairs.o
	gcc misc.c -c $(C_FLAGS)

win.o: win.c win.h misc.o colorPairs.o
	gcc win.c -c $(C_FLAGS)

colorPairs.o: colorPairs.h colorPairs.c
	gcc colorPairs.c -c $(C_FLAGS)

clean:
	rm *.o ttt
