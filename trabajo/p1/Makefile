CC=gcc
CFLAGS=-I. -pthread

all: sislog cliente

sislog: sislog.c cola.c util.c # A RELLENAR DEPENDENCIAS
	# A RELLENAR COMANDOS
	$(CC) -o sislog sislog.c cola.c util.c $(CFLAGS) -g

cliente: # A RELLENAR DEPENDENCIAS
	# A RELLENAR COMANDOS
	|
	|

main : main.c util.c cola.c
	$(CC) -o main main.c util.c cola.c -g


limpia:
	-rm *.o

cleanall: limpia
	-rm sislog cliente *.dat

