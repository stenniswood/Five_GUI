#include <gtk/gtk.h>

#include "sequencer_page.hpp"
#include "bk_actionbar.hpp"


GtkWidget* v_pid = NULL;
GtkWidget* w_pid = NULL;
GtkWidget* x_pid = NULL;
GtkWidget* y_pid = NULL;
GtkWidget* z_pid = NULL;
GtkWidget* pid_page=NULL;


void cb_pid_add_to_sequencer( GtkWidget *range, gpointer  user_data )
{
	char cmd[128];
	float pids[5];
	pids[0] = gtk_range_get_value((GtkRange*)v_pid);
	pids[1] = gtk_range_get_value((GtkRange*)w_pid);
	pids[2] = gtk_range_get_value((GtkRange*)x_pid);
	pids[3] = gtk_range_get_value((GtkRange*)y_pid);
	pids[4] = gtk_range_get_value((GtkRange*)z_pid);
	sprintf(cmd, "pid v%6.1f w%6.1f x%6.1f y%6.1f z%6.1f", pids[0], pids[1], pids[2], pids[3], pids[4] );	
	printf( "%s\n", cmd );
	char* device_name = gtk_combo_box_text_get_active_text((GtkComboBoxText*)five_stack);	
	sequencer_add_entry(device_name, cmd, "reply ignored");
}
GtkWidget *pid_sliders=NULL;

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
	action_buttons_setup();
		
//	gtk_widget_set_hexpand (v_pid, TRUE);
//	gtk_widget_set_vexpand (pid_page, TRUE);

	gtk_grid_attach (GTK_GRID (pid_page), pid_sliders, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (pid_page), action_items, 0, 1, 1, 1);

}
