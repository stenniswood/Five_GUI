#ifndef _ACTION_HPP_
#define _ACTION_HPP_


extern GtkWidget*   action_items;
extern GtkWidget*   continuous_send;
extern GtkWidget*   five_stack;
extern gint 		IsActive;				// GUI controls should immediately operate on hardware
extern char			last_operation[512];		// Store the last GUI action as a command line to Five.  



void cb_stop_motors(GtkButton *button, gpointer   user_data);
void cb_active_change(GtkWidget *active, gpointer  user_data);
void cb_add_to_sequencer(GtkWidget *range, gpointer  user_data);
void action_buttons_setup();


#endif
