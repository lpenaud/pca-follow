#include <stdio.h>
#include <assert.h>

#include "test.h"
#include "hachage.h"


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

int main(void)
{
    const unsigned int len = 5;
    strhash_table * table = test_init(len);

    test_add(table);

    table = test_destroy(table);
    return 0;
}
