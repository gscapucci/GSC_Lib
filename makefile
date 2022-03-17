out: main.c lib.o
	gcc main.c lib.o -o main

lib.o: Node.o Stack.o String.o LinkedList.o
	gcc -r Node.o Stack.o String.o LinkedList.o -o lib.o

Stack.o: Stack.c Stack.h LinkedList.h Node.h
	gcc -c Stack.c -o Stack.o

String.o: DataTypes/String.c DataTypes/String.h
	gcc -c DataTypes/String.c -o String.o

LinkedList.o: LinkedList.c LinkedList.h Node.h
	gcc -c LinkedList.c -o LinkedList.o

Node.o: Node.c Node.h
	gcc -c Node.c -o Node.o

clean:
	del *.o
	del *.exe

run:
	make
	./main
	make clean