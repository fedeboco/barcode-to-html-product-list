#Este archivo enlaza y compila todos los archivos necesarios del programa

CC = gcc
CFLAGS = -ansi -pedantic -Wall

all: inventory

inventory: log.o product.o vector.o utils.o inventory.o main.o 
	$(CC) $(CFLAGS) -o inventory log.o product.o vector.o main.o utils.o inventory.o

log.o: log.c types.h english.h product.h log.h
	$(CC) $(CFLAGS) -o log.o -c log.c

product.o: product.c types.h product.h
	$(CC) $(CFLAGS) -o product.o -c product.c
	
vector.o: vector.c types.h vector.h product.h
	$(CC) $(CFLAGS) -o vector.o -c vector.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -o utils.o -c utils.c

inventory.o: inventory.c inventory.h
	$(CC) $(CFLAGS) -o inventory.o -c inventory.c

main.o: main.c types.h vector.h main.h product.h log.h utils.h inventory.h
	$(CC) $(CFLAGS) -o main.o -c main.c
	
clean:
	rm *.o
