ENV = ${C_ENV}
CC = gcc

CFLAGS = -W -Wall -ansi -std=gnu99
LDFLAGS = -lm

ifeq ($(ENV),DEBUG)
	CFLAGS = -W -Wall -ansi -std=gnu99 -Og
endif

ifeq ($(OS),Windows_NT)
	PRE_EXEC = .exe
else
	PRE_EXEC = .out
endif

all: test_hachage test_liste test_follow
ifeq ($(ENV),DEBUG)
	@echo "Génération du mode DEBUG"
else
	@echo "Génération en mode release"
endif

test_follow: bin/test.o bin/follow.o bin/test_follow.o
	$(CC) -o $@$(PRE_EXEC) $^ $(LDFLAGS)

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
