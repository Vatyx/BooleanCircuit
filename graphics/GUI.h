#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>
#include <string>
#include <vector>
#include <iostream>
#include "Gate.h"

using namespace std;

class GUI;
class Button;
class DrawStuff;


class Button : Fl_Button {
	GUI* parent;
public:
	Button(int x, int y, int h, int w, const char* label) : Fl_Button(x,y,w,h,label) {}
	GUI* Parent() {return parent;}
};

class GUI {
	DrawStuff* parent;
	Fl_Button* and_button;
	Fl_Button* not_button;
	Fl_Button* or_button;

	int height;
	int width;
public:
	GUI(int sw, int sh);
	DrawStuff* Parent() {return parent;}
};

class DrawStuff : public Fl_Widget {
	And_Gate ag;
	GUI*  gui;
	vector<Gate*> gates;
	
public:
    DrawStuff(int X, int Y, int W, int H, const char*L=0);
	void add_gate(int gate, Gate* input1, Gate* input2);
	void add_gate(int gate, Gate* input);
    void draw();
};
