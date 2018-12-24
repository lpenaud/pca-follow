#include <gtk/gtk.h>

#include "follow.h"

GtkBuilder *builder = NULL;
GtkWidget *main_window = NULL;
follow *f = NULL;
s_node *tokens = NULL;

char * show_dialog_file(void)
{
    GtkWidget *dialog;
    gint res;
    GtkFileFilter *filter = gtk_file_filter_new();

    dialog = gtk_file_chooser_dialog_new(
        "Ouvrir...",
        GTK_WINDOW(main_window),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancel",
        GTK_RESPONSE_CANCEL,
        "_Ok",
        GTK_RESPONSE_ACCEPT,
        NULL);
    gtk_file_filter_set_name(filter, "Document Text");
    gtk_file_filter_add_mime_type(filter, "text/*");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    res = gtk_dialog_run(GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        gtk_widget_destroy(dialog);
        return filename;
    }
    return NULL;
}

void open_ref(void)
{
    char *filename;
    GtkWidget *label, *text;
    label = GTK_WIDGET(gtk_builder_get_object(builder, "LabelRef"));
    text = GTK_WIDGET(gtk_builder_get_object(builder, "TextRef"));
    filename = show_dialog_file();
    if (filename == NULL) return;
    if (f != NULL) {
        follow_destroy(f);
    }
    f = create_follow(filename);
    gtk_label_set_text(GTK_LABEL(label), filename);
    gtk_text_buffer_set_text(
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(text)),
        f->pTextRef->txt,
        f->pTextRef->txt_len
    );
    g_free(filename);
    return;
}

void open_cur(void)
{
    text *cur;
    char *filename;
    GtkWidget *label, *text;
    label = GTK_WIDGET(gtk_builder_get_object(builder, "LabelCur"));
    text = GTK_WIDGET(gtk_builder_get_object(builder, "TextCur"));
    if (f == NULL) {
        return;
    }
    if ((filename = show_dialog_file()) == NULL) return;
    if (tokens != NULL) {
        destroy_tokens(tokens);
        strhash_table_free(f->table);
    }
    cur = text_load(filename);
    tokens = plsc(f, cur);
    gtk_label_set_text(GTK_LABEL(label), filename);
    gtk_text_buffer_set_text(
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(text)),
        cur->txt,
        cur->txt_len
    );
    free(cur);
    destroy_tokens(tokens);
    g_free(filename);
    return;
}

void show_about(void)
{
    GtkWidget *about = GTK_WIDGET(gtk_builder_get_object(builder, "AboutDialog"));
    gtk_dialog_run(GTK_DIALOG(about));
    return;
}

int main (int argc, char *argv[])
{
    GError *error = NULL;
    gchar *filename = NULL;

    // Initialisation de la librairie Gtk
    gtk_init(&argc, &argv);

    // Initialise builder & contruit le chemin absolu du fichier glade
    builder = gtk_builder_new();
    filename = g_build_filename("glade/pca-follow.glade", NULL);

    // Chargement du fichier glade avec gestion d'erreur
    gtk_builder_add_from_file(builder, filename, &error);
    g_free(filename);
    if (error) {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free(error);
        return code;
    }

    // Récupération du pointeur de la fenêtre principale
    main_window = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));

    // Affectation des signals
    gtk_builder_connect_signals(builder, NULL);

    // Affichage de la fenêtre principale
    gtk_widget_show_all(main_window);

    gtk_main();

    return 0;
}
