CC=gcc
CFLAGS=-Wall -Wextra -pedantic
MAIN=main
MAIN_C=$(MAIN).c
DEBUG_FILES=$(MAIN_C) Node.c LinkedList.c Stack.c AVLTree.c DataTypes/*.c

out: $(MAIN_C) lib.o
	$(CC) $(CFLAGS) $(MAIN_C) lib.o -o $(MAIN)

debug:
	$(CC) -g $(DEBUG_FILES)

lib.o: Node.o Stack.o String.o LinkedList.o AVLTree.o
	$(CC) $(CFLAGS) -r Node.o Stack.o String.o LinkedList.o AVLTree.o -o lib.o

AVLTree.o: AVLTree.c AVLTree.h Node.o
	$(CC) $(CFLAGS) -c AVLTree.c -o AVLTree.o

Stack.o: Stack.c Stack.h LinkedList.o
	$(CC) $(CFLAGS) -c Stack.c -o Stack.o

String.o: DataTypes/String.c DataTypes/String.h
	$(CC) $(CFLAGS) -c DataTypes/String.c -o String.o

LinkedList.o: LinkedList.c LinkedList.h Node.o
	$(CC) $(CFLAGS) -c LinkedList.c -o LinkedList.o

Node.o: Node.c Node.h
	$(CC) $(CFLAGS) -c Node.c -o Node.o

clean:
	del Node.o Stack.o String.o LinkedList.o AVLTree.o
	del *.exe

lib:
	make lib.o
	del Node.o Stack.o String.o LinkedList.o AVLTree.o

run:
	make out
	./$(MAIN)