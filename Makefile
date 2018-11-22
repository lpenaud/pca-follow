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

DEPS = liste test_liste test

BIN = $(foreach dep, $(DEPS), bin/$(dep).o)
SRC = $(foreach dep, $(DEPS), src/$(dep).c)

test_hachage: bin/test.o bin/test_hachage.o
	$(CC) -o $@$(PRE_EXEC) $^ $(LDFLAGS)
ifeq ($(ENV),DEBUG)
	@echo "Génération du mode DEBUG"
else
	@echo "Génération en mode release"
endif

test_liste: bin/liste.o bin/test.o bin/test_liste.o
	$(CC) -o $@$(PRE_EXEC) $^ $(LDFLAGS)

bin/liste.o: src/liste.h

bin/hachage.o: src/hachage.h

bin/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	-rm bin/*.o
	-rm *.out
	-rm *.exe
