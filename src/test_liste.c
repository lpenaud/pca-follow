#include <stdio.h>
#include "liste.h"

void afficher_s_node(s_node * node)
{
    printf("[");
    do {
        printf("%d,", *(int *)(node->data));
    } while ((node = node->next) != NULL);
    printf("]\n");
    return;
}

int main(void)
{
    int x = 42, y = 84;
    s_node * liste = list_create();

    printf("--------------Test insert----------\n");
    printf("Insert %d\n", x);
    liste = list_insert(liste, (void *) &x);
    afficher_s_node(liste);
    printf("Insert %d\n", y);
    liste = list_insert(liste, (void *) &y);
    afficher_s_node(liste);
 
    printf("--------------Test append----------\n");
    printf("Append %d\n", x);
    liste = list_append(liste, (void *) &x);
    afficher_s_node(liste);

    printf("--------------Test headRemove----------\n");
    liste = list_headRemove(liste);
    afficher_s_node(liste);

    printf("--------------Test destroy----------\n");
    list_destroy(liste);
    if (liste == NULL) {
        printf("La liste a bien été supprimée\n");
    } else {
        printf("La liste n'a pas été supprimée\n");
        afficher_s_node(liste);
    }

    return 0;
}

