CC=gcc
CFLAGS=-Wall -Wextra -pedantic
DEBUG_FILES = main.c AVLTree.c Node.c DataTypes/String.c


debug:
	$(CC) -g $(DEBUG_FILES)

out: main.c lib.o
	$(CC) $(CFLAGS) main.c lib.o -o main

lib.o: Node.o Stack.o String.o LinkedList.o
	$(CC) $(CFLAGS) -r Node.o Stack.o String.o LinkedList.o -o lib.o

AVLTree.o: AVLTree.c AVLTree.h Node.o
	$(CC) $(CFLAGS) -c AVLTree.c Node.o -o AVLTree.o

Stack.o: Stack.c Stack.h LinkedList.h Node.h
	$(CC) $(CFLAGS) -c Stack.c -o Stack.o

String.o: DataTypes/String.c DataTypes/String.h
	$(CC) $(CFLAGS) -c DataTypes/String.c -o String.o

LinkedList.o: LinkedList.c LinkedList.h Node.h
	$(CC) $(CFLAGS) -c LinkedList.c -o LinkedList.o

Node.o: Node.c Node.h
	$(CC) $(CFLAGS) -c Node.c -o Node.o

clean:
	del *.o
	del *.exe

run:
	make
	./main
	make clean