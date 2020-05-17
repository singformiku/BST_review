CC = gcc

all:
	$(CC) -c json.c -o json.o
	$(CC) -c main.c -o main.o
	$(CC) json.o main.o -o main
	./main

clean:
	rm json.o main.o main