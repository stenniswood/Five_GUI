					Joing Us
				http://www.beyond-kinetics.com
				
This archive contains a graphical user interface to the Drive Five module.  It is based on GTK for Linux Raspberry Pi.
Code is pre-Alpha state, however some functionality is already working.  

			http://www.beyond-kinetics.com/store/five_product_details.php


# Five_GUI
"Drive Five" Demo software includes a sequencer for animating robot moves.  Plus control all aspects of the Five board from graphical controls.


PRE-REQUISITES:
===============
This repository has been built for RPI3.  To use you will need to install GTK:

	sudo apt-get install libgtk-3-dev

Also you will need a basic compiler:

	sudo apt-get install build-essential


BUILD:
======
	cd Five_GUI/
	make clean
	make

RUN:
====
	./bk_panel

