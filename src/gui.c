/* GUI.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   May 30, 2022, 7:52:04 PM GMT+2
 * Last edited:
 *   June 6, 2022, 11:04:06 AM GMT+2
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
#define USE_RESOURCE
#define PIC_X 3
#define PIC_Y 3

/*--- Global GTK variables ---*/
// (not always recommended, but used here for sake of simplicity)
GtkWidget *window;
// GtkWindow *window;
GtkWidget *fixed1;
// GtkWidget *image_grid;
GtkWidget *button1;
GtkWidget *label1;
GtkWidget *dialog1;
GtkWidget *dialog_entry;
GtkWidget *dialog_label;
GtkWidget *dialog_button1;
GtkWidget *dialog_button2;
GdkPixbuf *icon;
GdkPixbuf *chair_64;
GdkPixbuf *chair_128;
GtkWidget *image1;
GtkWidget *pic_array[PIC_X][PIC_Y];
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
#ifndef USE_RESOURCE
    builder = gtk_builder_new_from_file("glade-example.glade"); // Get Glade-XML from file
#endif
#ifdef USE_RESOURCE
    builder = gtk_builder_new_from_resource("/builder/glade-example.glade"); // Get Glade-XML from compiled resource
#endif
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
    image1 = GTK_WIDGET(gtk_builder_get_object(builder, "image1"));

    for (int i = 0; i < PIC_X; i++)
    {
        for (int j = 0; j < PIC_Y; j++)
        {
            char buf[8];
            sprintf(buf, "pic_%d_%d", i, j); // UNSAFE
            pic_array[i][j] = GTK_WIDGET(gtk_builder_get_object(builder, buf));
            g_print(buf);
        }
    }

// Get GdkPixbufs from file
#ifndef USE_RESOURCE
    icon = gdk_pixbuf_new_from_file("icon.png", NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image1), icon);
#endif

// Get GdkPixbufs from compiled resource
#ifdef USE_RESOURCE
    chair_64 = gdk_pixbuf_new_from_resource("/images/chair_64px.png", NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image1), chair_64);

    for (int i = 0; i < PIC_X; i++)
    {
        for (int j = 0; j < PIC_Y; j++)
        {
            gtk_image_set_from_pixbuf(GTK_IMAGE(pic_array[i][j]), chair_64);
            // pic_array[i][j] => GTK_Image an Stelle (X,Y) des Grids
        }
    }
    // set_image_at_position(x,y, pixbuf);
    // pic_array[x][y] => gtk_image_set_from_pixbuf()

    /*
PixBuf pic1;
PixBufpic2;
PixBuf pic3;

( ( (CELL_STATE, GtkWidget) ), ( () ), ( () ), )
(CELL_STATE, GtkWidget )
=> gridTable[0][0] = (CELL_STATE, GtkWidget) ... Tuple im Grid
=> gridTable[0][0] = struct cell {UNBELEGT, cell_0_0} ... übersetzt in Code (ca.)
struct targetCell = gridTable[0][0]
int x = &targetCell[0]
GtkWidgety = targetCell[1]

(x++) ... Zellenwert um 1 erhöhen
(x = x%3) ... Modulo 3 damit wir in Range 0-2 bleiben
((x++)%3, cell_0_0)

Empfehlung => switch() case
Abfrage, welches Bild gesetzt werden soll, anhand des aktuellen Zellenwerts = x
if(x == UNBELEGT) => gtk_image_set_pixBuf(cell_0_0, pic1)
if(x == FREI) => gtk_image_set_pixBuf(cell_0_0, pic2)
if(x == BELEGT) => gtk_image_set_pixBuf(cell_0_0, pic3)
    */
#endif

    gtk_widget_show_all(window); // GTK_WIDGET(window)
#endif
/* END OF GLADE SECTION */

/* Section, which uses pure GTK for the GUI */
#ifndef USE_GLADE // If macro USE_GLADE is not defined, then...
    g_print("Using pure GTK for the GUI...\n");
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
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
