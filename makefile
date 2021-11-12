output: BinaryTree.o LinkedList.o
	gcc -shared -o lib/DataStructure.dll objectfile/BinaryTree.o objectfile/LinkedList.o
	

BinaryTree.o: BinaryTree/BinaryTree.c BinaryTree/BinaryTree.h
	gcc -c BinaryTree/BinaryTree.c -o objectfile/BinaryTree.o

LinkedList.o: LinkedList/LinkedList.c LinkedList/LinkedList.h
	gcc -c LinkedList/LinkedList.c -o objectfile/LinkedList.o
