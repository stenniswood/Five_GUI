#include <gtk/gtk.h>
#include "drive_five.h"
#include "sequencer_page.hpp"
#include "drive_five.h"

extern DriveFive five;


GtkWidget * action_items=NULL;
GtkWidget*  continuous_send=NULL;
GtkWidget*  five_stack=NULL;
gint 		IsActive=0;
char		last_operation[512];		// Store the last GUI action as a command line to Five.  
										// Latter can be used to send or to add to sequencer.

/******************** CALLBACK FUNCTIONS *******************************/
/* Callback function for any change to any PWM slider. */
void cb_send(GtkWidget *range, gpointer  user_data)
{
	printf("cb_pwm_change()  active=%d\n", IsActive );
	// Fill these in anyway, even if not Active - so we can 'compose' the sequencer commands.
	if (IsActive) 
	{
		five.send_command  ( last_operation );
	}
	else printf("not active!\n");
}

void cb_stop_motors(GtkButton *button, gpointer   user_data)
{
	char cmd[128];
	sprintf( cmd, "stop\r\n" );	
	printf( "%s\n", cmd );
	five.send_command( cmd );
}

void cb_active_change(GtkWidget *active, gpointer  user_data)
{
	IsActive = gtk_toggle_button_get_active( (GtkToggleButton*)active );
	printf("Active Button pushed!  active=%d\n", IsActive );
}
void cb_add_to_sequencer(GtkWidget *range, gpointer  user_data)
{
	char* device_name = gtk_combo_box_text_get_active_text((GtkComboBoxText*) five_stack);	
	sequencer_add_entry(device_name, last_operation, "reply ignored");
}


void action_buttons_setup()
{
	action_items= gtk_action_bar_new ();

	GtkWidget* add_sequence = gtk_button_new_with_label("Sequence");	
	GtkWidget* send_motors  = gtk_button_new_with_label("Send");
	GtkWidget* stop_motors  = gtk_button_new_with_label("Stop!");
	continuous_send 		= gtk_check_button_new_with_label("Active");

	five_stack = gtk_combo_box_text_new();
	for (int i=0; i<DriveFive_device_names.size(); i++)
	{
		gtk_combo_box_text_append_text ((GtkComboBoxText*) five_stack, DriveFive_device_names[i].c_str() );
		//gtk_combo_box_text_append_text ((GtkComboBoxText*) five_stack, "/dev/ttyUSB0");
	}
	gtk_combo_box_set_active( (GtkComboBox*) five_stack, 0);	
	
	g_signal_connect ( continuous_send, "clicked", (GCallback)cb_active_change, NULL);
	g_signal_connect ( add_sequence, "clicked", (GCallback)cb_add_to_sequencer, NULL);	
	g_signal_connect ( send_motors, "clicked", (GCallback)cb_send, NULL);
	g_signal_connect ( stop_motors, "clicked", (GCallback)cb_stop_motors, NULL);

	gtk_action_bar_pack_start( (GtkActionBar*)action_items, five_stack );			
	gtk_action_bar_pack_start( (GtkActionBar*)action_items, add_sequence );
	gtk_action_bar_pack_start( (GtkActionBar*)action_items, send_motors );
	gtk_action_bar_pack_start( (GtkActionBar*)action_items, stop_motors );
	gtk_action_bar_pack_start( (GtkActionBar*)action_items, continuous_send );	
}


