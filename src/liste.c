#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

s_node * list_create(void)
{
    return NULL;
}

void * list_get_data(s_node * node)
{
    return node->data;
}

void list_set_data(s_node * node, void * data)
{
    node->data = data; 
}

s_node * list_insert(s_node * head, void * data)
{
    s_node * node = (s_node *) malloc(sizeof(s_node));
    list_set_data(node, data);
    node->next = head;
    return node;
}

s_node * list_append(s_node * head, void * data)
{
    if (head == NULL) return list_insert(head, data);

    s_node * node = head;

    while (node->next != NULL) {
        node = node->next;
    }

    node->next = (s_node *) malloc(sizeof(s_node));
    list_set_data(node->next, data);

    return head;
}

int list_process(s_node * head, int (*fct)(s_node * node, void * param), 
    void * param, s_node ** last);
// Application d'une fonction sur les données enregistrées
// dans la liste. last est le dernier noeud traité
// retourne 1 sur le parcours est arrêté avant la fin de la liste

s_node * list_insert_ordonne(s_node * head, int (*fct)(s_node * node, void * param),
    void * param, s_node ** last);

s_node * list_remove (s_node * head, void * data)
{
    if (head == NULL) return head;

    s_node * node;
    
    for (node = head; node->next != NULL; node = node->next) {
        if (node->data == data) {
            return list_headRemove(node);
        }
    }
    
    return head;
}

s_node * list_headRemove(s_node * head) {
    if (head == NULL) return head;
    s_node * n = head->next;
    free(head);
    return n;
}

void list_destroy(s_node * head) 
{
    if (head == NULL) return;

    s_node * node = head;

    while (node != NULL) {
        node = list_headRemove(node);
    }

    free(node);
    // printf("%p\n", (void *) node); -> nil
}
