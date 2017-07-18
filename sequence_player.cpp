#include <iostream>
#include <fstream>



void play_back( char* mFilename )
{
	std::ifstream text (name);
	if (text.is_open())
	{
		while (text.good())
		{
			getline(text,line);
			file->content.append(line);
			file->content.push_back('\n');
		}
		text.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl << std::endl;
	}			
}

void execute_one_line( char* mSequenceLine )
{
	// SEND COMMAND TO FIVE:
    tree_path_str = gtk_tree_path_to_string(path);
    g_print ("Row %s:\t%s\t%s\n", tree_path_str, device, command );
	five.send_command( command );

	// PAUSE FOR TIME STEP:	
	double theStep = gtk_spin_button_get_value( (GtkSpinButton*)step_time );
	int time_step = fabs(theStep);
	usleep( time_step*1000 );		// Pause between every line of execution.  ie Playback rate.
	
	// PAUSE FOR USER REQUESTED DELAY :
	if (strstr(command,"delay")!=NULL)	// if the command is a "delay 500 ms"
	{
		char* delay_ptr = strchr(command, ' ')+1;
		char* ms_ptr    = strchr(delay_ptr, ' ');
		*ms_ptr = 0;
		int delay_ms = atoi(delay_ptr);
		usleep( delay_ms * 1000 );					// Delay!
	}

	// WAIT FOR PID axis:
	char cmd_key[] = "wait for pid";	
	if (strstr(command,cmd_key)!=NULL)	// if the command is a "delay 500 ms"
	{
		char* delay_ptr = command+9;		// search after 'Wait PID' for v w x y z
		*ms_ptr = 0;
		int delay_ms = atoi(delay_ptr);
		long int timeout = 0;
		while (fives[selected_board].is_pid_done( 'v' )==FALSE )
		{
			usleep(1000);
			// nothing
			timeout++;
			if (timeout > PID_TIMEOUT_MS)
				break;
		}
	}
}
