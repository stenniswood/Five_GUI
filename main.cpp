#include <gtk/gtk.h>
#include "pid_page.hpp"
#include "status_page.hpp"
#include "sequencer_page.hpp"
#include "pages.hpp"
#include "drive_five.h"
#include "music_page.hpp"
#include "pictures_page.hpp"
#include "camera_page.hpp"
#include "about_page.hpp"


DriveFive five;


static void print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

void create_bk_control_panel( GtkWidget *window )
{
	GtkWidget* prog = gtk_progress_bar_new();
	gtk_progress_bar_set_fraction( (GtkProgressBar*)prog,      0.3 );

    bk_image = gtk_image_new_from_file ("bk_bridge_title.png");
    gtk_widget_set_hexpand(bk_image, TRUE);
    gtk_widget_set_vexpand(bk_image, TRUE);

	// add a page for 
	about_setup ();	
	pwm_setup   ();
	pid_setup   ();
	status_setup();
	robot_setup ();
	chat_setup  ();
	sequencer_setup();
	camera_setup   ();
	music_setup    ();
	pictures_setup ();
	
	GtkNotebook* bk_notebook = (GtkNotebook*)gtk_notebook_new ();
	GtkWidget *tab_about 	= gtk_label_new("About");
	GtkWidget *tab_pwm 		= gtk_label_new("PWM");
	GtkWidget *tab_pid 		= gtk_label_new("PID");
	GtkWidget *tab_status 	= gtk_label_new("Status");
	GtkWidget *tab_robot 	= gtk_label_new("Robot");	
	GtkWidget *tab_chat 	= gtk_label_new("Comms");		// direct to serial port
	GtkWidget *tab_sequencer = gtk_label_new("Sequencer");	

	gtk_notebook_set_show_border(bk_notebook, TRUE );
	gtk_notebook_set_tab_pos    (bk_notebook, GTK_POS_LEFT);	
	gtk_notebook_set_show_tabs  (bk_notebook, TRUE);
	gtk_notebook_set_scrollable (bk_notebook,TRUE);
	
	gint dummy = gtk_notebook_append_page ((GtkNotebook*)bk_notebook,
                          (GtkWidget*)about_page, tab_about);
	gint dummy2 = gtk_notebook_append_page ((GtkNotebook*)bk_notebook,
                          (GtkWidget*)pwm_page, tab_pwm);
	gint dummy3 = gtk_notebook_append_page ((GtkNotebook*)bk_notebook,
                          pid_page, tab_pid);
	gint dummy4 = gtk_notebook_append_page ((GtkNotebook*)bk_notebook,
                          status_page, tab_status);

	gint dummy5 = gtk_notebook_append_page ((GtkNotebook*)bk_notebook,
                          robot_control_page, tab_robot);
	gint dummy6 = gtk_notebook_append_page ((GtkNotebook*)bk_notebook,
                          chat_page, tab_chat);                          
	gint dummy7 = gtk_notebook_append_page ((GtkNotebook*)bk_notebook,
                          sequencer_page, tab_sequencer);

	GtkWidget *tab_camera   = gtk_label_new("Camera");		// direct to serial port
	GtkWidget *tab_music    = gtk_label_new("Music");		// direct to serial port
	GtkWidget *tab_pictures = gtk_label_new("Pictures");		// direct to serial port
	gint dummy8 = gtk_notebook_append_page ((GtkNotebook*)bk_notebook,
                          camera_page, tab_camera);
	gint dummy9 = gtk_notebook_append_page ((GtkNotebook*)bk_notebook,
                          music_page, tab_music);
	dummy8 = gtk_notebook_append_page ((GtkNotebook*)bk_notebook,
                          pictures_page, tab_pictures);

    gtk_container_add (GTK_CONTAINER (window), (GtkWidget*)bk_notebook);	
}

static void activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;  

  window = gtk_application_window_new (app);
  //gtk_window_fullscreen(GTK_WINDOW (window));
  
  gtk_window_set_title (GTK_WINDOW (window), "Control Panel");
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 200);
  
  create_bk_control_panel( window );
  
  gtk_widget_show_all (window);
}

int main (int argc,  char **argv)
{
  GtkApplication *app;
  int status;

  scan_available_boards();	// drive_five.cpp
  open_all_available();  
  //five.open("/dev/ttyUSB0");
  //five.set_baud(38400);

  app = gtk_application_new ("org.gtk.beyond_kinetics", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  close_all_fives();
  return status;
}

