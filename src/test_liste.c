#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "liste.h"

#define CPL 72

int random(const int max)
{
    return rand() % max;
}

void printf_template(const char * name_test) {
    const char prefix[] = "Test";
    const int len = strlen(prefix) + strlen(name_test) + 1;
    const int nb_dash = (CPL - len) / 2;

    putchar('\n');
    for (int i = 0; i <= CPL; i++) {
        if (i == nb_dash) {
            printf("%s %s", prefix, name_test);
            i += len;
        } else {
            putchar('-');
        }
    }
    putchar('\n');
}

void afficher_s_node(s_node * liste)
{
    printf("liste = [");
    do {
        printf("%d,", *((int *)(liste->data)));
    } while((liste = liste->next));
    printf("]\n");
    return;
}

int calc_length(s_node * node)
{
    int i;
    for (i = 0; node; i++)
        node = node->next;
    return i;
}

s_node * test_insert(s_node * node, int tab[], const int len, const int max)
{
    const int length = calc_length(node);

    printf_template("insert");
    for (int i = 0; i < len; i++) {
        tab[i] = random(max);
        printf("\t%d. Insertion du nombre %d\n", i, tab[i]);
        node = list_insert(node, (tab + i));
    }

    assert(len + length == calc_length(node));
    afficher_s_node(node);
    return node;
}

s_node * test_append(s_node * node, int tab[], const int len, const int max)
{
    int length = calc_length(node);

    printf_template("append");
    for (int i = 0; i < len; i++) {
        tab[i] = random(max);
        printf("\t%d. Ajout du nombre %d\n", i, tab[i]);
        node = list_append(node, (tab + i));
    }

    assert(len + length == calc_length(node));
    afficher_s_node(node);
    return node;
}


s_node * test_remove(s_node * node, int data[], const int len, const int count)
{
    const int length = calc_length(node);
    int newLength;

    printf_template("remove");
    for (int i = 0; i <= count; i++) {
        int * ptn = (data + random(len - 1));
        printf("\tSuppression du noeud ayant comme valeur %d\n", *ptn);
        node = list_remove(node, (void *)ptn);
    }
    newLength = calc_length(node);
    printf("\n\tTaille : \n\t\t* Ancienne %d\n\t\t* Nouvelle %d\n", length, newLength);

    assert(length > newLength);
    afficher_s_node(node);
    return node;
}

s_node * test_headRemove(s_node * node, const int count)
{
    const int length = calc_length(node);

    printf_template("headRemove");
    for (int i = 0; i < count; i++) {
        printf("\t%d. Suprression de %d\n", i, *(int *)(node->data));
        node = list_headRemove(node);
    }

    assert(length - count == calc_length(node));
    afficher_s_node(node);
    return node;
}

void test_destroy(s_node * node) {
    printf_template("destroy");
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
    const int len = 10;
    s_node * liste = list_create();
    int to_insert[len], to_append[len];

    liste = test_insert(liste, to_insert, len, 50);
    liste = test_append(liste, to_append, len, 20);
    liste = test_remove(liste, to_insert, len, random(len));
    liste = test_headRemove(liste, len / 2);
    test_destroy(liste);

    return 0;
}
