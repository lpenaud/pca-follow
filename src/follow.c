#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "follow.h"

void destroy_tokens(s_node *tokens)
{
    for (s_node *n = tokens; n; n = n->next) {
        free(n->data);
    }
    list_destroy(tokens);
}

s_node * tokens_append(s_node *n, token *t, strhash_table *ht, enum token_type type)
{
    token *data = (token *) malloc(sizeof(token));
    if (data == NULL) goto err;
    char *word = strhash_table_add(ht, t->data.word);
    data->data.word = word;
    data->type = type;
    if ((n = list_append(n, data)) == NULL) goto err;
    return n;
err:
    destroy_tokens(n);
    return NULL;
}

s_node * plsc(follow *f, text *cur)
{
    if (f == NULL) return NULL;
    text *ref = f->pTextRef;
    if (ref == NULL || cur == NULL) return NULL;
    unsigned int i, j, ref_word, cur_word;
    token *tik, *tok;
    s_node *res = NULL;
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
                if ((res = tokens_append(res, tok, f->table, REPLACE)) == NULL)
                    goto err;
                if ((res = tokens_append(res, tik, f->table, WORD)) == NULL)
                    goto err;
            } else {
                if ((res = tokens_append(res, tik, f->table, EMPTY)) == NULL)
                    goto err;
            }
        }
        if (ref_word > cur_word) {
            if ((res = tokens_append(res, tik, f->table, ERASE)) == NULL)
                 goto err;
        }
    }
    while (cur_word < cur->nb_word) {
        if ((tok = cur->tokenize_text[j++])->type != WORD) continue;
        if ((res = tokens_append(res, tok, f->table, INSERT)) == NULL)
            goto err;
        cur_word++;
    }
err:
    return res;
}

follow * create_follow(const char *filename)
{
    follow *f = (follow *) malloc(sizeof(follow));
    if (f == NULL) return NULL;
    f->pTextRef = text_load(filename);
    f->table = strhash_table_init(f->pTextRef->nb_word);
    return f;
}

void follow_destroy(follow *f)
{
    strhash_table_destroy(f->table);
    text_destroy(f->pTextRef);
    free(f);
}

void display_follow(follow *f)
{
    printf("# follow (%p)\n\n", f);
    display_text(f->pTextRef);
    putchar('\n');
    strhash_print(f->table);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
void display_tokens(s_node *tokens)
{
    s_node *n;
    token *t;
    for (n = tokens; n; n = n->next) {
        t = (token *) n->data;
        switch (t->type) {
            case WORD:
            case ERASE:
                printf(ANSI_COLOR_RED);
                break;
            case REPLACE:
                printf(ANSI_COLOR_BLUE);
                break;
            case INSERT:
                printf(ANSI_COLOR_GREEN);
                break;
        }
        printf("%s%s ", t->data.word, ANSI_COLOR_RESET);
    }
    putchar('\n');
}
#pragma GCC diagnostic pop
