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
    for (node = head; node != last[0]->next; node = node->next) {
        fct(node, param);
    }
    return node ? 1 : 0;
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
