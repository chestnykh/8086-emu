#include <gtk/gtk.h>
#include <stdbool.h>

#include <gui.h>











int main(int argc, char *argv[])
{
	//GtkWidget *frame;
	gtk_init(&argc, &argv);
	GtkWidget *i86 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *darea = gtk_drawing_area_new();
	
	gtk_window_set_title(GTK_WINDOW(i86), "Intel 8086 machine emulator");
	gtk_widget_set_size_request(i86, 640, 480);
	

	GtkWidget *frame = gtk_frame_new (NULL);
 	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
  	gtk_container_add (GTK_CONTAINER (i86), frame);

  	//gtk_widget_set_size_request (darea, 100, 100);
  	gtk_container_add (GTK_CONTAINER(frame), darea);

	g_signal_connect (darea,"configure-event", G_CALLBACK (kb_config_event), NULL);
	g_signal_connect (darea, "draw", G_CALLBACK (draw_on_kb_pressed), NULL);
	g_signal_connect(i86,"key-release-event",G_CALLBACK(kb_pressed),NULL);
	gtk_widget_set_events(darea, GDK_KEY_RELEASE_MASK);



	g_signal_connect_swapped(G_OBJECT(i86), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(i86);
	gtk_main();
	//gtk_main_quit();

	return 0;

}
