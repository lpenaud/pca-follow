#include <stdio.h>
#include <assert.h>
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
    if (table->list) { 
        printf("La table n'a pas été détruite (%p)\n", table);
        assert(0);
    }
    return NULL;
}

void test_add(strhash_table *table)
{
    char str[STR_LEN_MAX+1], *inserted;
    unsigned int i, j;
    for (i = 0; i < 3; i++) {
        strcpy(str, "");
        for (j = 0; j < STR_LEN_MAX; j++) {
            str[j] = (char) ('a' + random_with_max(26));
        }
        str[j] = '\0';
        inserted = strhash_table_add(table, str);
        if (strcmp(inserted, str) != 0) {
            printf("Chaines non égale : \n\tstr = %s\n\tinserted = %s\n", str, inserted);
            assert(0);
        }
    }
    return;
}

int main(void)
{
    const unsigned int len = 5;
    strhash_table * table = test_init(len);

    test_add(table);
    strhash_print(table);

    table = test_destroy(table);
    return 0;
}

