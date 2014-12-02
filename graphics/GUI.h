/*
   GUI.h
   Steven G. Leal		November 23, 2014
   Ryan Meyers
   Sahil Dhanju
*/

//
// Definition of the GUI class. Handles button data and input fields.
//

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
	Button* remove_button;
	Button* check_button;
	Button* load_button;
	Button* save_button;
	Button* gen_button;
	Fl_Input* input1;
	Fl_Input* input2;
	int gate_button;
	vector<Fl_Input*> inputs;
	string message;

	int height;
	int width;
public:
	GUI(int X, int Y, int W, int H, const char*L=0);
	Canvas* Parent() {return parent;}
	void set_parent(Canvas* p) {parent = p;}
	void draw();
	Fl_Input* Input1() {return input1;}
	Fl_Input* Input2() {return input2;}
	Fl_Input* get_input(int i) {return inputs[i];}
	int get_gate_button() {return gate_button;};
	void set_gate_button(int button) {gate_button = button;};
	void set_message(string m) {message = m;}
};

#endif