#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <string.h>

#include "test.h"
#include "hachage.h"

#define STR_LEN_MAX 6

strhash_table * test_init(const unsigned int len)
{
    strhash_table * table = strhash_table_init(len);
    if (!table) {
        printf("Table n'a pas été créée\n");
        assert(0);
    }
    return table;
}

strhash_table * test_destroy(strhash_table * table)
{
    table = strhash_table_destroy(table);
    if (table->list->node) {
        printf("La table n'a pas été détruite (%p)\n", table->list->node);
        assert(0);
    }
    return NULL;
}

void test_add(strhash_table *table, char strings[][STR_LEN_MAX+1], const unsigned int len)
{
    char *inserted;
    unsigned int i, j;
    for (i = 0; i < len; i++) {
        for (j = 0; j < STR_LEN_MAX; j++) {
            strings[i][j] = (char) ('a' + random_with_max(25));
        }
        strings[i][j] = '\0';
        inserted = strhash_table_add(table, strings[i]);
        if (strcmp(inserted, strings[i]) != 0) {
            printf("Chaines non égale : \n\tstr = %s\n\tinserted = %s\n", strings[i], inserted);
            assert(0);
        }
    }
    return;
}

void test_remove(strhash_table *table, char strings[][STR_LEN_MAX+1], const unsigned int len) {
    unsigned int lens[len], i, j = 0;
    for (i = 0; i < len; i++) {
        lens[i] = table->list[i].len;
    }
    strhash_table_remove(table, strings[random_with_max(len)]);
    for (i = 0; i < len; i++) {
        if (lens[i] == table->list[i].len) j++;
    }
    if (j == len - 1) {
        printf("Aucun changement au niveau des tailles des listes\n");
        assert(0);
    }
}

int main(void)
{
    const unsigned int len = 3;
    strhash_table * table = test_init(len);
    char strings[5][STR_LEN_MAX+1];

    test_add(table, strings, 5);
    strhash_print(table);
    strhash_table_stat(table);
    test_remove(table, strings, len);

    table = test_destroy(table);
    return 0;
}
