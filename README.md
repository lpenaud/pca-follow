# pca-follow

## Notes

### Module 3
```c
// structure décrivant une instance de Follow
struct follow {
    // table hachage (UNE SEULE)
    struct text * pTextRef; // document de référence
    // document représentant le nouveau text
    // document représentant la différence entre les deux
};

// structure décrivant un document
struct text {
    char * text; // le texte brut
    // text & token représente la même données 
    struct token ** tokenizeText; // le text découpé

    // longeur du texte brut, nb jetons total, nb jetons WORD, ...
};

/* 
    init func 
    file text_content to text;
    longueur chaine file_seek func
    token NULL
/*

// unité lexicale du texte
struct token {
    enum { WORD, SHORT_SPACE, SPACE, ERASE, INSERT, REPLACE, EMPTY } type; // espace ' ', '\n', ou '\t'

    int textOffset; // position dans le texte (char *) d'origine

    union {
        char * word; // pointeur sur un mot de la table de hachage
        char space[4]; // 4 délimiteurs max
    } data; // (accès via `data.word` ou `data.space` selon le type

};
// ->next

// PLSC func -> Plus Longue sous Séquence Sommune
// Éléments communs doivent être dansle même ordre, mais pas nécessairement consécutifs
```

```

// stackoverflow "file to char"
struct text * textLoad(const char * filename);

parser ne token à partir d'un offset dans le text burt. Une token peut être soit un espace court (ou long soit un mot)
Remarque : utiliser strhash_wordAdd

struct token * nextTokenGet(char * text, struct strhash_table * ht, int *offset);
text += offset
if (text == '\0') return NULL;
if (text == ' ' || text = '\n' || text == '\r')
// boucle tant qu'on a des epsace puis on crée et templi la struct token associée
else
    boucle tant qu'on a pas d'espace puis on crée et rempli la struct token associée
offset = newOffeset;

utiliser la fonction précédente dans une boucle pour lire et stocker toutes les tokens associées au texte brut
int textParse(struct text *ptext, stuct strhash_table *ht);
while (t = nextTokenGet(ptext->text, ht, &offset))
    ajout de la token dans le tableau de pointeurs 
    utilisation de realloc pour réallouer le tableau si nécessaire


```
