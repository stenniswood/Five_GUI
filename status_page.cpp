#include <gtk/gtk.h>

#include "pages.hpp"

int Number_of_boards_connected = 0;

GtkWidget* status_page = NULL;
GtkWidget* limit_switches_group=NULL;
GtkWidget* currents_group=NULL;

void limit_switches_setup()
{
	limit_switches_group = gtk_grid_new();
	gtk_container_set_border_width ((GtkContainer*)limit_switches_group, 20);
	
	GtkWidget *limits_group_label = gtk_label_new(NULL);	
	gtk_label_set_markup(GTK_LABEL(limits_group_label), "<b>Limit Switches</b>");
	
	gtk_grid_set_column_homogeneous( (GtkGrid*)limit_switches_group, TRUE);	
		
	GtkWidget* v_enabled = gtk_check_button_new_with_label ("Enabled");
	GtkWidget* v_near = gtk_check_button_new_with_label ("Near");
	GtkWidget* v_far = gtk_check_button_new_with_label ("Far");
	
	GtkWidget* w_enabled = gtk_check_button_new_with_label ("Enabled");
	GtkWidget* w_near = gtk_check_button_new_with_label ("Near");
	GtkWidget* w_far = gtk_check_button_new_with_label ("Far");

	GtkWidget* x_enabled = gtk_check_button_new_with_label ("Enabled");
	GtkWidget* x_near = gtk_check_button_new_with_label ("Near");
	GtkWidget* x_far = gtk_check_button_new_with_label ("Far");

	GtkWidget* y_enabled = gtk_check_button_new_with_label ("Enabled");
	GtkWidget* y_near = gtk_check_button_new_with_label ("Near");
	GtkWidget* y_far = gtk_check_button_new_with_label ("Far");

	GtkWidget* z_enabled = gtk_check_button_new_with_label ("Enabled");
	GtkWidget* z_near = gtk_check_button_new_with_label ("Near");
	GtkWidget* z_far = gtk_check_button_new_with_label ("Far");

	gtk_grid_attach (GTK_GRID (limit_switches_group), v_enabled, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), w_enabled, 0, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), x_enabled, 0, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), y_enabled, 0, 3, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), z_enabled, 0, 4, 1, 1);
					
	gtk_grid_attach (GTK_GRID (limit_switches_group), v_near, 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), w_near, 1, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), x_near, 1, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), y_near, 1, 3, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), z_near, 1, 4, 1, 1);

	gtk_grid_attach (GTK_GRID (limit_switches_group), v_far, 2, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), w_far, 2, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), x_far, 2, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), y_far, 2, 3, 1, 1);
	gtk_grid_attach (GTK_GRID (limit_switches_group), z_far, 2, 4, 1, 1);		

}

void currents_setup()
{
	currents_group = gtk_grid_new();
	gtk_grid_set_column_homogeneous( (GtkGrid*)currents_group, TRUE);	

	GtkWidget *currents_group_label = gtk_label_new(NULL);	
	gtk_label_set_markup(GTK_LABEL(currents_group_label), "<b>Motor Currents</b>");
			
	GtkWidget *v_name = gtk_label_new(NULL);	gtk_label_set_markup(GTK_LABEL(v_name), "<b>V</b>");
	GtkWidget *v_current_label = gtk_label_new("0 Amps");

	GtkWidget *w_name = gtk_label_new(NULL);	gtk_label_set_markup(GTK_LABEL(w_name), "<b>W</b>");
	GtkWidget *w_current_label = gtk_label_new("0 Amps");

	GtkWidget *x_name = gtk_label_new(NULL);	gtk_label_set_markup(GTK_LABEL(x_name), "<b>X</b>");
	GtkWidget *x_current_label = gtk_label_new("0 Amps");

	GtkWidget *y_name = gtk_label_new(NULL);	gtk_label_set_markup(GTK_LABEL(y_name), "<b>Y</b>");
	GtkWidget *y_current_label = gtk_label_new("0 Amps");

	GtkWidget *z_name = gtk_label_new(NULL);	gtk_label_set_markup(GTK_LABEL(z_name), "<b>Z</b>");
	GtkWidget *z_current_label = gtk_label_new("0 Amps");

	gtk_grid_attach(GTK_GRID (currents_group), currents_group_label, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID (currents_group), v_name, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (currents_group), w_name, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID (currents_group), x_name, 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID (currents_group), y_name, 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID (currents_group), z_name, 0, 5, 1, 1);
	
	gtk_grid_attach(GTK_GRID (currents_group), v_current_label, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (currents_group), w_current_label, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID (currents_group), x_current_label, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID (currents_group), y_current_label, 1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID (currents_group), z_current_label, 1, 5, 1, 1);
											
}

void status_setup()
{
	status_page = gtk_grid_new();
	gtk_grid_set_column_homogeneous( (GtkGrid*)status_page, TRUE);	
	
	GdkColor color;
	color.red = 0x7fff;
	color.blue = 0x0000;
	color.green = 0x7FFF;
	gtk_widget_modify_bg(status_page, GTK_STATE_NORMAL, &color);

	limit_switches_setup();
	currents_setup();
	action_buttons_setup();

	// SETUP STATUS OVER-ALL PAGE:
	gtk_grid_attach (GTK_GRID (status_page), limit_switches_group, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (status_page), currents_group, 	   1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (status_page), action_items, 0, 2, 3, 1);
}


