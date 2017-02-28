#include <console.h>
#include <vgafont.h>

extern cairo_surface_t *surf;

void draw_rect(GtkWidget *wd, gdouble x, gdouble y){
	cairo_t *cr = cairo_create(surf);
	cairo_set_source_rgb(cr, 65535, 65535, 65535);
	cairo_rectangle(cr, x, y, 1, 1);
	cairo_fill(cr);
	gtk_widget_queue_draw_area(wd, x, y, 1, 1);
}


void draw_char(GtkWidget *wd, int num){
	if(x + 8 > WIDTH){
		y += 16;
		x = 0.0;
	}
	if(y + 16 > HEIGHT)
		clear_screen();	

	gdouble tmp_x = x;
	unsigned char *symb;
	symb = vga_font_chars[num].symb;
	for(int i=0; i<16; i++){
		for(int j=0; j<8; j++){
			if((symb[i] >> j) & 1)
				draw_rect(wd, x, y);
			x++;
		}
		y++;
		x = tmp_x;
	}
	x += 8;
	y -= 16;
}
