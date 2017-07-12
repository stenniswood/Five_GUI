#ifndef _SEQUENCER_PAGE_HPP_
#define _SEQUENCER_PAGE_HPP_



extern GtkWidget* sequencer_page;
extern GtkListStore* Sequencer;		// ListStore here.

void sequencer_add_entry(char* DeviceName, char* mCommand, char* mResponse);

void sequencer_setup();


#endif
