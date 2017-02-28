#include <gtk/gtk.h>
#include <stdbool.h>


extern void screen_init();

int main(int argc, char *argv[])
{
	GtkWidget *i86;
	GtkWidget *darea;
	GtkWidget *frame;
	//GtkWidget *frame;
	gtk_init(&argc, &argv);
	i86 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	darea = gtk_drawing_area_new();
	frame = gtk_frame_new (NULL);
	screen_init(i86, darea, frame);
	gtk_widget_show_all(i86);
	gtk_main();

	return 0;

}
