#ifndef LISTE_H
#define LISTE_H

struct _list_node {
    void * data;
    struct _list_node *next;
};

typedef struct _list_node s_node;

s_node * list_create(void);
// creation d'une nouvelle list vide


void * list_get_data(s_node * node);
void list_set_data(s_node * node, void * data);
// lire ou écrire la donnée d'un noeud

s_node * list_insert(s_node * head, void * data);
// création et insertion d'un noeud en tête de list
// retourne la tete de la list

s_node * list_append(s_node * head, void * data);

int list_process(s_node * head, int (*fct)(s_node * node, void * param),
    void * param, s_node ** last);
// Application d'une fonction sur les données enregistrées
// dans la list. last est le dernier noeud traité
// retourne 1 sur le parcours est arrêté avant la fin de la list

s_node * list_ordered_append(s_node * head, int (*fct)(s_node * node, void * param),
    void * param);

s_node * list_remove (s_node * head, void * data);
// suprression de la première instance d'une
// donnée dans la list, retourne la tete de list

s_node * list_headRemove(s_node * head);
// suppression de la première instance d'une
// donnée dans la list, retourne la tête de list

s_node * list_destroy(s_node * head);
// destruction d'une list
// (La liberation des données n'est pas prise en charge)

#endif
