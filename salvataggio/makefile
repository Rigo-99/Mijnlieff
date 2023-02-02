CC = g++
CFLAGS = -Wall -O3 --std=c++11

all : mijnlieff.exe

mijnlieff.exe : main.o tavola.o
	$(CC) main.o tavola.o -o mijnlieff.exe

main.o : main.cpp salvataggi.cpp roba.cpp tutto.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)

tavola.o : new_tavola.cpp new_tavola.h tutto.h
	$(CC) -c new_tavola.cpp -o tavola.o $(CFLAGS)

clean :
	rm *.o mijnlieff.exe

