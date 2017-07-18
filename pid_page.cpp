#include <gtk/gtk.h>
#include <string.h>
#include "drive_five.h"

#include "sequencer_page.hpp"
#include "bk_actionbar.hpp"


GtkWidget *pid_sliders=NULL;
GtkWidget *pid_constants=NULL;

GtkWidget* v_pid = NULL;
GtkWidget* w_pid = NULL;
GtkWidget* x_pid = NULL;
GtkWidget* y_pid = NULL;
GtkWidget* z_pid = NULL;
GtkWidget* pid_page=NULL;


void cb_pid_change( GtkWidget *range, gpointer  user_data )
{
	char cmd[128];
	float pids[5];
	pids[0] = gtk_range_get_value((GtkRange*)v_pid);
	pids[1] = gtk_range_get_value((GtkRange*)w_pid);
	pids[2] = gtk_range_get_value((GtkRange*)x_pid);
	pids[3] = gtk_range_get_value((GtkRange*)y_pid);
	pids[4] = gtk_range_get_value((GtkRange*)z_pid);
	sprintf ( cmd, "pid v%6.1f w%6.1f x%6.1f y%6.1f z%6.1f", pids[0], pids[1], pids[2], pids[3], pids[4] );	
	strcpy  ( last_operation, cmd );
	printf  ( "%s\n", cmd );
	char* device_name = gtk_combo_box_text_get_active_text((GtkComboBoxText*)five_stack);	
	if (IsActive) {
		int selected_board = find_board( device_name );
		fives[selected_board].send_command( cmd );
	}
}


void pid_sliders_setup()
{
	pid_sliders = gtk_grid_new();
	GtkWidget *pid_slid_label = gtk_label_new("Position");

	GtkWidget *v_label = gtk_label_new(NULL);		gtk_label_set_markup(GTK_LABEL(v_label), "<b>V</b>");
	GtkWidget *w_label = gtk_label_new(NULL);		gtk_label_set_markup(GTK_LABEL(w_label), "<b>W</b>");
	GtkWidget *x_label = gtk_label_new(NULL);		gtk_label_set_markup(GTK_LABEL(x_label), "<b>X</b>");
	GtkWidget *y_label = gtk_label_new(NULL);		gtk_label_set_markup(GTK_LABEL(y_label), "<b>Y</b>");
	GtkWidget *z_label = gtk_label_new(NULL);		gtk_label_set_markup(GTK_LABEL(z_label), "<b>Z</b>");
	
	v_pid = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 4000000000.0, 1.0 );
	w_pid = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 4000000000.0, 1.0 );
	x_pid = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 4000000000.0, 1.0 );
	y_pid = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 4000000000.0, 1.0 );
	z_pid = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 4000000000.0, 1.0 );
	gtk_widget_set_hexpand (v_pid, TRUE);	

	g_signal_connect ( v_pid, "value-changed", (GCallback)cb_pid_change, NULL);
	g_signal_connect ( w_pid, "value-changed", (GCallback)cb_pid_change, NULL);
	g_signal_connect ( x_pid, "value-changed", (GCallback)cb_pid_change, NULL);
	g_signal_connect ( y_pid, "value-changed", (GCallback)cb_pid_change, NULL);
	g_signal_connect ( z_pid, "value-changed", (GCallback)cb_pid_change, NULL);

	gtk_grid_attach (GTK_GRID (pid_sliders), pid_slid_label, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_sliders), v_label, 0, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_sliders), w_label, 0, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_sliders), x_label, 0, 3, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_sliders), y_label, 0, 4, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_sliders), z_label, 0, 5, 1, 1);

	gtk_grid_attach (GTK_GRID (pid_sliders), v_pid, 1, 1, 3, 1);
	gtk_grid_attach (GTK_GRID (pid_sliders), w_pid, 1, 2, 3, 1);
	gtk_grid_attach (GTK_GRID (pid_sliders), x_pid, 1, 3, 3, 1);
	gtk_grid_attach (GTK_GRID (pid_sliders), y_pid, 1, 4, 3, 1);
	gtk_grid_attach (GTK_GRID (pid_sliders), z_pid, 1, 5, 3, 1);
}

GtkWidget *Kp_v  = NULL;
GtkWidget *Ki_v  = NULL; 
GtkWidget *Kd_v  = NULL;			
GtkWidget *Kp_w  = NULL;
GtkWidget *Ki_w  = NULL;
GtkWidget *Kd_w  = NULL;
GtkWidget *Kp_x  = NULL;
GtkWidget *Ki_x  = NULL;
GtkWidget *Kd_x  = NULL;

