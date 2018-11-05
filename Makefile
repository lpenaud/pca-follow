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
	EXEC = test_liste.exe
else
	EXEC = test_liste.out
endif

DEPS = liste test_liste

BIN = $(foreach dep, $(DEPS), bin/$(dep).o)
SRC = $(foreach dep, $(DEPS), src/$(dep).c)

all: $(EXEC)
ifeq ($(ENV),DEBUG)
	@echo "Génération du mode DEBUG"
else
	@echo "Génération en mode release"
endif

$(EXEC): $(BIN)
	$(CC) -o $@ $^ $(LDFLAGS)

bin/liste.o: src/liste.h

bin/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	-rm bin/*.o
	-rm $(EXEC)
