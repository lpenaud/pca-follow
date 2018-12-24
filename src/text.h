#ifndef TEXT_H
#define TEXT_H

#define BUFFER_MAX 255
#define SPACE_MAX 4

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
        char space[SPACE_MAX]; // 4 délimiteurs max
    } data;
} token;

// strucutre décrivant un document
typedef struct {
    char *txt; // texte brut
    // text & token représente la même données
    token **tokenize_text; // le text découpé
    unsigned int txt_len, nb_token, nb_word, nb_short_space, nb_space, nb_erase, nb_insert, nb_replace, nb_empty;
} text;

token * add_token(text *txt, int index, int len, enum token_type type);

text * text_load(const char *filename);

void text_destroy(text *content);

void display_text(text *content);

#endif
