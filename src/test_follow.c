#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#include "test.h"
#include "follow.h"

int main(int argc, char const *argv[])
{
    char str_err[BUFFER_MAX];
    follow *f;
    s_node *tokens;
    struct stat st;

    if (argc != 3) {
        sprintf(str_err, "Usage: %s fichierRef fichierCur", argv[0]);
        goto err;
    }
    if (stat(argv[1], &st) == -1) {
        sprintf(str_err, "'%s' n'est pas un fichier", argv[1]);
        goto err;
    }
    if (stat(argv[2], &st) == -1) {
        sprintf(str_err, "'%s' n'est pas un fichier", argv[2]);
        goto err;
    }
    if ((f = create_follow(argv[1])) == NULL) {
        sprintf(str_err, "Erreur lors la création de follow");
        goto err;
    }
    if ((tokens = plsc(f, argv[2])) == NULL) {
        sprintf(str_err, "Erreur lors de la fonction plsc");
        goto err;
    }
    display_tokens(tokens);
    destroy_tokens(tokens);
    follow_destroy(f);
    return 0;
err:
    fprintf(stderr, "%s\n", str_err);
    if (errno) {
        fprintf(stderr, "errno : %s\n", strerror(errno));
    }
    return -1;
}
