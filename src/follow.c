#include "follow.h"

int ** plsc(text *ref, text *cur)
{
    int **log = (int **) malloc((ref->nb_word+2) * sizeof(int)), i, j, y_token, x_token;
    for(i = 0; i < ref->nb_word + 1; i++)
        lg[i] = (int *) malloc((cur->nb_word + 1) * sizeof(int));
    
    i = j = 1;
    for(y_token = 0; y_token < ref->nb_token; y_token++) {
        if(i > ref->nb_word) break;

        if(ref->table[y_token]->type != WORD) continue;

        for(x_token = 0; x_token < cur->nb_token; x_token++) {
            if (j > cur->nb_word) break;
            if (ref->) continue;
            
        }
    }

}
