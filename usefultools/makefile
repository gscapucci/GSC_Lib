cc=gcc
CFLAGS=-Wall -Wextra -pedantic

out: cat.c FileManager.o
	gcc cat.c FileManager.o -o cat
debug:
	gcc -g cat.c ../FileManagment/FileManager.c

FileManager.o: ../FileManagment/FileManager.c ../FileManagment/FileManager.h
	gcc -c ../FileManagment/FileManager.c -o FileManager.o