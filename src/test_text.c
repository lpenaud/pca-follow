#include <stdio.h>
#include <assert.h>

#include "test.h"
#include "text.h"

text * test_load()
{
    text *txt = text_load("ref.txt");
    assert(txt != NULL);
    return txt;
}

void check_nb_token(text *txt, unsigned int nb_tokens[EMPTY + 1])
{
    assert(txt->nb_word == nb_tokens[WORD]);
    assert(txt->nb_short_space == nb_tokens[SHORT_SPACE]);
    assert(txt->nb_space == nb_tokens[SPACE]);
    assert(txt->nb_insert == nb_tokens[INSERT]);
    assert(txt->nb_replace == nb_tokens[REPLACE]);
    assert(txt->nb_empty == nb_tokens[EMPTY]);
}

int main(void)
{
    unsigned int nb_tokens_ref[EMPTY + 1], nb_tokens_cur[EMPTY + 1];
    text *ref, *cur;

    init_tab(nb_tokens_ref, EMPTY + 1, 0);
    init_tab(nb_tokens_cur, EMPTY + 1, 0);

    nb_tokens_ref[WORD] = 4;
    nb_tokens_ref[SHORT_SPACE] = 2;
    nb_tokens_ref[SPACE] = 1;

    nb_tokens_cur[WORD] = 5;
    nb_tokens_cur[SHORT_SPACE] = 3;
    nb_tokens_cur[SPACE] = 1;

    ref = test_load();
    cur = text_load("cur.txt");

    check_nb_token(ref, nb_tokens_ref);
    check_nb_token(cur, nb_tokens_cur);

    text_destroy(ref);
    text_destroy(cur);
    return 0;
}
