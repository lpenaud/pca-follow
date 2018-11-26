#include <stdio.h>

#include "test.h"
#include "hachage.h"

int calc_cle_hash(char str[])
{
    int i, cle = 0;
    for (i = 0; str[i]; i++) {
        cle *= 2;
        cle += (int) str[i];
    }
    return cle % i;
}

int main(void)
{
    const unsigned int len = 5;
    strhash_table * table = strhash_table_init(len);
    char str[] = "Bonsoir";

    if (!table) {
        printf("Table n'a pas été créée\n");
        return 1;
    }

    table = strhash_table_destroy(table);

    // if (table) { // TODO: free(): invalid pointer
    //     printf("La table n'a pas été détruite (%p)\n", table);
    //     return 1;
    // }

    printf("%s -> cle : %d\n", str, calc_cle_hash(str));

    return 0;
}
