#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <string>
#include <vector>
#include <iostream>
#include "stdio.h"
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
	void set_parent(GUI* p) {parent = p;}
};

class GUI {
	DrawStuff* parent;
	Button* and_button;
	Button* not_button;
	Button* or_button;
	Button* accept_button;
	Fl_Input* input1;
	Fl_Input* input2;
	int gate_button;

	int height;
	int width;
public:
	GUI(int sw, int sh);
	DrawStuff* Parent() {return parent;}
	void set_parent(DrawStuff* p) {parent = p;}
	Fl_Input* Input1() {return input1;}
	Fl_Input* Input2() {return input2;}
	int get_gate_button() {return gate_button;};
	void set_gate_button(int button) {gate_button = button;};
};

class DrawStuff : public Fl_Widget {
	And_Gate ag;
	GUI*  gui;
	vector<Gate*> gates;
	Fl_Double_Window* parent;
	
public:
    DrawStuff(int X, int Y, int W, int H, const char*L=0);
	void add_gate(int gate, Gate* input1, Gate* input2);
	void add_gate(int gate, Gate* input);
	void add_gate(int gate);
	Fl_Double_Window* Parent() {return parent;}
	void set_parent(Fl_Double_Window* p) {parent = p;}
    void draw();
	int num_gates () {return gates.size();}
	vector<Gate*> Gates () {return gates;}
};
