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
    ref = test_load();
    cur = text_load("cur.txt");
    display_text(ref);
    display_text(cur);
    text_destroy(ref);
    text_destroy(cur);
    return 0;
}
