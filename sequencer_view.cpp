#include <gtk/gtk.h>
#include <iostream>
#include "sequencer_view.h"


SequencerWindow::SequencerWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Quit("Quit"),
  m_Button_Stop("Stop"),
  m_Button_Run("Run"),
  m_Button_Next("Next"),
  m_Button_Rewind("Rewind"),
{
  set_title("Sequencer View");
  set_border_width(5);
  set_default_size(400, 200);

  add(m_VBox);

  //Add the TreeView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.add(m_TreeView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_VBox.pack_start(m_ScrolledWindow);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Rewind, Gtk::PACK_SHRINK);
  m_ButtonBox.pack_start(m_Button_Next, Gtk::PACK_SHRINK);
  m_ButtonBox.pack_start(m_Button_Run, Gtk::PACK_SHRINK);
  m_ButtonBox.pack_start(m_Button_Stop, Gtk::PACK_SHRINK);
  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);

  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &SequencerWindow::on_button_quit) );
  m_Button_Stop.signal_clicked().connect( sigc::mem_fun(*this,
              &SequencerWindow::on_button_quit) );
  m_Button_Run.signal_clicked().connect( sigc::mem_fun(*this,
              &SequencerWindow::on_button_quit) );
  m_Button_Next.signal_clicked().connect( sigc::mem_fun(*this,
              &SequencerWindow::on_button_quit) );
  m_Button_Rewind.signal_clicked().connect( sigc::mem_fun(*this,
              &SequencerWindow::on_button_quit) );

  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);

    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_timestamp;
    Gtk::TreeModelColumn<Glib::ustring> m_col_command;
    Gtk::TreeModelColumn<short> m_col_response;
    Gtk::TreeModelColumn<short> m_col_errors;


  //Fill the TreeView's model
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_timestamp] = "0";
  row[m_Columns.m_col_command]   = "use encoder";
  row[m_Columns.m_col_response]  = " ";  
  row[m_Columns.m_col_errors]    = "not executed;
  row = *(m_refTreeModel->append());
  
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_timestamp] = "0";
  row[m_Columns.m_col_command] = "pwm v0.5 w0.56 x0.9 y0.2 z0.1";
  row[m_Columns.m_col_response]  = " ";  
  row[m_Columns.m_col_errors]    = "not executed;
  row = *(m_refTreeModel->append());
  
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_timestamp] = "0";
  row[m_Columns.m_col_command]   = "delay 1000";		// preprocessed by sequencer
  row[m_Columns.m_col_response]  = " ";  
  row[m_Columns.m_col_errors]    = "not executed;
  row = *(m_refTreeModel->append());
    
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_timestamp] = "0";
  row[m_Columns.m_col_command]   = "POS v55000 w1120 x180 y270 z60";		// preprocessed by sequencer
  row[m_Columns.m_col_response]  = " ";  
  row[m_Columns.m_col_errors]    = "not executed;
  row = *(m_refTreeModel->append());

  //Add the TreeView's view columns:
  //This number will be shown with the default numeric formatting.
  m_TreeView.append_column("ID", m_Columns.m_col_id);
  m_TreeView.append_column("TimeStamp", m_Columns.m_col_timestamp );
  m_TreeView.append_column("Command", m_Columns.m_col_command     );
  m_TreeView.append_column("Response", m_Columns.m_col_response   );  
  m_TreeView.append_column("Errors", m_Columns.m_col_errors       );
  
  // Display a progress bar instead of a decimal number:
/*  auto cell = Gtk::manage(new Gtk::CellRendererProgress);
  int cols_count = m_TreeView.append_column("Some percentage", *cell);
  auto pColumn = m_TreeView.get_column(cols_count - 1);
  if(pColumn)
  {
    pColumn->add_attribute(cell->property_value(), m_Columns.m_col_percentage);
  } */

  //Make all the columns reorderable:
  //This is not necessary, but it's nice to show the feature.
  //You can use TreeView::set_column_drag_function() to more
  //finely control column drag and drop.
  for(guint i = 0; i < 5; i++)
  {
    auto column = m_TreeView.get_column(i);
    column->set_reorderable();
  }

  show_all_children();
}

SequencerWindow::~SequencerWindow()
{
}

SequencerWindow::play_sequence()
{
/*	for (int i=0; i<m_col_id.size(); i++)
	{
		if (strnstr(m_col_command[i], "delay", 5)!=NULL)
			sleep(us);
		else {
			// Send command
					
		}
	}*/
}

void SequencerWindow::on_button_quit()
{
  hide();
}
void SequencerWindow::on_button_stop()
{
  hide();
}
void SequencerWindow::on_button_run()
{
	play_sequencer()
}
void SequencerWindow::on_button_next()
{
	
}
void SequencerWindow::on_button_rewind()
{
  hide();
}

