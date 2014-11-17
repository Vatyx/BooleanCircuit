#ifndef GATE_H
#define GATE_H

#include "Classes.h"

using namespace std;

struct Point {
	int x;
	int y;
	Point(){x=0;y=0;}
	Point(int xx, int yy) {
		x = xx;
		y = yy;
	}
};
//Point Operators
inline bool operator==(Point a, Point b) { return a.x==b.x && a.y==b.y; } 
inline bool operator!=(Point a, Point b) { return !(a==b); }

//-----------------------------------------------------------------------

class Gate{
	Point pos;
	vector<bool> output;
	Canvas* parent;
public:
	Gate(Point p, Canvas* pa, const char* L=0){//Constructor
		pos = p;
		parent = pa;
	}
	Gate(Point p, vector<bool>* out, Canvas* pa, const char* L=0);
	virtual void draw();
	void draw_output();
	void set_output(vector<bool>* out);
	vector<bool> get_output() {return output;}
	Point Pos(){return pos;}
//protected:
	Canvas* Parent() {return parent;}
	void set_parent(Canvas* p) {parent = p;}
	//Gate(){};
};

//-----------------------------------------------------------------------

class And_Gate : public Gate {
	Gate* input1;
	Gate* input2;
	Fl_PNG_Image *AND;
	Canvas *parent;
public:
	//And_Gate(){}
	And_Gate(Point p, Gate* i1, Gate* i2, Canvas* pa);
	void draw();
	void cal_output();
};

//-----------------------------------------------------------------------

class Or_Gate : public Gate {
	Gate* input1;
	Gate* input2;
	Fl_PNG_Image *OR;
public:
	//Or_Gate(){}
	Or_Gate(Point p, Gate* i1, Gate* i2, Canvas* pa);
	void draw();
	void cal_output();
};

//-----------------------------------------------------------------------

class Not_Gate : public Gate {
	Gate* input1;
	Fl_PNG_Image *NOT;
public:
	//Not_Gate(){}
	Not_Gate(Point p, Gate* i1, Canvas* pa);
	void draw();
	void cal_output();
};

#endif