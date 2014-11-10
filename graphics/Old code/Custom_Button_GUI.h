/*
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Button {
	Fl_Button* button;
	Fl_PNG_Image *button_png;
	int x;
	int y;
public:
	Button(int xx, int yy, const char* a) {
		x = xx;
		y = yy;
		button_png  = new Fl_PNG_Image("./Gate_icons/And_Button.png");
		button = new Fl_Button(x,y,button_png->w(),button_png->h(), 0);
		button->hide();
	}
	void draw() {
		button_png->draw(x,y);
	}
};

class GUI {
	Button *and_button;
	Button *not_button;
	Button *or_button;
public:
	GUI(int w, int h) {
		and_button = new Button(0,h-64,"./Gate_icons/And_Button.png");
		
	}
	void draw() {
		and_button->draw();
	}
};
*/