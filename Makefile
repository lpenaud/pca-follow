follow: follow.o liste.o
	gcc -Wall follow.o liste.o -o follow

follow.o: follow.c liste.h
	gcc -Wall -c follow.c -o follow.o

liste.o: liste.h liste.c
	gcc -Wall -c liste.c -o liste.o

