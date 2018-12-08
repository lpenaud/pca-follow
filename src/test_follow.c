#include <stdio.h>
#include <assert.h>

#include "test.h"
#include "follow.h"

text * test_load()
{
    text *text = text_load("ref.txt");
    assert(text != NULL);
    return text;
}

int main(void)
{
    text *ref, *cur;
    int **lg;
    ref = test_load();
    cur = text_load("cur.txt");

    lg = plsc(ref, cur);

    display_matrix(lg, ref->txt_len, cur->txt_len);
    putchar('\n');
    display_text(ref);
    putchar('\n');
    display_text(cur);

    text_destroy(ref);
    text_destroy(cur);
    free_matrix(lg, ref->txt_len);
    return 0;
}
