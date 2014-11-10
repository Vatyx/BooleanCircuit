#include "GUI.h"

using namespace std;

void and_callback(Fl_Widget* widget, void*) {
    ((Fl_Button*)widget)->hide();
}

GUI::GUI(int sw, int sh) {
	height = 64;
	and_button = new Fl_Button(0,sh-height,height,height,"AND");
	and_button->callback((Fl_Callback*)and_callback);
	or_button = new Fl_Button(height,sh-height,height,height,"OR");
	not_button = new Fl_Button(height*2,sh-height,height,height,"NOT");
}

DrawStuff::DrawStuff(int X, int Y, int W, int H, const char*L) : Fl_Widget(X,Y,W,H,L) {
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
	
	add_gate(0,gates[0],gates[1]);
	
	cout << w() << "\n" << h() << "\n";
	gui = new GUI(w(),h());
}

void DrawStuff::add_gate(int gate, Gate* input1, Gate* input2) {
	Gate* last_gate = gates[gates.size()-1];
	switch (gate) {
		case 0 : gates.push_back(new And_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),input1,input2)); break;
		case 1 : gates.push_back(new Or_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),input1,input2)); break;
		default : break;
	}
}

void DrawStuff::add_gate(int gate, Gate* input) {
	Gate* last_gate = gates[gates.size()-1];
	switch (gate) {
		case 0 : gates.push_back(new Not_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),input)); break;
		default : break;
	}
}

void DrawStuff::draw() {
	
	fl_color(fl_rgb_color(255,249,234));
	fl_rectf(x(), y(), w(), h());
	
	for (int i=0;i<gates.size();++i) {
		gates[i]->draw();
	}
	//gui->draw();
}