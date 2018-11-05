deps = follow.o liste.o
gcc = gcc -Wall

follow: $(deps)
	$(gcc) $(deps) -o follow

follow.o: follow.c liste.h
	$(gcc) -c follow.c -o follow.o

liste.o: liste.h liste.c
	$(gcc) -c liste.c -o liste.o

