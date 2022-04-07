CC=gcc
CFLAGS=-Wall -Wextra -pedantic
MAIN=main
MAIN_C=$(MAIN).c
DEBUG_FILES=$(MAIN_C) Nodes/Node.c Nodes/DictionaryNode.c DataStructures/LinkedList.c DataStructures/Stack.c DataStructures/AVLTree.c DataTypes/String.c DataTypes/Dictionary.c DataTypes/BigInt.c FileManagment/FileManager.c

out: $(MAIN_C) gsc_lib.o
	$(CC) $(CFLAGS) $(MAIN_C) gsc_lib.o -o $(MAIN) -lm

debug:
	$(CC) -g $(DEBUG_FILES) -lm

gsc_lib.o: Node.o Stack.o String.o LinkedList.o AVLTree.o Dictionary.o DictionaryNode.o BigInt.o FileManager.o
	$(CC) $(CFLAGS) -r Node.o Stack.o String.o LinkedList.o AVLTree.o Dictionary.o DictionaryNode.o BigInt.o FileManager.o -o gsc_lib.o

Dictionary.o: DataTypes/Dictionary.c DataTypes/Dictionary.h
	$(CC) $(CFLAGS) -c DataTypes/Dictionary.c -o Dictionary.o

AVLTree.o: DataStructures/AVLTree.c DataStructures/AVLTree.h Node.o
	$(CC) $(CFLAGS) -c DataStructures/AVLTree.c -o AVLTree.o

Stack.o: DataStructures/Stack.c DataStructures/Stack.h LinkedList.o
	$(CC) $(CFLAGS) -c DataStructures/Stack.c -o Stack.o

String.o: DataTypes/String.c DataTypes/String.h
	$(CC) $(CFLAGS) -c DataTypes/String.c -o String.o

LinkedList.o: DataStructures/LinkedList.c DataStructures/LinkedList.h Node.o
	$(CC) $(CFLAGS) -c DataStructures/LinkedList.c -o LinkedList.o

Node.o: Nodes/Node.c Nodes/Node.h
	$(CC) $(CFLAGS) -c Nodes/Node.c -o Node.o

DictionaryNode.o: Nodes/DictionaryNode.c Nodes/DictionaryNode.h
	$(CC) $(CFLAGS) -c Nodes/DictionaryNode.c -o DictionaryNode.o

BigInt.o: DataTypes/BigInt.c DataTypes/BigInt.h
	$(CC) $(CFLAGS) -c DataTypes/BigInt.c -o BigInt.o

FileManager.o: FileManagment/FileManager.c FileManagment/FileManager.h
	$(CC) $(CFLAGS) -c FileManagment/FileManager.c -o FileManager.o

clean:
	del gsc_lib.o Node.o Stack.o String.o LinkedList.o AVLTree.o DictionaryNode.o Dictionary.o BigInt.o FileManager.o
	del *.exe

lib:
	make gsc_lib.o
	del Node.o Stack.o String.o LinkedList.o AVLTree.o DictionaryNode.o Dictionary.o BigInt.o FileManager.o

run:
	make debug
	make
	./main