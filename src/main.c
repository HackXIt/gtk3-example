/* MAIN.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   May 30, 2022, 7:50:05 PM GMT+2
 * Last edited:
 *   May 31, 2022, 8:09:21 AM GMT+2
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Source for main-program-execution -> calls GUI application
 **/

/*--- COMMON LIBRARIES ---*/

/*--- CUSTOM LIBRARIES ---*/
#include "inc/gui.h" // Automatically imports GTK for ease-of-use

/*--- MACROS ---*/

int main(int argc, char const *argv[])
{
    /* general program preparation code */

    /* execute gui_main() to start the graphic application */
    gui_main(argc, argv);

    /* Handle errors or do things after the GUI finished execution*/
    return 0;
}
