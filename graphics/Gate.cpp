/*
   Gate.cpp
   Steven G. Leal		November 23, 2014
   Ryan Meyers
   Sahil Dhanju
*/

//
// This is the implementation of the graphical gates to be drawn on the canvas.
//

#include "Truth_Table.h"
using namespace std;

Gate::Gate(Point p, vector<bool>* out, Canvas* pa, const char* L){
	pos = p;
	for (int i=0;i< (*out).size();++i) {
		output.push_back((*out)[i]);
	}
	accepted = true;
	parent = pa;
}
void Gate::draw() { // Draws the default gate structure (a rectangle and its output)
	fl_color(fl_rgb_color(0,79,255));
	fl_line_style(FL_SOLID, 4);
	fl_line(pos.x + Parent()->x(), pos.y + Parent()->y(), Fl::w()-1, pos.y + Parent()->y());
	fl_rectf(pos.x+Parent()->x()-16,pos.y+Parent()->y()-16,32,32);
}
void Gate::set_output(vector<bool>* out) {
	output.clear();
	for (int i=0;i< (*out).size();++i) {
		output.push_back((*out)[i]);
	}
}

//-----------------------------------------------------------------------

And_Gate::And_Gate(Point p, Gate* i1, Gate* i2, Canvas* pa): Gate(p, pa) {
	input1 = i1;
	input2 = i2;
	AND = new Fl_PNG_Image("./Gate_icons/And_Gate.png");
	AND_gray = new Fl_PNG_Image("./Gate_icons/And_Gate.png");
	AND_gray->desaturate();
}
void And_Gate::draw() {
	cal_output();
	int x = Parent()->x() + Gate::Pos().x;
	int y = Parent()->y() + Gate::Pos().y;
	
	Fl_Widget* ds = ((Fl_Widget*)Gate::Parent());
	
	fl_color(fl_rgb_color(255,178,0));
	fl_line_style(FL_SOLID, 4);
	fl_line(x, y, ds->w()-1, y);//Draw wire
	
	fl_color(fl_rgb_color(0,190,0));
	fl_line_style(FL_SOLID, 2);
	fl_line(x-29, y+4, x-29, (*input1).Pos().y + Parent()->y());//Draw input1 wire
	
	fl_color(fl_rgb_color(255,0,0));
	fl_line_style(FL_SOLID, 2);
	fl_line(x-22, y-3, x-23, (*input2).Pos().y + Parent()->y());//Draw input1 wire

	if (Accepted())
		AND->draw(x-(AND->w()/2),y-(AND->h()/2)); //Draw Gate
	else {
		AND_gray->draw(x-(AND->w()/2),y-(AND->h()/2));
	}
		
	
}
void And_Gate::cal_output() {
	vector<bool> outputs;
	for (int i=0; i<(*input1).get_output().size(); i++) {
		outputs.push_back((*input1).get_output()[i]&&(*input2).get_output()[i]);
	}
	Gate::set_output(&outputs);
}

//-----------------------------------------------------------------------

Or_Gate::Or_Gate(Point p, Gate* i1, Gate* i2, Canvas* pa): Gate(p, pa) {
	input1 = i1;
	input2 = i2;
	OR  = new Fl_PNG_Image("./Gate_icons/Or_Gate.png");
	OR_gray  = new Fl_PNG_Image("./Gate_icons/Or_Gate.png");
	OR_gray->desaturate();
}
void Or_Gate::draw() {
	cal_output();
	int x = Parent()->x() + Gate::Pos().x;
	int y = Parent()->y() + Gate::Pos().y;
	
	Fl_Widget* ds = ((Fl_Widget*)Gate::Parent());
	
	fl_color(fl_rgb_color(24,202,237));
	fl_line_style(FL_SOLID, 4);
	fl_line(x, y, ds->w()-1, y);//Draw wire
	
	fl_color(fl_rgb_color(0,190,0));
	fl_line_style(FL_SOLID, 2);
	fl_line(x-29, y+5, x-29, (*input1).Pos().y + Parent()->y());//Draw input1 wire
	
	fl_color(fl_rgb_color(255,0,0));
	fl_line_style(FL_SOLID, 2);
	fl_line(x-19, y-4, x-19, (*input2).Pos().y + Parent()->y());//Draw input2 wire
	
	if (Accepted())
		OR->draw(x-(OR->w()/2),y-(OR->h()/2)); //Draw Gate
	else {
		OR_gray->draw(x-(OR->w()/2),y-(OR->h()/2));
	}
	
}
void Or_Gate::cal_output() {
	vector<bool> outputs;
	for (int i=0; i<(*input1).get_output().size(); i++) {
		outputs.push_back((*input1).get_output()[i]||(*input2).get_output()[i]);
	}
	Gate::set_output(&outputs);
}

//-----------------------------------------------------------------------

Not_Gate::Not_Gate(Point p, Gate* i1, Canvas* pa): Gate(p, pa) {
	input1 = i1;
	NOT = new Fl_PNG_Image("./Gate_icons/Not_Gate.png");
	NOT_gray  = new Fl_PNG_Image("./Gate_icons/Not_Gate.png");
	NOT_gray->desaturate();
}
void Not_Gate::draw() {
	cal_output();
	int x = Parent()->x() + Gate::Pos().x;
	int y = Parent()->y() + Gate::Pos().y;
	
	Fl_Widget* ds = ((Fl_Widget*)Gate::Parent());
	
	fl_color(fl_rgb_color(125,118,50));
	fl_line_style(FL_SOLID, 4);
	fl_line(x, y, ds->w()-1, y);//Draw wire
	
	fl_color(fl_rgb_color(255,0,0));
	fl_line_style(FL_SOLID, 2);
	fl_line(x-29, y, x-29, (*input1).Pos().y + Parent()->y());//Draw input1 wire
	
	if (Accepted())
		NOT->draw(x-(NOT->w()/2),y-(NOT->h()/2)); //Draw Gate
	else {
		NOT_gray->draw(x-(NOT->w()/2),y-(NOT->h()/2));
	}
	
}
void Not_Gate::cal_output() {
	vector<bool> outputs;
	for (int i=0; i<(*input1).get_output().size(); i++) {
		outputs.push_back(!(*input1).get_output()[i]);
	}
	Gate::set_output(&outputs);
}
