#include <stdio.h>

#include "test.h"
#include "hachage.h"

int main(void)
{
    unsigned int len = 5;
    strhash_table * table = strhash_table_init(len);

    if (!table) return 1;

    return 0;
}

