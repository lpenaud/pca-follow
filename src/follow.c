#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "follow.h"

void plsc(follow *f, text *cur)
{
    if (f == NULL) return;
    text *ref = f->pTextRef;
    if (ref == NULL || cur == NULL) return;
    unsigned int i, j, ref_word, cur_word;
    token *tik, *tok;
    j = i = ref_word = 0;
    while (ref_word < ref->nb_word) {
        tik = ref->tokenize_text[i++];
        if (tik->type != WORD) continue;
        cur_word = ref_word++;
        while (j < cur->nb_token && cur_word < ref_word) {
            tok = cur->tokenize_text[j++];
            if (tok->type != WORD) continue;
            cur_word++;
            if (strcmp(tik->data.word, tok->data.word) != 0) {
                if (cur_word > ref_word) {
                    printf("INSERT: %s (%s)\n", tik->data.word, tok->data.word);
                } else {
                    printf("REPLACE: %s (%s)\n", tik->data.word, tok->data.word);
                }
            }
        }
        if (ref_word > cur_word) {
            printf("ERASE: %s\n", tik->data.word);
        }
    }
    while (cur_word < cur->nb_word) {
        if ((tok = cur->tokenize_text[j++])->type != WORD) continue;
        printf("INSERT: %s\n", tok->data.word);
        cur_word++;
    }
}

follow * create_follow(text *ref, text *cur)
{
    follow *f = (follow *) malloc(sizeof(follow));
    if (f == NULL) return NULL;
    f->pTextRef = ref;
    f->table = strhash_table_init(ref->nb_word);
    plsc(f, cur);
    return f;
}

void follow_destroy(follow *f)
{
    strhash_table_destroy(f->table);
    free(f);
}

void display_follow(follow *f)
{
    printf("# follow (%p)\n\n", f);
    display_text(f->pTextRef);
    putchar('\n');
    strhash_print(f->table);
}
