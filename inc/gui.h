/* GUI.h
 *   by Nikolaus Rieder
 *
 * Created:
 *   May 30, 2022, 7:52:51 PM GMT+2
 * Last edited:
 *   May 31, 2022, 9:30:20 AM GMT+2
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Header-File for GUI application library
**/

#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

void on_button1_clicked(GtkButton *b);
int gui_main(int argc, char **argv);

#endif