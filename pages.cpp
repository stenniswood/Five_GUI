#include <gtk/gtk.h>
#include "drive_five.h"
#include "sequencer_page.hpp"
#include "bk_actionbar.hpp"
#include <string.h>


extern DriveFive five;
extern GtkWidget *bk_image;
float pwms[5];
GtkWidget* v_pwm;
GtkWidget* w_pwm;
GtkWidget* x_pwm;
GtkWidget* y_pwm;
GtkWidget* z_pwm;
GtkWidget*  use_encoders=NULL;
GtkWidget*  use_pots=NULL;
GtkWidget*  pwm_page=NULL;

GtkWidget * source_encoder_pot=NULL;
GtkWidget*  slider_grid=NULL;


/******************** CALLBACK FUNCTIONS *******************************/
// Puts it in the pointer :
void compose_pwm_command(char* mCommand)
{
	sprintf(mCommand, "pwm v%1.3f w%1.3f x%1.3f y%1.3f z%1.3f", pwms[0], pwms[1], pwms[2], pwms[3], pwms[4] );	
	strcpy(last_operation, mCommand);		// Store for later sequencing/sending.
	printf( "%s\n", mCommand );
}


/* Callback function for any change to any PWM slider. */
void cb_pwm_change(GtkWidget *range, gpointer  user_data)
{
	char cmd[128];	
	printf("cb_pwm_change()  active=%d\n", IsActive );
	// Fill these in anyway, even if not Active - so we can 'compose' the sequencer commands.
	pwms[0] = gtk_range_get_value((GtkRange*)v_pwm)/100.0;
	pwms[1] = gtk_range_get_value((GtkRange*)w_pwm)/100.0;	
	pwms[2] = gtk_range_get_value((GtkRange*)x_pwm)/100.0;	
	pwms[3] = gtk_range_get_value((GtkRange*)y_pwm)/100.0;	
	pwms[4] = gtk_range_get_value((GtkRange*)z_pwm)/100.0;
	if (IsActive) 
	{
		compose_pwm_command( cmd );
		five.send_command  ( cmd );
	}
	else printf("not active!\n");
}


/* Callback function for a change in the radio buttons: use_encoders/pots */
void change_use_encoder_pots (GtkButton *button, gpointer   user_data)
{
	char msg[50];
	bool enc = gtk_toggle_button_get_active ((GtkToggleButton*)button);
	if (enc)
		sprintf(msg, "use encoder %c", *(char*)user_data );
	else 
		sprintf(msg, "use potentiometer %c", *(char*)user_data );
	printf("%s\n", msg);
	five.send_command( msg );
}

/******************** SETUP CONTROL FUNCTIONS *******************************/
void sliders_setup()
{
	slider_grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous( (GtkGrid*)slider_grid, TRUE);	
	
	v_pwm = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, -100.0, 100.0, 1.0 );
	w_pwm = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, -100.0, 100.0, 1.0 );
	x_pwm = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, -100.0, 100.0, 1.0 );
	y_pwm = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, -100.0, 100.0, 1.0 );
	z_pwm = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, -100.0, 100.0, 1.0 );
	gtk_widget_set_vexpand (v_pwm, TRUE);

	gtk_range_set_value( (GtkRange*)v_pwm, 0.00 );
	gtk_range_set_value( (GtkRange*)w_pwm, 0.00 );
	gtk_range_set_value( (GtkRange*)x_pwm, 0.00 );
	gtk_range_set_value( (GtkRange*)y_pwm, 0.00 );
	gtk_range_set_value( (GtkRange*)z_pwm, 0.00 );
	
	gtk_scale_set_draw_value( (GtkScale*)v_pwm, TRUE );
	gtk_scale_set_has_origin ((GtkScale*)v_pwm, TRUE);
	gtk_scale_set_has_origin ((GtkScale*)w_pwm, TRUE);
	gtk_scale_set_has_origin ((GtkScale*)x_pwm, TRUE);

	g_signal_connect ( v_pwm, "value-changed", (GCallback)cb_pwm_change, NULL);
	g_signal_connect ( w_pwm, "value-changed", (GCallback)cb_pwm_change, NULL);
	g_signal_connect ( x_pwm, "value-changed", (GCallback)cb_pwm_change, NULL);
	g_signal_connect ( y_pwm, "value-changed", (GCallback)cb_pwm_change, NULL);
	g_signal_connect ( z_pwm, "value-changed", (GCallback)cb_pwm_change, NULL);
			
	/*GdkRGBA color;
	color.red = 0xffff;
	color.blue = 0xFFFF;
	color.green = 0xFFFF;
	gtk_widget_override_background_color( v_pwm, GTK_STATE_FLAG_NORMAL, &color);	*/							
	
	gtk_grid_attach (GTK_GRID (slider_grid), v_pwm, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (slider_grid), w_pwm, 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (slider_grid), x_pwm, 2, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (slider_grid), y_pwm, 3, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (slider_grid), z_pwm, 4, 0, 1, 1);			
}


