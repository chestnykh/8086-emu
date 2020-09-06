#include <limits.h>
#include <console.h>


cairo_surface_t *surf = NULL;

void clear_screen (){
	cairo_t *cr;
	cr = cairo_create (surf);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_paint (cr);
	cairo_destroy (cr);

	x = 0.0;
	y = 0.0;
}

gboolean kbd_config_event (GtkWidget *wd, GdkEventConfigure *event, gpointer data){
	int width, height;
	width = gtk_widget_get_allocated_width(wd);
	height = gtk_widget_get_allocated_height(wd);

  	if (surf)
		cairo_surface_destroy (surf);

  	surf = gdk_window_create_similar_surface (gtk_widget_get_window (wd), CAIRO_CONTENT_COLOR, width, height);

  	clear_screen ();
  	return TRUE;
}

gboolean draw_on_kbd_pressed (GtkWidget *widget, cairo_t *cr, gpointer data){
	cairo_set_source_surface(cr, surf, 0, 0);
	cairo_paint(cr);
	return FALSE;
}

void kb_draw(GtkWidget *wd, gdouble x, gdouble y){
	cairo_t *cr;
	cr = cairo_create(surf);
	cairo_set_source_rgb(cr, 65535,65535, 65535);
	cairo_rectangle(cr,x,y,1,1);
	cairo_fill(cr);
	gtk_widget_queue_draw_area (wd, x, y, 1, 1);
}

void dr(GtkWidget *wd, gdouble x, gdouble y){
	unsigned char Achar[16] = {0x00, 0x00, 0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00};
	gdouble tmp_x = x;
	for(int i=0; i<16; i++){
		for(int j=0; j<8; j++){
			if((Achar[i] >> j) & 1){
				kb_draw(wd, x, y);
			}
			
			x++;
		}
		y++;
		x = tmp_x;
	}
	return;
}	



gboolean kbd_pressed(GtkWidget *wd, GdkEventKey *event){
	draw_char(wd, (int)(event -> keyval));
	gtk_widget_queue_draw(wd);
	return TRUE;
}

void screen_init(GtkWidget *mainwin, GtkWidget *darea, GtkWidget *frame){
	gtk_window_set_title(GTK_WINDOW(mainwin), "Intel 8086 machine emulator");
	gtk_widget_set_size_request(mainwin, WIDTH, HEIGHT);	
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
	gtk_container_add(GTK_CONTAINER(mainwin), frame);
	gtk_container_add(GTK_CONTAINER(frame), darea);
	gtk_widget_set_events(darea, GDK_KEY_RELEASE_MASK);
	/*signal handlers*/
	g_signal_connect_swapped(G_OBJECT(mainwin), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(mainwin, "key-release-event", G_CALLBACK(kbd_pressed), NULL);
	g_signal_connect(darea, "configure-event", G_CALLBACK(kbd_config_event), NULL);
	g_signal_connect(darea, "draw", G_CALLBACK(draw_on_kbd_pressed), NULL);

	x = 0.0;
	y = 0.0;
	return;
}