GtkWidget *Kp_y  = NULL;
GtkWidget *Ki_y  = NULL;
GtkWidget *Kd_y  = NULL;
GtkWidget *Kp_z  = NULL;
GtkWidget *Ki_z  = NULL;
GtkWidget *Kd_z  = NULL;

void pid_constant_set_values()
{
	// Need to fill with Real Values from "read Kp"
	gtk_spin_button_set_value( (GtkSpinButton*)Kp_v, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Ki_v, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Kd_v, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Kp_w, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Ki_w, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Kd_w, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Kp_x, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Ki_x, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Kd_x, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Kp_y, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Ki_y, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Kd_y, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Kp_z, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Ki_z, 0.001 );
	gtk_spin_button_set_value( (GtkSpinButton*)Kd_z, 0.001 );
}

void pid_constants_setup()
{
	pid_constants = gtk_grid_new();	

	GtkWidget *Kp_label = gtk_label_new(NULL);	
	gtk_label_set_markup(GTK_LABEL(Kp_label), "<b>Kp</b>");
	GtkWidget *Ki_label = gtk_label_new(NULL);	
	gtk_label_set_markup(GTK_LABEL(Kp_label), "<b>Ki</b>");
	GtkWidget *Kd_label = gtk_label_new(NULL);	
	gtk_label_set_markup(GTK_LABEL(Kp_label), "<b>Kd</b>");

	GtkWidget *V_label = gtk_label_new(NULL);	
	gtk_label_set_markup(GTK_LABEL(V_label), "<b>V</b>");
	GtkWidget *W_label = gtk_label_new(NULL);	
	gtk_label_set_markup(GTK_LABEL(W_label), "<b>W</b>");
	GtkWidget *X_label = gtk_label_new(NULL);	
	gtk_label_set_markup(GTK_LABEL(X_label), "<b>X</b>");
	GtkWidget *Y_label = gtk_label_new(NULL);	
	gtk_label_set_markup(GTK_LABEL(Y_label), "<b>Y</b>");
	GtkWidget *Z_label = gtk_label_new(NULL);	
	gtk_label_set_markup(GTK_LABEL(Z_label), "<b>Z</b>");

	Kp_v = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);	
	Ki_v = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);	
	Kd_v = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);

	Kp_w = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);	
	Ki_w = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);	
	Kd_w = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);

	Kp_x = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);	
	Ki_x = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);	
	Kd_x = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);

	Kp_y = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);	
	Ki_y = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);	
	Kd_y = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);

	Kp_z = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);	
	Ki_z = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);	
	Kd_z = gtk_spin_button_new_with_range(0.0, 10.0, 0.00001);

	pid_constant_set_values();
	
	gtk_grid_attach (GTK_GRID (pid_constants), Kp_v, 1, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Ki_v, 2, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Kd_v, 3, 1, 1, 1);			
	gtk_grid_attach (GTK_GRID (pid_constants), Kp_w, 1, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Ki_w, 2, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Kd_w, 3, 2, 1, 1);			
	gtk_grid_attach (GTK_GRID (pid_constants), Kp_x, 1, 3, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Ki_x, 2, 3, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Kd_x, 3, 3, 1, 1);			
	gtk_grid_attach (GTK_GRID (pid_constants), Kp_y, 1, 4, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Ki_y, 2, 4, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Kd_y, 3, 4, 1, 1);			
	gtk_grid_attach (GTK_GRID (pid_constants), Kp_z, 1, 5, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Ki_z, 2, 5, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Kd_z, 3, 5, 1, 1);

	gtk_grid_attach (GTK_GRID (pid_constants), Kp_label, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Ki_label, 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Kd_label, 2, 0, 1, 1);
	
	gtk_grid_attach (GTK_GRID (pid_constants), V_label, 0, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), W_label, 0, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), X_label, 0, 3, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Y_label, 0, 4, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_constants), Z_label, 0, 5, 1, 1);
	
}

void pid_setup()
{
	pid_page = gtk_grid_new();
	gtk_grid_set_column_homogeneous( (GtkGrid*)pid_page, TRUE);	
	
	GdkColor color;
	color.red = 0x0000;
	color.blue = 0x5FFF;
	color.green = 0x5FFF;
	gtk_widget_modify_bg(pid_page, GTK_STATE_NORMAL, &color);

	pid_sliders_setup();
	pid_constants_setup();
	action_buttons_setup();
	
	gtk_grid_attach (GTK_GRID (pid_page), pid_sliders,  0, 0, 1, 1 );
	gtk_grid_attach (GTK_GRID (pid_page), action_items, 0, 1, 1, 1 );
	gtk_grid_attach (GTK_GRID (pid_page), pid_constants, 0, 2, 1, 1);
}
