#ifndef GTKMM_SEQUENCERWINDOW_H
#define GTKMM_SEQUENCERWINDOW_H

#include <gtk/gtk.h>
//#include <gtk.h>

class SequencerWindow : public Gtk::Window
{
public:
  SequencerWindow();
  virtual ~SequencerWindow();

protected:
  //Signal handlers:
  void on_button_quit();

  //Tree model columns:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    { add(m_col_id); add(m_col_command); add(m_col_response); add(m_col_errors);}

    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_timestamp;
    Gtk::TreeModelColumn<Glib::ustring> m_col_command;
    Gtk::TreeModelColumn<short> m_col_response;
    Gtk::TreeModelColumn<short> m_col_errors;
  };
  
	void play_sequence();
	void on_button_quit();
	void on_button_stop();
	void on_button_run();
	void on_button_next();
	void on_button_rewind();
  

  ModelColumns m_Columns;

  //Child widgets:
  Gtk::Box m_VBox;

  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

  Gtk::ButtonBox m_ButtonBox;
  Gtk::Button m_Button_Rewind;
  Gtk::Button m_Button_Next;  
  Gtk::Button m_Button_Run;
  Gtk::Button m_Button_Stop;
  Gtk::Button m_Button_Quit;
};

#endif //GTKMM_SEQUENCERWINDOW_H
