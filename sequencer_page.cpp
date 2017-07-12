#include <gtk/gtk.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "sequencer_page.hpp"
#include "drive_five.h"


extern DriveFive five;


GtkWidget* delay_time=NULL;
GtkWidget* step_time=NULL;

GtkWidget*    sequencer_page  = NULL;
GtkListStore* Sequencer       = NULL;
int 		  Sequencer_id 	  = 0;
int 		  Current_sequencer_id = 0;
enum { SEQUENCE_ID, DEVICE, TIMESTAMP, COMMAND, RESPONSE, EXEC_STATUS, NUM_COLUMNS  };
GtkWidget* 	  seq_buttons	  =NULL;


void sequencer_add_entry(char* DeviceName, char* mCommand, char* mResponse)
{
	// Get TimeStamp:
	char timestamp[256];		
	time_t rawtime;   
	time ( &rawtime );
	struct tm* timeinfo = localtime (&rawtime);
	strftime (timestamp,80,"%I:%M%p.",timeinfo);

	GtkTreeIter   iter;
	gtk_list_store_append( Sequencer, &iter );  /* Acquire an iterator */
	gtk_list_store_set   ( Sequencer, &iter, 
	 0, Sequencer_id++,
	 1, DeviceName,
	 2, timestamp,
	 3, mCommand,
	 4, mResponse,
	 5, "not executed",
	 -1);
}

gboolean  seq_play_foreach_func (GtkTreeModel *model,
                GtkTreePath  *path,
                GtkTreeIter  *iter,
                gpointer      user_data)
  {
    gchar *device, *command, *tree_path_str;

    /* Note: here we use 'iter' and not '&iter', because we did not allocate
     *  the iter on the stack and are already getting the pointer to a tree iter */
    gtk_tree_model_get (model,   iter,
                        DEVICE,  &device,
                        COMMAND, &command,  -1 );                        

    tree_path_str = gtk_tree_path_to_string(path);
    g_print ("Row %s:\t%s\t%s\n", tree_path_str, device, command );
	five.send_command( command );

	double theStep = gtk_spin_button_get_value( (GtkSpinButton*)step_time );
	int time_step = fabs(theStep);
	usleep( time_step*1000 );		// Pause between every line of execution.  ie Playback rate.
	
	if (strstr(command,"delay")!=NULL)	// if the command is a "delay 500 ms"
	{
		char* delay_ptr = strchr(command, ' ')+1;
		char* ms_ptr    = strchr(delay_ptr, ' ');
		*ms_ptr = 0;
		int delay_ms = atoi(delay_ptr);
		usleep( delay_ms * 1000 );					// Delay!
	}

    g_free(tree_path_str);
    g_free(device );    /* gtk_tree_model_get made copies of       */
    g_free(command);    /* the strings for us when retrieving them */
    return FALSE; 		/* do not stop walking the store, call us with next row */
  }
  

void cb_start_over( GtkWidget *range, gpointer  user_data )
{
	Current_sequencer_id = 0;
}
void cb_play_sequence( GtkWidget *range, gpointer  user_data )
{
	gtk_tree_model_foreach( GTK_TREE_MODEL(Sequencer), seq_play_foreach_func, NULL );

//	send_message( mCmd );
}
void cb_stop_sequencer( GtkWidget *range, gpointer  user_data )
{
}
void cb_add_delay_to_sequencer( GtkWidget *range, gpointer  user_data )
{
	char delay_msg[32];
	double theDelay = gtk_spin_button_get_value( (GtkSpinButton*)delay_time );
	int delay_i = fabs(theDelay);
	sprintf(delay_msg, "delay %d ms", delay_i );
//	char* device_name = gtk_combo_box_text_get_active_text(five_stack);
	sequencer_add_entry("internal", delay_msg, "");
}

void cb_add_wait_pid_to_sequencer( GtkWidget *range, gpointer  user_data )
{
	char delay_msg[32];
	double theDelay = gtk_spin_button_get_value( (GtkSpinButton*)delay_time );
	int delay_i     = fabs(theDelay);
	sprintf(delay_msg, "wait for pid %d ms", delay_i );
	sequencer_add_entry("internal", delay_msg, "");
}

