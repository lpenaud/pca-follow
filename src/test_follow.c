#include <stdio.h>

#include "test.h"
#include "follow.h"

int main(void) {
    follow *f;
    text *ref, *cur;

    ref = text_load("ref.txt");
    cur = text_load("cur.txt");
    printf("**ref**\n");
    display_text(ref);
    printf("**cur**\n");
    display_text(cur);

    f = create_follow(ref, cur);
    follow_destroy(f);
    return 0;
}
