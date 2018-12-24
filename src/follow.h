#ifndef FOLLOW_H
#define FOLLOW_H

#include "hachage.h"
#include "text.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))

//  structure décrivant une instance de follow
typedef struct {
    strhash_table *table;
    text *pTextRef;
} follow;

// PLSC -> Plus Longue sous Séquence Commune
void plsc(follow *f, text *cur);

follow * create_follow(text *ref, text *cur);

void display_follow(follow *f);

void follow_destroy(follow *f);

token * next_token_get(char *text, strhash_table *ht, int *offset);

#endif
