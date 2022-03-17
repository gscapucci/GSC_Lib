out: main.c Stack.o String.o LinkedList.o Node.o
	gcc main.c Stack.o String.o LinkedList.o Node.o -o main

Stack.o: Stack.c Stack.h
	gcc -c Stack.c -o Stack.o

String.o: DataTypes/String.c DataTypes/String.h
	gcc -c DataTypes/String.c -o String.o

LinkedList.o: LinkedList.c LinkedList.h
	gcc -c LinkedList.c -o LinkedList.o

Node.o: Node.c Node.h
	gcc -c Node.c -o Node.o

clean:
	del *.o

run:
	make
	make clean
	./main

