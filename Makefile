DEBUG = true
CC = gcc

ifeq ($(DEBUG),true)
	CFLAGS = -W -Wall -ansi -std=c99 -g -ggdb
	LDFLAGS =
else
	CFLAGS = -W -Wall -ansi -std=c99
	LDFLAGS =
endif

EXEC = test_liste
DEPS = liste test_liste

BIN = $(foreach dep, $(DEPS), bin/$(dep).o)
SRC = $(foreach dep, $(DEPS), src/$(dep).c)

all: $(EXEC)
ifeq ($(DEBUG),true)
	@echo "Génération du mode debug"
else
	@echo "Génération en mode release"
endif

test_liste: $(BIN)
	$(CC) -o $@ $^ $(LDFLAGS)

bin/liste.o: src/liste.h

bin/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm bin/*.o
	rm $(EXEC)
