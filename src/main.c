#include <gtk/gtk.h>



static gboolean kpressed(GtkWidget *wd, GdkEventKey *event)
{
	g_print("%s", gdk_keyval_name(event -> keyval));
	return FALSE;
}

static void activate(GtkApplication *app, gpointer data)
{
	GtkWidget *frame;
	GtkWidget *i86 = gtk_application_window_new(app);
	GtkWidget *darea = gtk_drawing_area_new();
	gtk_window_set_title(GTK_WINDOW(i86), "Intel 8086 machine emulator");
	//gtk_widget_set_size_request(i86, 800, 700);
	/*GdkColor background_color;
	background_color.red = 0;
	background_color.green = 65000;
	background_color.blue = 0;
	gtk_widget_modify_bg(i86, GTK_STATE_NORMAL, &background_color);
	*/
	//gtk_window_set_resizable (GTK_WINDOW(i86), FALSE);
	frame = gtk_frame_new (NULL);
	gtk_frame_set_shadow_type (GTK_FRAME(frame), GTK_SHADOW_IN);
	gtk_container_add (GTK_CONTAINER (i86), frame);
	gtk_widget_set_size_request (darea, 500, 500);
	gtk_container_add (GTK_CONTAINER (frame), darea);
	g_signal_connect_swapped(G_OBJECT(i86), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	//gtk_widget_set_events(i86, GDK_KEY_RELEASE_MASK);
	//g_signal_connect(i86,"key-release-event",G_CALLBACK(kpressed),NULL);
	//g_signal_connect(i86, "key_release_event", G_CALLBACK(kpressed), NULL);
	gtk_widget_show_all(i86);
}



int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkApplication *emu;
	int status;
	emu = gtk_application_new("Emulator", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (emu, "activate", G_CALLBACK (activate), NULL);
  	status = g_application_run (G_APPLICATION(emu), argc, argv);
	gtk_main_quit();
  	//g_object_unref (emu);

	return status;

}
