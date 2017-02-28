#include <gtk/gtk.h>


cairo_surface_t *surf = NULL;

void clear_screen (){
	cairo_t *cr;
	cr = cairo_create (surf);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_paint (cr);
	cairo_destroy (cr);
}

gboolean kb_config_event (GtkWidget *wd, GdkEventConfigure *event, gpointer data){
	int width, height;
	width = gtk_widget_get_allocated_width(wd);
	height = gtk_widget_get_allocated_height(wd);

  	if (surf)
		cairo_surface_destroy (surf);

  	surf = gdk_window_create_similar_surface (gtk_widget_get_window (wd), CAIRO_CONTENT_COLOR, width, height);

  	clear_screen ();
  	return TRUE;
}

gboolean draw_on_kb_pressed (GtkWidget *widget, cairo_t *cr, gpointer data){
	cairo_set_source_surface (cr, surf, 0, 0);
	cairo_paint (cr);
	return FALSE;
}

void kb_draw(GtkWidget *wd, gdouble x, gdouble y){
	cairo_t *cr;
	cr = cairo_create(surf);
	cairo_set_source_rgb(cr, 65535,65535, 65535);
	cairo_rectangle (cr,200, 200, 100, 100);
	cairo_fill(cr);
	/*cairo_destroy(cr);*/
	gtk_widget_queue_draw_area (wd, 200, 200, 100, 100);
}

gboolean kb_pressed(GtkWidget *wd, GdkEventKey *event){
	if(event -> keyval == 'c'){
		clear_screen();
		gtk_widget_queue_draw(wd);
		return TRUE;
	}
	kb_draw(wd, 0,0);
	return TRUE;
}

