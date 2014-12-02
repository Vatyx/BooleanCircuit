/*
   Gate.h
   Steven G. Leal		November 23, 2014
   Ryan Meyers
   Sahil Dhanju
*/

//
// This is the definition of the graphical gates to be drawn on the canvas.
//

#ifndef GATE_H
#define GATE_H

#include "Helper_Functions.h"
using namespace std;

struct Point { //Point class was included to test the significance of a dedicated class for passing vector data.
	int x;
	int y;
	Point(){x=0;y=0;}
	Point(int xx, int yy) {
		x = xx;
		y = yy;
	}
};
//This Point class was derived from a version used in Principles and Practice Using C++" by Bjarne Stroustrup
inline bool operator==(Point a, Point b) { return a.x==b.x && a.y==b.y; } 
inline bool operator!=(Point a, Point b) { return !(a==b); }

//-----------------------------------------------------------------------

class Gate{ //Stores information on graphical gates and their outputs.
	bool accepted;
	Point pos;
	vector<bool> output;
	Canvas* parent;
public:
	Gate(Point p, Canvas* pa, const char* L=0){
		pos = p;
		parent = pa;
		accepted = true;
	}
	Gate(Point p, vector<bool>* out, Canvas* pa, const char* L=0);
	virtual void draw();
	void draw_output();
	void set_output(vector<bool>* out);
	vector<bool> get_output() {return output;}
	Point Pos(){return pos;}
	bool Accepted() {return accepted;}
	void set_accepted(bool a) {accepted = a;}
	Canvas* Parent() {return parent;}
	void set_parent(Canvas* p) {parent = p;}
};

//-----------------------------------------------------------------------
// The following child classes of the Gate subclass add gate inputs
// and output calculations.
//-----------------------------------------------------------------------
 

class And_Gate : public Gate {
	Gate* input1;
	Gate* input2;
	Fl_PNG_Image *AND;
	Fl_PNG_Image *AND_gray;
	Canvas *parent;
public:
	And_Gate(Point p, Gate* i1, Gate* i2, Canvas* pa);
	void draw();
	void cal_output();
	Gate* get_input1() {return input1;}
	Gate* get_input2() {return input2;}
};

//-----------------------------------------------------------------------

class Or_Gate : public Gate {
	Gate* input1;
	Gate* input2;
	Fl_PNG_Image *OR;
	Fl_PNG_Image *OR_gray;
public:
	Or_Gate(Point p, Gate* i1, Gate* i2, Canvas* pa);
	void draw();
	void cal_output();
	Gate* get_input1() {return input1;}
	Gate* get_input2() {return input2;}
};

//-----------------------------------------------------------------------

class Not_Gate : public Gate {
	Gate* input1;
	Fl_PNG_Image *NOT;
	Fl_PNG_Image *NOT_gray;
public:
	Not_Gate(Point p, Gate* i1, Canvas* pa);
	void draw();
	void cal_output();
	Gate* get_input1() {return input1;}
};

#endif