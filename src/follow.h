#ifndef FOLLOW_H
#define FOLLOW_H

#include "hachage.h"
#include "text.h"

#define ANSI_COLOR_RED     "\x1b[41m" //ERASE
#define ANSI_COLOR_GREEN   "\x1b[42m" //INSERT
#define ANSI_COLOR_BLUE    "\x1b[44m" //REPLACE
#define ANSI_COLOR_RESET   "\x1b[0m"

//  structure décrivant une instance de follow
typedef struct {
    strhash_table *table;
    text *pTextRef;
} follow;

// PLSC -> Plus Longue sous Séquence Commune
s_node * plsc(follow *f, const char *filename);

follow * create_follow(const char *filename);

void display_follow(follow *f);

void follow_destroy(follow *f);

void display_tokens(s_node *tokens);

void destroy_tokens(s_node *tokens);

#endif
