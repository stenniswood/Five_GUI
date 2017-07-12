#include <gtk/gtk.h>
#include <stdlib.h>
#include <vector>
#include <string> 
#include <math.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <errno.h>

#include "music_page.hpp"


GtkWidget*    music_page = NULL;
GtkListStore* SongList   = NULL;
int Song_index = 0;
enum { SONG_ID, PLAYLENGTH, NAME, ARTIST, FREQUENCY, NUM_COLUMNS  };


void song_add_entry(const char* Name, const char* Artist)
{
	// Get TimeStamp:
	char timestamp[256];		
	time_t rawtime;   
	time ( &rawtime );
	struct tm* timeinfo = localtime (&rawtime);
	strftime (timestamp,80,"%I:%M%p.",timeinfo);

	GtkTreeIter   iter;
	gtk_list_store_append( SongList, &iter );  /* Acquire an iterator */
	gtk_list_store_set (SongList, &iter, 
	 0, Song_index++,
	 1, timestamp,
	 2, Name,
	 3, Artist,
	 4, "not executed",
	 -1);
}

void play_song( char* path, char* filename )
{
	char cmd[256];
	sprintf(cmd, "omxplayer -o local \"%s%s\" &\n", path,filename);
	printf("play_song:%s\n", cmd);
	system(cmd);
}

void cb_play_song(  GtkTreeView  	  *tree_view,
               		GtkTreePath       *path,
               		GtkTreeViewColumn *column,
               		gpointer           user_data)
{
	char* filename;
	char* artist;

	printf("cb_play_song callback\n");
		
	GtkTreeSelection *tmp   = gtk_tree_view_get_selection( (GtkTreeView*) tree_view );
	GtkTreeModel     *model = gtk_tree_view_get_model( (GtkTreeView*) tree_view );
	GtkTreeIter iter;
	gboolean okay = gtk_tree_model_get_iter (model,
                         &iter, path);

	gtk_tree_model_get (model, &iter,
                        NAME,   &filename,
                        ARTIST, &artist,
                        -1);
	printf("cb_play_song %s %s\n", filename, artist);
    play_song( artist, filename );

    g_free(filename);
    g_free(artist  );
}

using namespace std;
vector<string> filelist_paths;
vector<string> filelist_names;

void populate_songs_in_directory(char* mPath,
								vector<string> &filelist_paths,
								vector<string> &filelist_names,
								bool show_hidden_files )
{
	DIR           *d;
	struct dirent *dir;
	d 	= opendir(mPath);
	bool	is_hidden_file = false;
	if (d)
	{
		// go thru all FILES:
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_type==DT_REG)  
			{
				is_hidden_file = (dir->d_name[0]=='.')?true:false;
				if ((show_hidden_files==false) && (is_hidden_file))
					continue;		// skip!
				filelist_paths.push_back( mPath );
				filelist_names.push_back( dir->d_name );
			}        
		}
		closedir(d);
	}
}

void add_files_to_tree_view()
{
	size_t size = filelist_names.size();
	for (int i=0; i<size; i++)
		song_add_entry( filelist_names[i].c_str(), filelist_paths[i].c_str() );
}

// dont need:
void populate_directories( char* mPath, bool show_hidden_files=false )
{
	DIR           *d;
	struct dirent *dir;
	d 	 = opendir(mPath);
	bool   is_hidden_file = false;

	if (d)
	{
		// Next, go thru all DIRECTORIES:	
		while ((dir=readdir(d)) != NULL)
		{	
			// Next go thru all directories:
			// if a directory, then recurse:
			if (dir->d_type==DT_DIR)  
			{
				is_hidden_file = (dir->d_name[0]=='.') ? true:false;
				if ((show_hidden_files==false) && (is_hidden_file))
					continue;		// skip!

				song_add_entry( dir->d_name, mPath );
/*				icon_id.push_back( DIRECTORY_ID );	   */
			}
		}
		closedir(d);
	}	
}


void music_setup()
{
	music_page = gtk_grid_new();
	
		GdkColor color;
	color.red = 0x5FFF;
	color.blue = 0x5FFF;
	color.green = 0x5FFF;
	gtk_widget_modify_bg(music_page, GTK_STATE_NORMAL, &color);

	SongList = gtk_list_store_new (5, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	// Fill in some dummy data:
	char name1[]   = "Glory Lord Jesus";
	char artist1[] = "Keith Green";
	song_add_entry( (char*)name1, (char*)artist1 );
	populate_songs_in_directory( (char*)"/home/pi/Music/", filelist_paths, filelist_names );
	add_files_to_tree_view();
	
	// Create the View : 
	GtkWidget *Music_view;
	Music_view = gtk_tree_view_new_with_model (GTK_TREE_MODEL (SongList));	
	g_signal_connect ( Music_view, "row-activated", (GCallback)cb_play_song, NULL );
	

	// Create the Columns (model/view architecture)
	GtkCellRenderer   *renderer = gtk_cell_renderer_text_new ();
	GtkTreeViewColumn *column;
	column   = gtk_tree_view_column_new_with_attributes ("  ",
                                                   renderer,
                                                   "text", SONG_ID,
                                                   NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (Music_view), column);

	column   = gtk_tree_view_column_new_with_attributes ("PlayLength",
                                                   renderer,
                                                   "text", PLAYLENGTH,
                                                   NULL);	
	gtk_tree_view_append_column (GTK_TREE_VIEW (Music_view), column);	

	column   = gtk_tree_view_column_new_with_attributes ("Name",
                                                   renderer,
                                                   "text", NAME,
                                                   NULL);	
	gtk_tree_view_append_column (GTK_TREE_VIEW (Music_view), column);	

	column   = gtk_tree_view_column_new_with_attributes ("Artist",
                                                   renderer,
                                                   "text", ARTIST,
                                                   NULL);	
	gtk_tree_view_append_column (GTK_TREE_VIEW (Music_view), column);	

	column   = gtk_tree_view_column_new_with_attributes ("Frequency",
                                                   renderer,
                                                   "text", FREQUENCY,
                                                   NULL);	
	gtk_tree_view_append_column (GTK_TREE_VIEW (Music_view), column);	

//                                          "Status", EXEC_STATUS,
	gtk_grid_attach (GTK_GRID (music_page), (GtkWidget*)Music_view, 0, 0, 3, 3);
}

