#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"

void printf_template(const char * name_test, const char ch)
{
    const char prefix[] = "Test";
    const int len = strlen(prefix) + strlen(name_test) + 1;
    const unsigned int nb_ch = (CPL - len) / 2;

    putchar('\n');
    for (unsigned int i = 0; i <= CPL; i++) {
        if (i == nb_ch) {
            printf("%s %s", prefix, name_test);
            i += len;
        } else {
            putchar(ch);
        }
    }
    putchar('\n');
}

int random_with_max(const int max)
{
    return rand() % (max + 1);
}

void init_tab(unsigned int tab[], const unsigned int len, const unsigned int value)
{
    for (unsigned int i = 0; i < len; i++) tab[i] = value;
}
