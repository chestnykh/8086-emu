#ifndef CONSOLE_H
#define CONSOLE_H

#define WIDTH	640
#define HEIGHT	480 

#include <gtk/gtk.h>


/*current coordinates*/
gdouble x;
gdouble y;


void clear_screen();

void draw_char(GtkWidget *wd, int num);


#endif /*CONSOLE_H*/
