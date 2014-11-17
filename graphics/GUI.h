#ifndef GUI_H
#define GUI_H

#include "Gate.h"

using namespace std;

class GUI;
class Button;
class Canvas;

class Button : Fl_Button {
	GUI* parent;
public:
	Button(int x, int y, int h, int w, const char* label) : Fl_Button(x,y,w,h,label) {}
	GUI* Parent() {return parent;}
	void set_parent(GUI* p) {parent = p;}
};

//-----------------------------------------------------------------------

class GUI: public Fl_Widget {
	Canvas* parent;
	Button* and_button;
	Button* not_button;
	Button* or_button;
	Button* accept_button;
	Fl_Input* input1;
	Fl_Input* input2;
	int gate_button;
	Button* remove_button;

	int height;
	int width;
public:
	GUI(int X, int Y, int W, int H, const char*L=0);
	Canvas* Parent() {return parent;}
	void set_parent(Canvas* p) {parent = p;}
	void draw();
	Fl_Input* Input1() {return input1;}
	Fl_Input* Input2() {return input2;}
	int get_gate_button() {return gate_button;};
	void set_gate_button(int button) {gate_button = button;};
};

//-----------------------------------------------------------------------

class Canvas : public Fl_Widget{
	GUI* gui;
	vector<Gate*> gates;
	Fl_Scroll* parent;
	Truth_Table* table;
	
public:
    Canvas(int X, int Y, int W, int H, Fl_Scroll* sc, const char*L=0);
	void add_gate(int gate, Gate* input1, Gate* input2);
	void add_gate(int gate, Gate* input);
	void add_gate(int gate);
	Fl_Scroll* Parent() {return parent;}
	void set_parent(Fl_Scroll* p) {parent = p;}
    void draw();
	int num_gates () {return gates.size();}
	vector<Gate*> *Gates () {return &gates;}
	Truth_Table* get_table() {return table;}
	void set_table(Truth_Table* t) {table = t;}
};
#endif