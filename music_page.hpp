#ifndef _MUSIC_PAGE_HPP_
#define _MUSIC_PAGE_HPP_

#include <vector>
#include <string> 
using namespace std;

extern GtkWidget*    music_page;


void populate_songs_in_directory(char* mPath,
								vector<string> &filelist_paths,
								vector<string> &filelist_names,
								bool show_hidden_files=false );

void song_add_entry ( const char* Name, const char* Artist);
void music_setup	( );



#endif
