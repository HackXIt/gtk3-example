/* MAIN.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   May 30, 2022, 7:50:05 PM GMT+2
 * Last edited:
 *   May 31, 2022, 11:29:28 AM GMT+2
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Source for main-program-execution -> calls GUI application
 **/

/*--- COMMON LIBRARIES ---*/
#include <stdio.h>

/*--- CUSTOM LIBRARIES ---*/
// The path to the header file should be included when executing compiler, not inside source
#include "gui.h" // Automatically imports GTK for ease-of-use

/*--- MACROS ---*/

int main(int argc, char const *argv[])
{
    /* general program preparation code */
    printf("Program was started as %s with %d arguments.\n", argv[0], argc);

    /* execute gui_main() to start the graphic application */
    gui_main(argc, (char **)argv);

    /* Handle errors or do things after the GUI finished execution*/
    return 0;
}
