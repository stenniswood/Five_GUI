LIBS = `pkg-config --libs gtk+-3.0`
CFLAGS = `pkg-config --cflags gtk+-3.0`


SRC = main.cpp pages.cpp drive_five.cpp pid_page.cpp sequencer_page.cpp status_page.cpp \
	music_page.cpp camera_page.cpp pictures_page.cpp about_page.cpp bk_actionbar.cpp

OBJS = main.o pages.o drive_five.o pid_page.o sequencer_page.o status_page.o \
	music_page.o camera_page.o pictures_page.o about_page.o bk_actionbar.o

#sequencer_view.cpp 

%.o: %.cpp
	g++ -c -o $@ $< $(CFLAGS)

bk_panel: $(OBJS)
	g++ -o  $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm *.o bk_panel

#//all:
#	g++ $(CFLAGS) -o bk_panel $(OBJS) $(LIBS)

