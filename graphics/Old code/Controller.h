
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

class Controller : public Fl_Widget {
	And_Gate ag;
	GUI*  gui;
	vector<Gate*> gates;
	
public:
    Controller(int X, int Y, int W, int H, const char*L=0) : Fl_Widget(X,Y,W,H,L) {
		vector<bool> out;
		bool out1[8] = {false,false,false,false,true,true,true,true };
		out.assign(&out1[0], &out1[0]+8);
		gates.push_back(new Gate(Point(64,48),&out));
		
		bool out2[8] = {false,false,true,true,false,false,true,true};
		out.assign(&out2[0], &out2[0]+8);
		gates.push_back(new Gate(Point(128,96),&out));
		
		bool out3[8] = {false,true,false,true,false,true,false,true};
		out.assign(&out3[0], &out3[0]+8);
		gates.push_back(new Gate(Point(192,144),&out));
		
		gates.push_back(new And_Gate(Point(256,192),gates[0],gates[1]));
		gates.push_back(new And_Gate(Point(320,240),gates[2],gates[3]));
		gates.push_back(new Not_Gate(Point(384,288),gates[3]));
		gates.push_back(new Or_Gate(Point(448,336),gates[2],gates[3]));
		
		cout << w() << "\n" << h() << "\n";
		gui = new GUI(this,w(),h());
    }
    void draw() {
		
		fl_color(fl_rgb_color(255,249,234));
		fl_rectf(x(), y(), w(), h());
		
		for (int i=0;i<gates.size();++i) {
			gates[i]->draw();
		}
		gui->draw();
    }
};

