CC=gcc
CFLAGS=-Wall -Wextra -pedantic
MAIN=main
MAIN_C=$(MAIN).c
DEBUG_FILES=$(MAIN_C) Nodes/Node.c Nodes/DictionaryNode.c LinkedList.c Stack.c AVLTree.c DataTypes/String.c DataTypes/Dictionary.c DataTypes/BigInt.c

out: $(MAIN_C) gsc_lib.o
	$(CC) $(CFLAGS) $(MAIN_C) Ofiles/gsc_lib.o -o $(MAIN)

debug:
	$(CC) -g $(DEBUG_FILES)

gsc_lib.o: Node.o Ofiles/Stack.o Ofiles/String.o Ofiles/LinkedList.o Ofiles/AVLTree.o Ofiles/Dictionary.o Ofiles/DictionaryNode.o Ofiles/BigInt.o
	$(CC) $(CFLAGS) -r Ofiles/Node.o Ofiles/Stack.o Ofiles/String.o Ofiles/LinkedList.o Ofiles/AVLTree.o Ofiles/Dictionary.o Ofiles/DictionaryNode.o Ofiles/BigInt.o -o Ofiles/gsc_lib.o

Dictionary.o: DataTypes/Dictionary.c DataTypes/Dictionary.h
	$(CC) $(CFLAGS) -c DataTypes/Dictionary.c -o Ofiles/Dictionary.o

AVLTree.o: AVLTree.c AVLTree.h Ofiles/Node.o
	$(CC) $(CFLAGS) -c AVLTree.c -o Ofiles/AVLTree.o

Stack.o: Stack.c Stack.h Ofiles/LinkedList.o
	$(CC) $(CFLAGS) -c Stack.c -o Ofiles/Stack.o

String.o: DataTypes/String.c DataTypes/String.h
	$(CC) $(CFLAGS) -c DataTypes/String.c -o Ofiles/String.o

LinkedList.o: LinkedList.c LinkedList.h Ofiles/Node.o
	$(CC) $(CFLAGS) -c LinkedList.c -o Ofiles/LinkedList.o

Node.o: Nodes/Node.c Nodes/Node.h
	$(CC) $(CFLAGS) -c Nodes/Node.c -o Ofiles/Node.o

DictionaryNode.o: Nodes/DictionaryNode.c Nodes/DictionaryNode.h
	$(CC) $(CFLAGS) -c Nodes/DictionaryNode.c -o Ofiles/DictionaryNode.o

BigInt.o: DataTypes/BigInt.c DataTypes/BigInt.h
	$(CC) $(CFLAGS) -c DataTypes/BigInt.c -o Ofiles/BigInt.o

clean:
	cd Ofiles
	del Node.o Stack.o String.o LinkedList.o AVLTree.o DictionaryNode.o Dictionary.o BigInt.o gsc_lib.o
	del *.exe
	cd ..
	del *.exe

lib:
	make gsc_lib.o
	cd Ofiles
	del Node.o Stack.o String.o LinkedList.o AVLTree.o DictionaryNode.o Dictionary.o BigInt.o
	cd ..

run:
	make debug
	make
	./main