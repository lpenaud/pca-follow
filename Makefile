ENV = ${C_ENV}
CC = gcc

ifeq ($(ENV),DEBUG)
	CFLAGS = -W -Wall -ansi -std=c99 -Og
	LDFLAGS =
else
	CFLAGS = -W -Wall -ansi -std=c99
	LDFLAGS =
endif

ifeq ($(OS),Windows_NT)
	PRE_EXEC = .exe
else
	PRE_EXEC = .out
endif

all: test_hachage test_liste
ifeq ($(ENV),DEBUG)
	@echo "Génération du mode DEBUG"
else
	@echo "Génération en mode release"
endif

test_hachage: bin/test.o bin/test_hachage.o bin/hachage.o bin/liste.o
	$(CC) -o $@$(PRE_EXEC) $^ $(LDFLAGS)

test_liste: bin/liste.o bin/test.o bin/test_liste.o
	$(CC) -o $@$(PRE_EXEC) $^ $(LDFLAGS)

bin/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	-rm bin/*.o
	-rm *.out
	-rm *.exe
