#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "liste.h"

#define CPL 72

int random(const int max)
{
    return rand() % (max + 1);
}

void printf_template(const char * name_test, const char ch) {
    const char prefix[] = "Test";
    const int len = strlen(prefix) + strlen(name_test) + 1;
    const unsigned int nb_ch = (CPL - len) / 2;

    putchar('\n');
    for (unsigned int i = 0; i <= CPL; i++) {
        if (i == nb_ch) {
            printf("%s %s", prefix, name_test);
            i += len;
        } else {
            putchar(ch);
        }
    }
    putchar('\n');
}

void afficher_s_node(s_node * list)
{
    printf("\nliste = [");
    while (list) {
        printf("%d,", *((int *)(list->data)));
        list = list->next;
    }
    printf("]\n");
    return;
}

unsigned int calc_length(s_node * node)
{
    unsigned int i = 0;
    while (node) {
        node = node->next;
        i++;
    }
    return i;
}

int process_produit(s_node * node, void * param)
{
    int data = *(int *)(node->data), nb = *(int *)(param);

    *(int *)(node->data) = *(int *)node->data * nb;
    printf("\t\t- %d * %d = %d\n", data, nb, *(int *)(node->data));
    assert(data * nb == *(int *)(node->data));

    return 0;
}

int tri_int(s_node * node, void * param)
{
    int data = *(int *) node->data;
    int nb = *(int *) param;
    if (data > nb) return 1;
    if (data < nb) return -1;
    return 0;
}

s_node * test_insert(s_node * node, int tab[], const unsigned int len, const unsigned int max)
{
    const unsigned int length = calc_length(node);
    unsigned int new_length;

    printf_template("insert", '-');
    for (unsigned int i = 0; i < len; i++) {
        tab[i] = random(max);
        printf("\t%d. Insertion du nombre %d\n", i, tab[i]);
        node = list_insert(node, (tab + i));
    }
    new_length = calc_length(node);
    printf("\n\tTaille : \n\t\t- Ancienne %d\n\t\t- Nouvelle %d\n", length, new_length);

    assert(len + length == calc_length(node));
    afficher_s_node(node);
    return node;
}

s_node * test_append(s_node * node, int tab[], const unsigned int len, const unsigned int max)
{
    const unsigned int length = calc_length(node);
    unsigned int new_length;

    printf_template("append", '-');
    for (unsigned int i = 0; i < len; i++) {
        tab[i] = random(max);
        printf("\t%d. Ajout du nombre %d\n", i, tab[i]);
        node = list_append(node, (tab + i));
    }
    new_length = calc_length(node);
    printf("\n\tTaille : \n\t\t- Ancienne %d\n\t\t- Nouvelle %d\n", length, new_length);

    assert(len + length == new_length);
    afficher_s_node(node);
    return node;
}

s_node * test_process(s_node * node) {
    unsigned int res, nb = 2;

    printf_template("process", '-');
    printf("Liste original");

    afficher_s_node(node);
    res = list_process(node, &process_produit, &nb, &node);

    printf("Nouvelle liste");
    afficher_s_node(node);

    assert(res == 0);
    return node;
}

s_node * test_ordered_append(s_node * node)
{
    static const int tab[2] = { -1, 2 };
    const unsigned int new_len = calc_length(node) + 2;

    printf_template("ordered_append", '-');
    printf("Avant :\t");
    afficher_s_node(node);

    for (unsigned int i = 0; i < 2; i++) {
        printf("Insertion du nombre %d\n", tab[i]);
        node = list_ordered_append(&node, &tri_int, (void *)(tab + i));
    }

    printf("Après :");
    afficher_s_node(node);
    assert(new_len == calc_length(node));
    return node;
}

s_node * test_remove(s_node * node, int data[], const unsigned int len, const unsigned int count)
{
    const unsigned int length = calc_length(node);
    unsigned int new_length;

    printf_template("remove", '-');
    for (unsigned int i = 0; i <= count; i++) {
        int * ptn = (data + random(len - 1));
        printf("\tSuppression du noeud ayant comme valeur %d\n", *ptn);
        node = list_remove(node, (void *)ptn);
    }
    new_length = calc_length(node);
    printf("\n\tTaille : \n\t\t- Ancienne %d\n\t\t- Nouvelle %d\n", length, new_length);

    assert((length == 0 && new_length == 0) || length > new_length);
    afficher_s_node(node);
    return node;
}

s_node * test_headRemove(s_node * node, const unsigned int count)
{
    const unsigned int length = calc_length(node);
    unsigned int new_length;

    printf_template("headRemove", '-');
    for (unsigned int i = 0; i < count; i++) {
        printf("\t%d. Supression de %p\n", i, node);
        node = list_headRemove(node);
    }
    new_length = calc_length(node);
    printf("\n\tTaille : \n\t\t- Ancienne %d\n\t\t- Nouvelle %d\n", length, new_length);

    assert((length == 0 && new_length == 0) || length - count == calc_length(node));
    afficher_s_node(node);
    return node;
}

void test_destroy(s_node * node) {
    printf_template("destroy", '-');
    node = list_destroy(node);
    assert(!node);
    if (!node) {
        printf("La liste a bien été supprimée\n");
    } else {
        printf("La liste n'a pas été supprimée\n");
        afficher_s_node(node);
    }
}

int main(void)
{
    const unsigned int len = 10, max = 50;
    s_node * list = list_create();
    int to_insert[len], to_append[len];

    printf_template("liste non null", '=');

    list = test_insert(list, to_insert, len, max);
    list = test_append(list, to_append, len, max);
    list = test_process(list);
    list = test_ordered_append(list);
    list = test_remove(list, to_append, len, random(len));
    list = test_headRemove(list, len / 2);
    test_destroy(list);

    printf_template("liste null", '=');

    test_destroy(list);
    list = list_create();
    test_append(list, to_append, 2, 20);
    list = list_destroy(list);

    list = list_create();
    list = test_process(list);

    list = test_ordered_append(list);
    list = list_destroy(list);

    test_remove(list, to_insert, 2, random(len));
    list = list_destroy(list);

    list = list_create();
    test_headRemove(list_create(), 2);
    list = list_destroy(list);

    list = list_create();
    test_destroy(list);


    return 0;
}
