#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

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
    follow *f;
    ref = test_load();
    cur = text_load("cur.txt");


    putchar('\n');
    putchar('\n');
    f = create_follow(ref, cur);
    display_follow(f);

    follow_destroy(f);
    text_destroy(cur);
    return 0;
}
