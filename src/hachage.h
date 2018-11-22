#ifndef HACHAGE_H
#define HACHAGE_H

#include "liste.h"

typedef struct {
    s_node * list;
    unsigned int len;
} super_list;

typedef struct {
    super_list * list;
    unsigned int len; 
} strhash_table;

strhash_table * strhash_table_init(const unsigned int len);
// malloc sizeof super_list * len
// len = len
// list_create * len

strhash_table * strhash_table_destroy(strhash_table * table);

strhash_table * strhash_table_free(strhash_table * table);
// remove list->data

strhash_table * strhash_table_add(strhash_table * table, char * str);
// str_dump(
// ordered_append(

strhash_table * strhash_table_remove(strhash_table * table, char * str);

void strhash_table_stat(strhash_table * table);
/*
    Nombre total élément
    Nombre minimum
    Nombre maximum
    Écart type du nombre d'éléments par entrée
*/

void strhash_print(strhash_table * table);

#endif

