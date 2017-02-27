#include <gtk/gtk.h>
#include <stdbool.h>


cairo_surface_t *surface = NULL;

static void clear_surface ()
{
 	cairo_t *cr;
  	cr = cairo_create (surface);
  	cairo_set_source_rgb (cr, 0, 65000, 0);
  	cairo_paint (cr);
  	cairo_destroy (cr);
}



static gboolean configure_event_cb (GtkWidget  *widget, GdkEventConfigure *event, gpointer data)
{
	
  	if (surface)
    	cairo_surface_destroy (surface);

  	surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                               CAIRO_CONTENT_COLOR,
                                               gtk_widget_get_allocated_width (widget),
                                               gtk_widget_get_allocated_height (widget));

  /* Initialize the surface to white */
  	clear_surface ();

  /* We've handled the configure event, no need for further processing. */
  	return TRUE;
}

static gboolean
draw_cb (GtkWidget *widget,
         cairo_t   *cr,
         gpointer   data)
{
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);

  return FALSE;
}


static void
draw_brush (GtkWidget *widget,
            gdouble    x,
            gdouble    y)
{
  cairo_t *cr;

  /* Paint to the surface, where we store our state */
  cr = cairo_create (surface);

  cairo_rectangle (cr,200, 200, 100, 100);
  cairo_fill (cr);

  cairo_destroy (cr);

  /* Now invalidate the affected region of the drawing area. */
  gtk_widget_queue_draw_area (widget, 200, 200, 100, 100);
}


static gboolean kpressed(GtkWidget *wd, GdkEventKey *event)
{
	//drawing
	g_print("%c\n", event -> keyval);
	if(event -> keyval == 'c'){
		clear_surface();
		gtk_widget_queue_draw(wd);
		/*
		cairo_t *cr = cairo_create(surface);
  		cairo_set_source_surface (cr, surface, 0, 0);
  		cairo_set_source_rgb (cr, 0, 65000, 0);
  		cairo_paint (cr);
		cairo_destroy(cr);
		*/
		return TRUE;
	}
	draw_brush(wd, 0,0);
	return TRUE;
}




int main(int argc, char *argv[])
{
	//GtkWidget *frame;
	gtk_init(&argc, &argv);
	GtkWidget *i86 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *darea = gtk_drawing_area_new();
	
	gtk_window_set_title(GTK_WINDOW(i86), "Intel 8086 machine emulator");
	gtk_widget_set_size_request(i86, 800, 700);
	
	gtk_container_set_border_width (GTK_CONTAINER(i86), 10);

	GtkWidget *frame = gtk_frame_new (NULL);
 	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
  	gtk_container_add (GTK_CONTAINER (i86), frame);

  	gtk_widget_set_size_request (darea, 100, 100);
  	gtk_container_add (GTK_CONTAINER (frame), darea);

	g_signal_connect (darea,"configure-event", G_CALLBACK (configure_event_cb), NULL);
	g_signal_connect (darea, "draw", G_CALLBACK (draw_cb), NULL);
	g_signal_connect(i86,"key-release-event",G_CALLBACK(kpressed),NULL);
	gtk_widget_set_events(darea, gtk_widget_get_events(darea) | GDK_KEY_RELEASE_MASK);



	g_signal_connect_swapped(G_OBJECT(i86), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(i86);
	gtk_main();
	//gtk_main_quit();

	return 0;

}
