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
    if (!head) return list_insert(head, data);

    s_node * node = head;

    while (node->next) {
        node = node->next;
    }

    node->next = (s_node *) malloc(sizeof(s_node));
    node->next->next = list_create();
    list_set_data(node->next, data);

    return head;
}

int list_process(s_node * head, int (*fct)(s_node * node, void * param),
    void * param, s_node ** last)
{
    if (!head) return 0;

    s_node * node;
    for (node = head; node; node = node->next) {
        if (fct(node, param) == 1) {
            *last = node;
            return 1;
        }
    }
    return 0;
}

s_node * list_ordered_append(s_node ** head, int (*fct)(s_node * node, void * param),
    void * param)
{
    // quand elle est vide
    if (!(*head)) {
        *head = list_insert(*head, param);
        return *head;
    }

    // insertion en tete
    s_node * node;
    if (fct(*head, param) == 1) {
        *head = list_insert(*head, param);
        return (*head);
    }

    // cas general
    int res;
    for(node = *head; node->next; node = node->next) {
        printf("%s\n", (char *) node->next->data);
        if ((res = fct(node->next, param)) == 1) {
            node->next = list_insert(node->next, param);
            return node->next;
        } else if (res == 0) {
            return node->next;
        }
    }
    if (fct(node, param) == 0) return node;

    *head = list_append(*head, param);
    return node->next;
}

s_node * list_remove (s_node * head, void * data)
{
    if (!head) return head;

    for (s_node * node = head; node->next; node = node->next) {
        if (node->next->data == data) {
            s_node * n = node->next->next;
            free(node->next);
            node->next = n;
            break;
        }
    }

    return head;
}

s_node * list_headRemove(s_node * head)
{
    if (!head) return head;
    s_node * n = head->next;
    free(head);
    return n;
}

s_node * list_destroy(s_node * head)
{
    if (!head) return head;

    s_node * node = head;

    while (node) {
        node = list_headRemove(node);
    }

    free(node);
    return node;
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
