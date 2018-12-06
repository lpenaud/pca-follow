#ifndef FOLLOW_H
#define FOLLoW_H

#include "hachage.h"

//  structure décrivant une instance de follow
typedef struct {
    strhash_table table;
    text * pTextRef;
} follow;

// strucutre décrivant un document
typedef struct {
    char *text; // texte brut
    // text & token représente la même données
    token **tokenize_text; // le text découpé

    // longeur du text brut, nb jetons total, nb jetons WORD, ...
} text;

// unité lexicale du texte
typedef struct {
    // espace  ' ', '\n', ou '\t'
    enum { WORD, SHORT_SPACE, SPACE, ERASE, INSERT, REPLACE, EMPTY } type;
    int textOffset; // position dans le texte (char *) d'origines
    union {
        char *word; // pointeur sur un mot de la table de hachage
        char space[4]; // 4 délimiteurs max
    } data;
} token;

text * text_load(const char *filename);

token * next_token_get(char *text, strhash_table *ht, int *offset);

// PLSC -> Plus Longue sous Séquence Commune
int ** plsc(text *ref, text *cur);

#endif
