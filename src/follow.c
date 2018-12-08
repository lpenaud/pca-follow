#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "follow.h"

text * text_load(const char *filename)
{
    size_t i, nb_space, nb_car;
    char buffer[BUFFER_MAX], *tmp;
    FILE *fp;
    text *content;
    token **tik, *tok;

    if ((content = (text *) malloc(sizeof(text))) == NULL) return NULL;
    if ((content->txt = (char *) malloc(sizeof(char))) == NULL) {
        free(content);
        return NULL;
    }
    if ((fp = fopen(filename, "r")) == NULL) {
        free(content->txt);
        free(content);
        return NULL;
    }

    content->txt_len = 1;
    while (fgets(buffer, BUFFER_MAX, fp) != NULL)  {
        content->txt_len += strlen(buffer);
        tmp = (char *) realloc(content->txt, sizeof(char) * (content->txt_len + 2));
        if (tmp == NULL) {
            free(content->txt);
            free(content);
            free(tmp);
            fclose(fp);
            return NULL;
        }
        content->txt = tmp;
        strcat(content->txt, buffer);
    }
    fclose(fp);

    if ((content->tokenize_text = (token **) malloc(sizeof(token *))) == NULL) {
        free(content->txt);
        free(content);
        free(tmp);
    }
    content->nb_token =
    content->nb_word =
    content->nb_short_space =
    content->nb_space =
    content->nb_erase =
    content->nb_insert =
    content->nb_replace =
    content->nb_empty =
    nb_space =
    nb_car = 0;
    for (i = 0; i < content->txt_len; i++) {
        switch (content->txt[i]) {
            case ' ':
            case '\n':
            case '\t':
                nb_space++;
                if (nb_car > 0) {
                    tok = (token *) malloc(sizeof(token));
                    if (tok == NULL) {
                        free(content->tokenize_text);
                        free(content->txt);
                        free(content);
                        return NULL;
                    }
                    tok->textOffset = i - nb_car;
                    tok->type = WORD;
                    tok->data.word = NULL;
                    content->nb_token++;
                    content->nb_word++;
                    tik = (token **) realloc(content->tokenize_text, sizeof(token **) * content->nb_token);
                    if (tik == NULL) {
                        free(tok);
                        free(content->tokenize_text);
                        free(content->txt);
                        free(content);
                        return NULL;
                    }
                    tik[content->nb_token - 1] = tok;
                    content->tokenize_text = tik;
                    nb_car = 0;
                }
                break;
            default:
                nb_car++;
                if (nb_space > 0) {
                    tok = (token *) malloc(sizeof(token));
                    if (tok == NULL) {
                        free(content->tokenize_text);
                        free(content->txt);
                        free(content);
                        return NULL;
                    }
                    tok->data.word = NULL;
                    tok->textOffset = i - nb_space;
                    if (nb_space > 4) {
                        tok->type = SPACE;
                        content->nb_space++;
                    } else {
                        tok->type = SHORT_SPACE;
                        content->nb_short_space++;
                    }
                    content->nb_token++;
                    tik = (token **) realloc(content->tokenize_text, sizeof(token **) * content->nb_token);
                    if (tik == NULL) {
                        free(tok);
                        free(content->tokenize_text);
                        free(content->txt);
                        free(content);
                        return NULL;
                    }
                    tik[content->nb_token - 1] = tok;
                    content->tokenize_text = tik;
                    nb_space = 0;
                }
                break;
        }
    }

    return content;
}

void text_destroy(text *content)
{
    if (content == NULL) return;
    size_t i;
    token *tok;
    for ( i = 0; i < content->nb_token; i++) {
        tok = content->tokenize_text[i];
        if (tok != NULL) {
            if (tok->data.word != NULL) free(tok->data.word);
            free(tok);
        }
    }
    free(content->tokenize_text);
    free(content->txt);
    free(content);
    return;
}
void display_text(text *content)
{
    printf("# Pointer\n%p\n", content);
    printf("\n# Text (%u)\n%s\n", content->txt_len, content->txt);
    printf("# Tokens (%u)\n", content->nb_token);
    printf("\tNombre token WORD : %u\n", content->nb_word);
    printf("\tNombre token SHORT_SPACE : %u\n", content->nb_short_space);
    printf("\tNombre token SPACE : %u\n", content->nb_space);
    printf("\tNombre token ERASE : %u\n", content->nb_erase);
    printf("\tNombre token INSERT : %u\n", content->nb_insert);
    printf("\tNombre token REPLACE : %u\n", content->nb_replace);
    printf("\tNombre token EMPTY : %u\n", content->nb_empty);
    return;
}
