#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hachage.h"
#include "text.h"

token * add_token(text *txt, int index, int len, enum token_type type)
{
    token **tik, *tok;
    int i;

    if ((tok = (token *) malloc(sizeof(token))) == NULL) return NULL;
    tok->textOffset = index - len;
    switch (tok->type = type) {
        case WORD:
            tok->data.word = (char *) malloc(sizeof(char) * (len + 1));
            if (tok->data.word == NULL) {
                free(tok);
                return NULL;
            }
            for (i = 0; i < len; i++) {
                tok->data.word[i] = txt->txt[tok->textOffset + i];
            }
            tok->data.word[i] = '\0';
            txt->nb_word++;
            break;
        case SHORT_SPACE:
            for (i = 0; i < len; i++) {
                tok->data.space[i] = txt->txt[tok->textOffset + i];
            }
            tok->data.space[i] = '\0';
            txt->nb_short_space++;
            break;
        case SPACE:
            for (i = 0; i < (SPACE_MAX - 1); i++) {
                tok->data.space[i] = txt->txt[tok->textOffset + i];
            }
            tok->data.space[i] = '\0';
            txt->nb_space++;
            break;
        case ERASE:
            txt->nb_erase++;
            break;
        case INSERT:
            txt->nb_insert++;
            break;
        case REPLACE:
            txt->nb_replace++;
            break;
        case EMPTY:
            txt->nb_empty++;
            break;
    }

    tik = (token **) realloc(txt->tokenize_text, sizeof(token *) * (++txt->nb_token));
    if (tik == NULL) {
        free(tok);
        return NULL;
    }
    tik[txt->nb_token - 1] = tok;
    txt->tokenize_text = tik;
    return tok;
}

char * read_file(const char *filename)
{
    FILE *fp;
    char *data, buf[BUFFER_MAX + 1];

    if ((fp = fopen(filename, "r")) == NULL) return NULL;
    fseek(fp, 0L, SEEK_END);
    if ((data = (char *) malloc(sizeof(char) * (ftell(fp) + 1))) == NULL) {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    data[0] = '\0';
    while (fgets(buf, BUFFER_MAX, fp) != NULL) strcat(data, buf);
    fclose(fp);
    return data;
}

text * text_load(const char *filename)
{
    size_t i, nb_space, nb_car;
    text *content;

    if ((content = (text *) malloc(sizeof(text))) == NULL) return NULL;
    if ((content->txt = read_file(filename)) == NULL) {
        free(content);
        return NULL;
    }

    if ((content->tokenize_text = (token **) malloc(sizeof(token *))) == NULL) {
        free(content->txt);
        free(content);
    }

    content->txt_len =
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
    for (i = 0; content->txt[i]; i++) {
        content->txt_len++;
        switch (content->txt[i]) {
            case ' ':
            case '\n':
            case '\t':
                nb_space++;
                if (nb_car > 0) {
                    if (add_token(content, i, nb_car, WORD) == NULL) {
                        free(content->tokenize_text);
                        free(content->txt);
                        free(content);
                        return NULL;
                    }
                    nb_car = 0;
                }
                break;
            default:
                nb_car++;
                if (nb_space > 0) {
                    if (add_token(content, i, nb_space, nb_space > SPACE_MAX ? SPACE : SHORT_SPACE) == NULL) {
                        free(content->tokenize_text);
                        free(content->txt);
                        free(content);
                        return NULL;
                    }
                    nb_space = 0;
                }
        }
    }
    return content;
}

void text_destroy(text *content)
{
    if (content == NULL) return;
    unsigned int i;
    for (i = 0; i < content->nb_token; i++) {
        if (content->tokenize_text[i]->type == WORD
            && content->tokenize_text[i]->data.word != NULL) {
            free(content->tokenize_text[i]->data.word);
        }
        free(content->tokenize_text[i]);
    }
    free(content->tokenize_text);
    free(content->txt);
    free(content);
    return;
}

void display_text(text *content)
{
    printf("# Text (%p)\n", content);
    printf("\n## Content (%u)\n%s\n", content->txt_len, content->txt);
    printf("## Tokens (%u)\n", content->nb_token);
    printf("\tNombre token WORD : %u\n", content->nb_word);
    printf("\tNombre token SHORT_SPACE : %u\n", content->nb_short_space);
    printf("\tNombre token SPACE : %u\n", content->nb_space);
    printf("\tNombre token ERASE : %u\n", content->nb_erase);
    printf("\tNombre token INSERT : %u\n", content->nb_insert);
    printf("\tNombre token REPLACE : %u\n", content->nb_replace);
    printf("\tNombre token EMPTY : %u\n", content->nb_empty);
    return;
}
