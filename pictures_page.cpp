#include <gtk/gtk.h>
#include <vector>
#include <string>
#include "pictures_page.hpp"
#include "music_page.hpp"


GtkWidget*    pictures_page = NULL;
GtkWidget*    current_image = NULL;

static vector<string> filelist_paths;
static vector<string> filelist_names;

using namespace std;
int current_index = 0;

void cb_show_prev_image( GtkWidget *range, gpointer  user_data )
{
	string fullfilename = filelist_paths[current_index] + "/" + filelist_names[current_index];	
	printf("cb_show_prev_image: %s\n", fullfilename.c_str() );
	gtk_image_set_from_file( (GtkImage*)current_image, fullfilename.c_str() );	
		gtk_widget_set_vexpand(current_image, TRUE);
	current_index--;
}
void cb_show_next_image( GtkWidget *range, gpointer  user_data )
{
	string fullfilename = filelist_paths[current_index] + "/" + filelist_names[current_index];	
	printf("cb_show_next_image: %s\n", fullfilename.c_str() );
	gtk_image_set_from_file( (GtkImage*)current_image, fullfilename.c_str() );	
		gtk_widget_set_vexpand(current_image, TRUE);
	current_index++;
}

void pictures_setup()
{
/* then we have to figure each images sizes and this windows size.  Must be another way...

	GtkAdjustment *hadj = gtk_adjustment_new (gdouble value,
                    gdouble lower,
                    gdouble upper,
                    gdouble step_increment,
                    gdouble page_increment,
                    gdouble page_size);
	GtkAdjustment *vadj = gtk_adjustment_new (gdouble value,
                    gdouble lower,
                    gdouble upper,
                    gdouble step_increment,
                    gdouble page_increment,
                    gdouble page_size);
	pictures_page = gtk_scrolled_window_new( hadj, vadj );
*/
	pictures_page = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

	

	char base_path[] = "/home/pi/Pictures";
	populate_songs_in_directory( base_path, filelist_paths, filelist_names );
							
	GtkWidget* next = gtk_button_new_from_icon_name ("go-next", GTK_ICON_SIZE_BUTTON );
	GtkWidget* prev = gtk_button_new_from_icon_name ("go-previous", GTK_ICON_SIZE_BUTTON );
	g_signal_connect ( next, "clicked", (GCallback)cb_show_next_image, NULL);		
	g_signal_connect ( prev, "clicked", (GCallback)cb_show_prev_image, NULL);		
	
	current_image = gtk_image_new_from_file ("bk_bridge_title.png");
	gtk_widget_set_vexpand(current_image, TRUE);
	
	gtk_box_pack_start( GTK_BOX(pictures_page), prev, FALSE, FALSE, 0 );
	gtk_box_pack_start( GTK_BOX(pictures_page), current_image, TRUE, TRUE, 0 );
	gtk_box_pack_end  ( GTK_BOX(pictures_page), next, FALSE, FALSE, 0 );

}

