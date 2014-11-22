#include "Truth_Table.h"
using namespace std;

Canvas::Canvas(int X, int Y, int W, int H, Fl_Scroll* sc, const char*L): Fl_Widget(X,Y,W,H,L) {
	vector<bool> out;
	parent = sc;
	table = NULL;
	gui = NULL;
	accepted = true;
	
	bool out1[8] = {false,false,false,false,true,true,true,true };
	out.assign(&out1[0], &out1[0]+8);
	gates.push_back(new Gate(Point(64,48),&out,this));

	bool out2[8] = {false,false,true,true,false,false,true,true};
	out.assign(&out2[0], &out2[0]+8);
	gates.push_back(new Gate(Point(128,96),&out,this));
	
	bool out3[8] = {false,true,false,true,false,true,false,true};
	out.assign(&out3[0], &out3[0]+8);
	gates.push_back(new Gate(Point(192,144),&out,this));

}
void Canvas::add_gate(int gate, Gate* input1, Gate* input2) {
	Gate* last_gate = gates[gates.size()-1];
	switch (gate) {
		case 0 : gates.push_back(new And_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),input1,input2,this)); break;
		case 1 : gates.push_back(new Or_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),input1,input2,this)); break;
		default : break;
	}
}
void Canvas::add_gate(int gate, Gate* input) {
	Gate* last_gate = gates[gates.size()-1];
	switch (gate) {
		case 0 : gates.push_back(new Not_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),input,this)); break;
		default : break;
	}
}
void Canvas::add_gate(int gate) {
	parent->begin();
	Gate* last_gate = gates[gates.size()-1];
	switch (gate) {
		case 0 : 
			And_Gate* g;
			g = new And_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),gates[0],gates[1],this);
			gates.push_back(g);
			break;
		default : break;
	}
	parent->end();
}
void Canvas::draw() {
	if (table!= NULL){
		table->redraw();
	}
	fl_color(fl_rgb_color(255,249,234));
	fl_rectf(x(), y(), w(), h());
	
	for (int i=0;i<gates.size();++i) {
		fl_color(FL_BLACK);
		string s = "Gate " + to_string(i+1);
		fl_draw(s.c_str(), s.size(), (i+1)*64 + x()-32, ((i+1)*48)+y()+36);
		gates[i]->draw();
	}
	if (gui!= NULL){
		gui->draw();
	}
	//cout<<"Drawing Canvas"<< Fl_Widget::y()<< "\n";
}

void Canvas::generate_circuit() {
	//Create tertiary AND Gates for every (1) in the truth table.
	vector<bool> a = Gates()->operator[](0)->get_output();
	vector<bool> output;
	for (int i=0;i<8;++i) {
		output.push_back(get_gui()->get_input(i)->value());
	}
}