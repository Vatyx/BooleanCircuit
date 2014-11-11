#include "GUI.h"

using namespace std;

void and_callback(Fl_Widget* widget, void*) {
	GUI* gui = ((Button*)widget)->Parent();
	gui->set_gate_button(1);
	gui->Input2()->show();
	gui->Input1()->label("AND In1");
	gui->Input2()->label("AND In2");
	gui->Parent()->Parent()->redraw();
}

void or_callback(Fl_Widget* widget, void*) {
	GUI* gui = ((Button*)widget)->Parent();
	gui->set_gate_button(2);
	gui->Input2()->show();
	gui->Input1()->label("OR In1");
	gui->Input2()->label("OR In2");
	gui->Parent()->Parent()->redraw();
}

void not_callback(Fl_Widget* widget, void*) {
	GUI* gui = ((Button*)widget)->Parent();
	gui->set_gate_button(3);
	gui->Input2()->hide();
	gui->Input1()->label("NOT In1");
	gui->Parent()->Parent()->redraw();
}

void accept_callback(Fl_Widget* widget, void*) {
	GUI* gui = ((Button*)widget)->Parent();
	int button = gui->get_gate_button();
	int i1;
	sscanf(gui->Input1()->value(), "%d", &i1);
	int i2;
	sscanf(gui->Input2()->value(), "%d", &i2);

	if (button<1 || button>3) {
		cout<<"Need to select Gate-Button\n";
		return;
	}
	switch(button) {
		case 1:
			if (i1==0 || gui->Parent()->num_gates() < i1) {
				cout<<"Bad Input1\n";
				return;
			}
			if (i2==0 || gui->Parent()->num_gates() < i2) {
				cout<<"Bad Input2\n";
				return;
			}
			gui->Parent()->add_gate(0,gui->Parent()->Gates()[i1-1],gui->Parent()->Gates()[i2-1]);
			gui->Parent()->Parent()->redraw();
			break;
		case 2:
			if (i1==0 || gui->Parent()->num_gates() < i1) {
				cout<<"Bad Input1\n";
				return;
			}
			if (i2==0 || gui->Parent()->num_gates() < i2) {
				cout<<"Bad Input2\n";
				return;
			}
			gui->Parent()->add_gate(1,gui->Parent()->Gates()[i1-1],gui->Parent()->Gates()[i2-1]);
			gui->Parent()->Parent()->redraw();
			break;
		case 3:
			if (i1==0 || gui->Parent()->num_gates() < i1) {
				cout<<"Bad Input\n";
				return;
			}
			
			gui->Parent()->add_gate(0,gui->Parent()->Gates()[i1-1]);
			gui->Parent()->Parent()->redraw();
			break;
		default: break;
	}
}

GUI::GUI(int sw, int sh) {
	gate_button = 0;
	height = 64;
	and_button = new Button(0,sh-height,height,height,"AND");
	and_button->set_parent(this);
	((Fl_Button*)and_button)->callback((Fl_Callback*)and_callback);
	
	or_button = new Button(height,sh-height,height,height,"OR");
	or_button->set_parent(this);
	((Fl_Button*)or_button)->callback((Fl_Callback*)or_callback);
	
	not_button = new Button(height*2,sh-height,height,height,"NOT");
	not_button->set_parent(this);
	((Fl_Button*)not_button)->callback((Fl_Callback*)not_callback);
	
	input1 = new Fl_Input(height*4,sh-height,height,height/2,"Input1");
	input2 = new Fl_Input(height*6,sh-height,height,height/2,"Input2");
	
	accept_button = new Button(height*8,sh-height + height/4,height/2,height,"Accept");
	accept_button->set_parent(this);
	((Fl_Button*)accept_button)->callback((Fl_Callback*)accept_callback);
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

	gui = new GUI(w(),h());
	gui->set_parent(this);
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

void DrawStuff::add_gate(int gate) {
	Gate* last_gate = gates[gates.size()-1];
	switch (gate) {
		case 0 : gates.push_back(new And_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),gates[0],gates[1])); break;
		default : break;
	}
	//DrawStuff::Parent()->redraw();
}

void DrawStuff::draw() {
	fl_color(fl_rgb_color(255,249,234));
	fl_rectf(x(), y(), w(), h());
	
	for (int i=0;i<gates.size();++i) {
		gates[i]->draw();
	}
	//gui->draw();
}