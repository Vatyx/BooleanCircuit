#ifndef ADD_H
#define ADD_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include "string"
#include <vector>
#include <iostream>

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


class Gate {
	Point pos;
	vector<bool> output;
public:
	Gate(Point p) {//Constructor
		pos = p;
	}
	Gate(Point p, vector<bool>* out) {//Constructor
		pos = p;
		for (int i=0;i< (*out).size();++i) {
			output.push_back((*out)[i]);
		}
	}
	virtual void draw() {
		fl_color(fl_rgb_color(25,218,255));
		fl_line_style(FL_SOLID, 4);
		fl_line(pos.x, pos.y, Fl::w()-1, pos.y);
		draw_output();
	}
	void draw_output() {
		fl_color(FL_BLACK);
		char a = 'A';
		for (int i=0; i< output.size(); i++) {
			if (output[i]) {
				
				a='1';
			}
			else {
				a='0';
			}
			fl_draw(&a, 1, pos.x, (Fl::h()/2)+((i+1)*16));
		}
	}
	void set_output(vector<bool>* out) {
		for (int i=0;i< (*out).size();++i) {
			output.push_back((*out)[i]);
		}
	}
	vector<bool> get_output() {return output;}
	Point Pos(){return pos;}
//protected:
	Gate(){};
};

class And_Gate : public Gate {
	Gate* input1;
	Gate* input2;
	Fl_PNG_Image *AND;
public:
	And_Gate(){}
	And_Gate(Point p, Gate* i1, Gate* i2): Gate(p) {
		input1 = i1;
		input2 = i2;
		AND  = new Fl_PNG_Image("./Gate_icons/And_Gate.png");
	}
	virtual void draw() {
		cal_output();
		Gate::draw_output();
		
		fl_color(fl_rgb_color(255,178,0));
		fl_line_style(FL_SOLID, 4);
		fl_line(Gate::Pos().x, Gate::Pos().y, Fl::w()-1, Gate::Pos().y);//Draw wire
		
		fl_color(fl_rgb_color(255,0,0));
		fl_line_style(FL_SOLID, 2);
		fl_line(Gate::Pos().x-23, Gate::Pos().y-3, Gate::Pos().x-23, (*input1).Pos().y);//Draw input1 wire
		
		fl_color(fl_rgb_color(0,190,0));
		fl_line_style(FL_SOLID, 2);
		fl_line(Gate::Pos().x-29, Gate::Pos().y+4, Gate::Pos().x-29, (*input2).Pos().y);//Draw input1 wire
		
		AND->draw(Gate::Pos().x-(AND->w()/2),Gate::Pos().y-(AND->h()/2)); //Draw Gate
		
	}
	
	void cal_output() {
		vector<bool> outputs;
		for (int i=0; i<(*input1).get_output().size(); i++) {
			outputs.push_back((*input1).get_output()[i]&&(*input2).get_output()[i]);
		}
		Gate::set_output(&outputs);
	}
};

class Or_Gate : public Gate {
	Gate* input1;
	Gate* input2;
	Fl_PNG_Image *OR;
public:
	Or_Gate(){}
	Or_Gate(Point p, Gate* i1, Gate* i2): Gate(p) {
		input1 = i1;
		input2 = i2;
		OR  = new Fl_PNG_Image("./Gate_icons/Or_Gate.png");
	}
	virtual void draw() {
		cal_output();
		Gate::draw_output();
		
		fl_color(fl_rgb_color(24,202,237));
		fl_line_style(FL_SOLID, 4);
		fl_line(Gate::Pos().x, Gate::Pos().y, Fl::w()-1, Gate::Pos().y);//Draw wire
		
		fl_color(fl_rgb_color(255,0,0));
		fl_line_style(FL_SOLID, 2);
		fl_line(Gate::Pos().x-19, Gate::Pos().y-4, Gate::Pos().x-19, (*input1).Pos().y);//Draw input1 wire
		
		fl_color(fl_rgb_color(0,190,0));
		fl_line_style(FL_SOLID, 2);
		fl_line(Gate::Pos().x-29, Gate::Pos().y+5, Gate::Pos().x-29, (*input2).Pos().y);//Draw input1 wire
		
		OR->draw(Gate::Pos().x-(OR->w()/2),Gate::Pos().y-(OR->h()/2)); //Draw Gate
		
	}
	void cal_output() {
		vector<bool> outputs;
		for (int i=0; i<(*input1).get_output().size(); i++) {
			outputs.push_back((*input1).get_output()[i]||(*input2).get_output()[i]);
		}
		Gate::set_output(&outputs);
	}
};

class Not_Gate : public Gate {
	Gate* input1;
	Fl_PNG_Image *NOT;
public:
	Not_Gate(){}
	Not_Gate(Point p, Gate* i1): Gate(p) {
		input1 = i1;
		NOT = new Fl_PNG_Image("./Gate_icons/Not_Gate.png");
	}
	virtual void draw() {
		cal_output();
		Gate::draw_output();
		
		fl_color(fl_rgb_color(84,79,34));
		fl_line_style(FL_SOLID, 4);
		fl_line(Gate::Pos().x, Gate::Pos().y, Fl::w()-1, Gate::Pos().y);//Draw wire
		
		fl_color(fl_rgb_color(255,0,0));
		fl_line_style(FL_SOLID, 2);
		fl_line(Gate::Pos().x-29, Gate::Pos().y, Gate::Pos().x-29, (*input1).Pos().y);//Draw input1 wire
		
		NOT->draw(Gate::Pos().x-(NOT->w()/2),Gate::Pos().y-(NOT->h()/2)); //Draw Gate
		
	}
	void cal_output() {
		vector<bool> outputs;
		for (int i=0; i<(*input1).get_output().size(); i++) {
			outputs.push_back(!(*input1).get_output()[i]);
		}
		Gate::set_output(&outputs);
	}
};
#endif