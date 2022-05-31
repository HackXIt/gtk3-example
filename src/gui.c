/* GUI.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   May 30, 2022, 7:52:04 PM GMT+2
 * Last edited:
 *   May 31, 2022, 1:22:43 PM GMT+2
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Source file for functions handling GUI application
 **/

/*--- COMMON LIBRARIES ---*/
#include <stdio.h>
#include <stdlib.h>

/*--- CUSTOM LIBRARIES ---*/
// The path to the header file should be included when executing compiler, not inside source
#include "gui.h"

/*--- MACROS ---*/
#define USE_GLADE

/*--- Global GTK variables ---*/
// (not always recommended, but used here for sake of simplicity)
GtkWidget *window;
// GtkWindow *window;
GtkWidget *fixed1;
GtkWidget *button1;
GtkWidget *label1;
GtkWidget *dialog1;
GtkWidget *dialog_entry;
GtkWidget *dialog_label;
GtkWidget *dialog_button1;
GtkWidget *dialog_button2;
#ifdef USE_GLADE
GtkBuilder *builder;
#endif

void on_button1_clicked(GtkButton *b)
{
    gtk_label_set_text(GTK_LABEL(label1), (const gchar *)"Hello World");
    gtk_widget_show(dialog1);
}

void on_dialog_save(GtkButton *b, gpointer data)
{
    GtkEntry *entry = GTK_ENTRY(data);
    gtk_label_set_text(GTK_LABEL(dialog_label), gtk_entry_get_text(entry));
}

void on_dialog_write(GtkEntry *entry)
{
    gtk_label_set_text(GTK_LABEL(dialog_label), gtk_entry_get_text(entry));
}

// GTK also requires argc & argv
int gui_main(int argc, char **argv)
{
    // This is a seperate main, which exclusively is used for the GUI
    // If any CLI stuff or generic setup outside of the GUI needs to be done, do it in main.c

    /* GTK initialization */
    gtk_init(&argc, &argv);

/* Section, which uses Glade for the GUI */
#ifdef USE_GLADE // If macro USE_GLADE is defined, then...
    g_print("Using Glade for the GUI...\n");
    builder = gtk_builder_new_from_file("glade-example.glade");           // Get Glade-XML from file
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));       // Get main window container
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // Connect close-button of window with internal quit-callback

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);
    label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    dialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog1"));
    dialog_entry = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_entry"));
    g_signal_connect(dialog_entry, "changed", G_CALLBACK(on_dialog_write), NULL);
    dialog_label = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_label"));
    dialog_button1 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_button1"));
    g_signal_connect(dialog_button1, "clicked", G_CALLBACK(on_dialog_save), dialog_entry);
    dialog_button2 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_button2"));

    gtk_widget_show_all(window); // GTK_WIDGET(window)
#endif
/* END OF GLADE SECTION */

/* Section, which uses pure GTK for the GUI */
#ifndef USE_GLADE // If macro USE_GLADE is not defined, then...
    g_print("Using pure GTK for the GUI...\n");
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "GTK3 Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    fixed1 = gtk_fixed_new();
    // GTK_PACK_START()
    label1 = gtk_label_new("");
    button1 = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(button1), "Greeting");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // Connect close-button of window with internal quit-callback
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);

    gtk_fixed_put(GTK_FIXED(fixed1), button1, 50, 100);
    gtk_fixed_put(GTK_FIXED(fixed1), label1, 200, 100);

    gtk_widget_show_all(window);
#endif
    /* END OF PURE GTK SECTION */

    gtk_main();
    g_print("The main GUI loop has been terminated.\n");
    return EXIT_SUCCESS;
}
