#include <gtk/gtk.h>

#include "about_page.hpp"


GtkWidget *bk_image=NULL;
cairo_surface_t* mk_image=NULL;


gboolean about_window_draw_cb (GtkWidget * widget, cairo_t * cr, cairo_surface_t* m_bgImage)
{
    gint root_width,root_height;

	cairo_set_source_surface (cr,m_bgImage, 0, 0);

	gtk_window_get_size (GTK_WINDOW(widget), &root_width, &root_height);
	cairo_rectangle (cr, 0, 0,root_width, root_height);
	cairo_fill (cr);

	//Enable Below code to draw child widget after background rendering
	//gtk_widget_draw (childwidget, cr);
	//cairo_fill (cr);
    return TRUE;
}

GtkWidget* about_page = NULL;

void about_setup()
{
//    bk_image = gtk_image_new_from_file ("bk_bridge_title.png");

	about_page = gtk_grid_new();
	gtk_grid_set_column_homogeneous( (GtkGrid*)about_page, TRUE);	
	    
	mk_image = cairo_image_surface_create_from_png("bk_bridge_title.png");
	g_signal_connect (G_OBJECT (about_page), "draw", G_CALLBACK(about_window_draw_cb), mk_image);
	
	gtk_grid_attach (GTK_GRID (about_page), (GtkWidget*)mk_image, 0, 0, 1, 1);
}