void seq_action_buttons_setup()
{
	seq_buttons = gtk_grid_new();

	GtkWidget *step_time_label = gtk_label_new(NULL);	
	gtk_label_set_markup(GTK_LABEL(step_time_label), "<b>Step Time</b>");

	GtkWidget *drive_selection = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text ((GtkComboBoxText*) drive_selection, "V");
	gtk_combo_box_text_append_text ((GtkComboBoxText*) drive_selection, "W");
	gtk_combo_box_text_append_text ((GtkComboBoxText*) drive_selection, "X");
	gtk_combo_box_text_append_text ((GtkComboBoxText*) drive_selection, "Y");
	gtk_combo_box_text_append_text ((GtkComboBoxText*) drive_selection, "Z");
	gtk_combo_box_set_active( (GtkComboBox*) drive_selection, 0);

	// gtk_button_new_with_label("Rewind");
	//GtkWidget* play = gtk_button_new_with_label("play");
	GtkWidget* rewind = gtk_button_new_from_icon_name ("media-seek-backward", GTK_ICON_SIZE_BUTTON );
	GtkWidget* play   = gtk_button_new_from_icon_name ("media-playback-start", GTK_ICON_SIZE_BUTTON );
	GtkWidget* pause  = gtk_button_new_from_icon_name ("media-playback-pause", GTK_ICON_SIZE_BUTTON );
	GtkWidget* stop   = gtk_button_new_from_icon_name ("media-playback-stop", GTK_ICON_SIZE_BUTTON );
	GtkWidget* delay  = gtk_button_new_with_label("Delay");
	GtkWidget* wait_pid  = gtk_button_new_with_label("Wait PID");	
	delay_time = gtk_spin_button_new_with_range(0.0, 10000, 10);	
	step_time  = gtk_spin_button_new_with_range(0.0, 10000, 10);
	gtk_spin_button_set_value( (GtkSpinButton*)delay_time, 250.0 );
	gtk_spin_button_set_value( (GtkSpinButton*)step_time, 100.0 );
	

	gtk_grid_attach (GTK_GRID (seq_buttons), step_time_label, 0, 0, 1, 1);		
	gtk_grid_attach (GTK_GRID (seq_buttons), step_time, 1, 0, 1, 1);		
	gtk_grid_attach (GTK_GRID (seq_buttons), rewind,    0, 1, 1, 1);	
	gtk_grid_attach (GTK_GRID (seq_buttons), play,      0, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (seq_buttons), stop,      0, 3, 1, 1);
	gtk_grid_attach (GTK_GRID (seq_buttons), delay_time,  1, 5, 1, 1);
	gtk_grid_attach (GTK_GRID (seq_buttons), delay,	      0, 5, 1, 1);				
	gtk_grid_attach (GTK_GRID (seq_buttons), wait_pid,	  0, 6, 1, 1);
	gtk_grid_attach (GTK_GRID (seq_buttons), drive_selection, 1, 6, 1, 1);		
		
	g_signal_connect ( rewind, "clicked", (GCallback)cb_start_over, NULL);		
	g_signal_connect ( play, "clicked", (GCallback)cb_play_sequence, NULL);		
	g_signal_connect ( stop, "clicked", (GCallback)cb_stop_sequencer, NULL);		
	g_signal_connect ( delay, "clicked", (GCallback)cb_add_delay_to_sequencer, NULL);
	g_signal_connect ( delay, "clicked", (GCallback)cb_add_wait_pid_to_sequencer, NULL);
						
}

void sequencer_setup()
{
	sequencer_page = gtk_grid_new();
	gtk_grid_set_column_homogeneous( (GtkGrid*)sequencer_page, TRUE);	
	
	GdkColor color;
	color.red = 0x0000;
	color.blue = 0x5FFF;
	color.green = 0x00;
	gtk_widget_modify_bg(sequencer_page, GTK_STATE_NORMAL, &color);

	seq_action_buttons_setup();

	Sequencer = gtk_list_store_new (6, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	// Fill in some dummy data:
//	sequencer_add_entry("/dev/ttyKEITH", "Glory Lord Jesus", "Power and praise be to his name");
	//sequencer_add_entry("Glory Lord Jesus!", "Heaven and earth adore you!");
	
	// Create the View : 
	GtkWidget *Sequencer_view;
	Sequencer_view = gtk_tree_view_new_with_model (GTK_TREE_MODEL (Sequencer));	

	// Create the Columns (model/view architecture)
	GtkCellRenderer   *renderer = gtk_cell_renderer_text_new ();
	GtkTreeViewColumn *column;
	column   = gtk_tree_view_column_new_with_attributes ("Step",
                                                   renderer,
                                                   "text", SEQUENCE_ID,
                                                   NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (Sequencer_view), column);

	column   = gtk_tree_view_column_new_with_attributes ("Device",
                                                   renderer,
                                                   "text", DEVICE,
                                                   NULL);	
	gtk_tree_view_append_column (GTK_TREE_VIEW (Sequencer_view), column);	
	
	column   = gtk_tree_view_column_new_with_attributes ("TimeStamp",
                                                   renderer,
                                                   "text", TIMESTAMP,
                                                   NULL);	
	gtk_tree_view_append_column (GTK_TREE_VIEW (Sequencer_view), column);	

	column   = gtk_tree_view_column_new_with_attributes ("Command",
                                                   renderer,
                                                   "text", COMMAND,
                                                   NULL);	
	gtk_tree_view_append_column (GTK_TREE_VIEW (Sequencer_view), column);	

	column   = gtk_tree_view_column_new_with_attributes ("Response",
                                                   renderer,
                                                   "text", RESPONSE,
                                                   NULL);	
	gtk_tree_view_append_column (GTK_TREE_VIEW (Sequencer_view), column);	

//                                          "Status", EXEC_STATUS,
	gtk_grid_attach (GTK_GRID (sequencer_page), (GtkWidget*)Sequencer_view, 0, 0, 3, 3);
	gtk_grid_attach (GTK_GRID (sequencer_page), (GtkWidget*)seq_buttons,    3, 0, 1, 4);
}

