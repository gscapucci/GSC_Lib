CC=gcc
CFLAGS=-Wall -Wextra -pedantic
MAIN=main
MAIN_C=$(MAIN).c
DEBUG_FILES=$(MAIN_C) Nodes/Node.c Nodes/DictionaryNode.c LinkedList.c Stack.c AVLTree.c DataTypes/String.c DataTypes/Dictionary.c DataTypes/BigInt.c

out: $(MAIN_C) gsc_lib.o
	$(CC) $(CFLAGS) $(MAIN_C) gsc_lib.o -o $(MAIN)

debug:
	$(CC) -g $(DEBUG_FILES)

gsc_lib.o: Node.o Stack.o String.o LinkedList.o AVLTree.o Dictionary.o DictionaryNode.o BigInt.o
	$(CC) $(CFLAGS) -r Node.o Stack.o String.o LinkedList.o AVLTree.o Dictionary.o DictionaryNode.o -o gsc_lib.o

Dictionary.o: DataTypes/Dictionary.c DataTypes/Dictionary.h
	$(CC) $(CFLAGS) -c DataTypes/Dictionary.c -o Dictionary.o

AVLTree.o: AVLTree.c AVLTree.h Node.o
	$(CC) $(CFLAGS) -c AVLTree.c -o AVLTree.o

Stack.o: Stack.c Stack.h LinkedList.o
	$(CC) $(CFLAGS) -c Stack.c -o Stack.o

String.o: DataTypes/String.c DataTypes/String.h
	$(CC) $(CFLAGS) -c DataTypes/String.c -o String.o

LinkedList.o: LinkedList.c LinkedList.h Node.o
	$(CC) $(CFLAGS) -c LinkedList.c -o LinkedList.o

Node.o: Nodes/Node.c Nodes/Node.h
	$(CC) $(CFLAGS) -c Nodes/Node.c -o Node.o

DictionaryNode.o: Nodes/DictionaryNode.c Nodes/DictionaryNode.h
	$(CC) $(CFLAGS) -c Nodes/DictionaryNode.c -o DictionaryNode.o

BigInt.o: DataTypes/BigInt.c DataTypes/BigInt.h
	$(CC) $(CFLAGS) -c DataTypes/BigInt.c -o BigInt.o

clean:
	del Node.o Stack.o String.o LinkedList.o AVLTree.o DictionaryNode.o Dictionary.o gsc_lib.o
	del *.exe

lib:
	make gsc_lib.o
	del Node.o Stack.o String.o LinkedList.o AVLTree.o DictionaryNode.o Dictionary.o

run:
	make out
	./$(MAIN)