void encoder_selection_setup()
{
	source_encoder_pot = gtk_grid_new();
	gtk_grid_set_column_homogeneous( (GtkGrid*)source_encoder_pot, TRUE);	
		
	GtkWidget *use_encoders = gtk_label_new ("Use Encoder:");
	GtkWidget *use_pots     = gtk_label_new ("Use Potentiometer:");

	GtkWidget* v_e_fb = gtk_radio_button_new_with_label(NULL,"V");		// feedback
	GtkWidget* v_p_fb = gtk_radio_button_new_with_label(NULL,"V");		// feedback
	
	GtkWidget* w_e_fb = gtk_radio_button_new_with_label(NULL,"W");		// feedback
	GtkWidget* w_p_fb = gtk_radio_button_new_with_label(NULL,"W");		// feedback
	
	GtkWidget* x_e_fb = gtk_radio_button_new_with_label(NULL,"X");		// feedback
	GtkWidget* x_p_fb = gtk_radio_button_new_with_label(NULL,"X");		// feedback
	
	GtkWidget* y_e_fb = gtk_radio_button_new_with_label(NULL,"Y");		// feedback
	GtkWidget* y_p_fb = gtk_radio_button_new_with_label(NULL,"Y");		// feedback

	GtkWidget* z_e_fb = gtk_radio_button_new_with_label(NULL,"Z");		// feedback
	GtkWidget* z_p_fb = gtk_radio_button_new_with_label(NULL,"Z");		// feedback

	 
	GSList* use_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (use_encoders));	
	gtk_radio_button_join_group ((GtkRadioButton*)use_pots, (GtkRadioButton*)use_encoders);	

	char vs[]="v";	char ws[]="w";	char xs[]="x";	char ys[]="y";	char zs[]="z";
	
	g_signal_connect ( v_e_fb, "clicked", (GCallback)change_use_encoder_pots, vs);
	g_signal_connect ( v_p_fb, "clicked", (GCallback)change_use_encoder_pots, vs);
	g_signal_connect ( w_e_fb, "clicked", (GCallback)change_use_encoder_pots, ws);
	g_signal_connect ( w_p_fb, "clicked", (GCallback)change_use_encoder_pots, ws);
	g_signal_connect ( x_e_fb, "clicked", (GCallback)change_use_encoder_pots, xs);
	g_signal_connect ( x_p_fb, "clicked", (GCallback)change_use_encoder_pots, xs);
	g_signal_connect ( y_e_fb, "clicked", (GCallback)change_use_encoder_pots, ys);
	g_signal_connect ( y_p_fb, "clicked", (GCallback)change_use_encoder_pots, ys);
	g_signal_connect ( z_e_fb, "clicked", (GCallback)change_use_encoder_pots, zs);
	g_signal_connect ( z_p_fb, "clicked", (GCallback)change_use_encoder_pots, zs);

	
	gtk_grid_attach (GTK_GRID (source_encoder_pot), use_encoders, 0, 0, 1, 1);	
	gtk_grid_attach (GTK_GRID (source_encoder_pot), use_pots, 0, 1, 1, 1);	
	
	gtk_grid_attach (GTK_GRID (source_encoder_pot), v_e_fb, 1, 0, 1, 1);	
	gtk_grid_attach (GTK_GRID (source_encoder_pot), v_p_fb, 1, 1, 1, 1);	

	gtk_grid_attach (GTK_GRID (source_encoder_pot), w_e_fb, 2, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (source_encoder_pot), w_p_fb, 2, 1, 1, 1);	

	gtk_grid_attach (GTK_GRID (source_encoder_pot), x_e_fb, 3, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (source_encoder_pot), x_p_fb, 3, 1, 1, 1);	
	
	gtk_grid_attach (GTK_GRID (source_encoder_pot), y_e_fb, 4, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (source_encoder_pot), y_p_fb, 4, 1, 1, 1);	
	
	gtk_grid_attach (GTK_GRID (source_encoder_pot), z_e_fb, 5, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (source_encoder_pot), z_p_fb, 5, 1, 1, 1);	
	
}

void pwm_setup()
{	
	pwm_page = gtk_grid_new();
	gtk_grid_set_column_homogeneous( (GtkGrid*)pwm_page, TRUE);	
	
	GdkColor color;
	color.red = 0x7fff;
	color.blue = 0x0000;
	color.green = 0x00FF;
	gtk_widget_modify_bg(pwm_page, GTK_STATE_NORMAL, &color);

                                
//	GtkStyleContext* context = gtk_widget_get_style_context( (GtkWidget*) pwm_page );
//	gtk_style_context_add_provider( context, (GtkStyleProvider*)css, GTK_STYLE_PROVIDER_PRIORITY_USER );
		
	sliders_setup();
	encoder_selection_setup();
	action_buttons_setup();

	//GtkWidget *tab_about = gtk_label_new("Duty");
	gtk_widget_set_vexpand( pwm_page, TRUE );


	gtk_grid_attach (GTK_GRID (pwm_page), source_encoder_pot, 1, 0, 1, 1);	
	gtk_grid_attach (GTK_GRID (pwm_page), slider_grid,   0, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (pwm_page), action_items,  0, 2, 1, 1);
	
}




GtkWidget* robot_control_page = NULL;
void robot_setup()
{
	robot_control_page = gtk_grid_new();
	
}

GtkWidget* chat_page =NULL;
void chat_setup()
{
	chat_page = gtk_grid_new();
	
	GtkWidget* add_sequence = gtk_button_new_with_label("Sequence");	
	gtk_grid_attach (GTK_GRID (chat_page), add_sequence, 0, 1, 2, 1);	
}



void print_pwms()
{
	for (int i=0; i<5; i++)
		printf("pwm %d = %6.3f\n", i, pwms[i] );
}
