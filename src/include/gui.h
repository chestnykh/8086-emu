#include <gtk/gtk.h>

gboolean kb_config_event (GtkWidget *wd, GdkEventConfigure *event, gpointer data);

gboolean draw_on_kb_pressed (GtkWidget *widget, cairo_t *cr, gpointer data);

gboolean kb_pressed(GtkWidget *wd, GdkEventKey *event);

void screen_init();
