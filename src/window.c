#include <gtk/gtk.h>

int main (int argc, char *argv[])
{
    GtkWidget *main_window = NULL;
    GtkBuilder *builder = NULL;
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

    // Affectation du signal "destroy"
    g_signal_connect(G_OBJECT(main_window), "destroy", (GCallback)gtk_main_quit, NULL);

    // Affichage de la fenêtre principale
    gtk_widget_show_all(main_window);

    gtk_main();

    return 0;
}

