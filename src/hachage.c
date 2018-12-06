#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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

int compare_str_add(s_node *node, void *param)
{
    int res = strcmp((char *) node->data, (char *) param);
    if (res < 0) return -1;
    if (res > 0) return 1;
    return 0;
}

int find_str_node(s_node *node, void *param)
{
    return strcmp((char *) node->data, (char *) param) == 0 ? 1 : 0;
}

void strhash_print(strhash_table * table)
{
    unsigned int i, j;
    super_list *list;
    s_node *node;

    printf("Hash table %p\n", table);
    for (i = 0; i < table->len; i++) {
        list = table->list + i;
        printf("\tList %p\n", list);
        for (j = 0, node = list->node; j < list->len; j++, node = node->next) {
            printf("\t\t%d. %s\n", j, (char *) node->data);
        }
    }

    return;
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
    unsigned int i;
    super_list *list;
    s_node *node;

    for (i = 0; i < table->len; i++) {
        list = table->list + i;
        for (node = list->node; node != NULL; node = node->next) {
//            printf("%s\n", node->data);
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

char * strhash_table_add(strhash_table * table, char * str)
{
    char * to_insert = strdup(str);
    int index = calc_cle_hash(str, table->len);

    s_node *inserted_or_exist_node = list_ordered_append(&(table->list[index].node), &compare_str_add, to_insert);
    if (inserted_or_exist_node->data == to_insert)
        table->list[index].len++;
    return (char *) inserted_or_exist_node->data;
}

strhash_table * strhash_table_remove(strhash_table * table, char * str)
{
    const int index = calc_cle_hash(str, table->len);
    if (table->list[index].len == 0) return table;

    s_node *find_node;
    const int result = list_process(table->list[index].node, &find_str_node, str, &find_node);
    if (result == 1) {
        free(find_node->data);
        table->list[index].node = list_remove(table->list[index].node, find_node->data);
        table->list[index].len--;
    }
    return table;
}

void strhash_table_stat(strhash_table * table)
{
    unsigned int i;
    unsigned int len, min, max;
    float deviation, moy;

    len = max = min = table->list[0].len;
    for (i = 1; i < table->len; i++) {
        if (table->list[i].len > max) max = table->list[i].len;
        else if (table->list[i].len < min) min = table->list[i].len;
        len += table->list[i].len;
    }

    moy = (float)len / table->len;
    deviation = 0;
    for (i = 0; i < table->len; i++) {
        deviation += (table->list[i].len - moy) * (table->list[i].len - moy);
    }
    deviation = (float) sqrt(deviation / table->len);

    printf("Table hachage : %p\n", table);
    printf("\tNombre total d'élément : %u\n", len);
    printf("\tNombre minimum : %u\n", min);
    printf("\tNombre maximum : %u\n", max);
    printf("\tÉcart type du nombre d'éléments par entrée : %.2f\n", deviation);

    return;
}
