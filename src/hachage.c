#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hachage.h"
#include "liste.h"

int calc_cle_hash(char * str, const int size_hash_table)
{
     int i, cle = 0;
     for (i = 0; str[i] != '\0'; i++) {
        cle *= 2;
        cle += (int) str[i];
    }
     return cle % size_hash_table;
}

strhash_table * strhash_table_init(const unsigned int len)
{
    super_list *list;
    strhash_table *table = (strhash_table *) malloc(sizeof(strhash_table));
    if(!table) return NULL;

    table->len = len;
    list = (super_list *) malloc(sizeof(super_list) * len);
    if (!list) return NULL;

    for (unsigned int i = 0; i < len; i++) {
        list[i].node = list_create();
        list[i].len = 0;
    }
    table->list = list;

    return table;
}

strhash_table * strhash_table_destroy(strhash_table * table)
{
    unsigned int i, j;
    super_list *list;
    s_node *node;

    for (i = 0; i < table->len; i++) {
        list = table->list + i;
        for (j = 0; j < list->len; j++) {
            node = list->node + j;
            free(node->data);
        }
        list_destroy(list->node);
    }
    free(table->list);
 
    free(table);
    return table;
}

strhash_table * strhash_table_free(strhash_table * table)
{
    unsigned int i;
    super_list *list;
    for (i = 0; i < table->len; i++) {
        list = table->list + i;
        if (list->len > 0) {
            free(list->node->data);
            list->node = list_destroy(list->node);
            list->len = 0;
            return table;
        }
    }
    return table;
}
// remove list->data

int compare_str(s_node *node, void *param){
    int res = strcmp((char *) node->data, (char *) param);
    if (res < 0) return -1;
    if (res > 0) return 1;
    return 0;
}

char * strhash_table_add(strhash_table * table, char * str)
{
    char * to_insert = strdup(str);
    int index = calc_cle_hash(str, table->len);

    s_node *inserted_or_exist_node = list_ordered_append(&(table->list[index].node), compare_str, to_insert); 
    if(inserted_or_exist_node->data != to_insert) {
        free(to_insert);
    }
    return inserted_or_exist_node->data;
}

strhash_table * strhash_table_remove(strhash_table * table, char * str);
// list_process strcomp
// last -> élément à supprimer

void strhash_table_stat(strhash_table * table);
/*
    Nombre total élément
    Nombre minimum
    Nombre maximum
    Écart type du nombre d'éléments par entrée
*/

void strhash_print(strhash_table * table);
