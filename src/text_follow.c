#include <stdio.h>
#include <assert.h>

#include "test.h"
#include "follow.h"

text * test_load()
{
    text *text = text_load("example.txt");
    assert(text != NULL);
    return text;
}

int main(void)
{
    text *text;
    text = test_load();
    display_text(text);
    return 0;
}
