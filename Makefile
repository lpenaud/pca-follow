ENV = ${C_ENV}
CC = gcc

CFLAGS = -W -Wall -ansi -std=gnu99
LDFLAGS = -lm

ifeq ($(ENV),DEBUG)
	CFLAGS += -Og
endif

all: test_hachage.out test_liste.out test_text.out
ifeq ($(ENV),DEBUG)
	@echo "Génération du mode DEBUG"
else
	@echo "Génération en mode release"
endif

test_text.out: bin/test.o bin/text.o bin/test_text.o bin/hachage.o bin/liste.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_hachage.out: bin/test.o bin/test_hachage.o bin/hachage.o bin/liste.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_liste.out: bin/liste.o bin/test.o bin/test_liste.o
	$(CC) -o $@ $^ $(LDFLAGS)

bin/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	-rm bin/*.o
	-rm *.out
