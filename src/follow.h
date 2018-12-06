#ifndef FOLLOW_H
#define FOLLOW_H

#include "hachage.h"

#define BUFFER_MAX 255

enum token_type {
    WORD,
    SHORT_SPACE,
    SPACE,
    ERASE,
    INSERT,
    REPLACE,
    EMPTY
};

// unité lexicale du texte
typedef struct {
    // espace  ' ', '\n', ou '\t'
    enum token_type type;
    int textOffset; // position dans le texte (char *) d'origines
    union {
        char *word; // pointeur sur un mot de la table de hachage
        char space[4]; // 4 délimiteurs max
    } data;
} token;

// strucutre décrivant un document
typedef struct {
    char *txt; // texte brut
    // text & token représente la même données
    token **tokenize_text; // le text découpé
    unsigned int txt_len, nb_token, nb_word, nb_short_space, nb_space, nb_erase, nb_insert, nb_replace, nb_empty;
} text;

//  structure décrivant une instance de follow
typedef struct {
    strhash_table table;
    text * pTextRef;
} follow;

text * text_load(const char *filename);

token * next_token_get(char *text, strhash_table *ht, int *offset);

// PLSC -> Plus Longue sous Séquence Commune
int ** plsc(text *ref, text *cur);

#endif
