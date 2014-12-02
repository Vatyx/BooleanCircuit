/*
   main.cpp
   Steven G. Leal		November 23, 2014
   Ryan Meyers
   Sahil Dhanju
*/

//
// Begins the program by opening the main window and starts the event handling.
//


#include "Truth_Table.h"

using namespace std;
int main() { 
	Fl_Double_Window win(1600,900,"Gates");
		Fl_Scroll scroll1(0,0,win.w(),500);
		scroll1.type(Fl_Scroll::BOTH_ALWAYS);
		scroll1.begin();
			Canvas* canvas = new Canvas(0, 0, scroll1.w(), scroll1.h(), &scroll1);
		scroll1.end();
		Fl_Scroll scroll2(0,scroll1.h(),win.w()-192,334);
		scroll2.type(Fl_Scroll::HORIZONTAL_ALWAYS);
		scroll2.begin();
			Truth_Table* table = new Truth_Table(0,scroll2.y(),scroll2.w(),scroll2.h(), canvas);
			canvas->set_table(table);
			table->set_scroll(&scroll2);
		scroll2.end();
		GUI gui(0,win.h()-64,win.w(),64);
		gui.set_parent(canvas);
		canvas->set_gui(&gui);
	win.end();
    win.resizable(win);
    win.show();
    return(Fl::run());
}

