#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include <math.h> 
#include <vector>
#include "Gate.h"
#include "GUI.h"
#include <iostream>

using namespace std;

int main() {
	Fl_Double_Window win(1600,900,"Gates");
	DrawStuff control(0, 0, win.w(), win.h());
	control.set_parent(&win);
    win.resizable(win);
    win.show();
    return(Fl::run());
}

