#include "Truth_Table.h"

using namespace std;

void resize(Canvas *ds, bool dir) {
	if (ds->Gates()->size() > 9) {
		if (dir) {
			((Fl_Widget*)ds)->size(((Fl_Widget*)ds)->w()+64,((Fl_Widget*)ds)->h()+48);
		}
		else {
			((Fl_Widget*)ds)->size(((Fl_Widget*)ds)->w()-64,((Fl_Widget*)ds)->h()-48);
			if (ds->Parent()->xposition() > (ds->w() - ds->Parent()->w())) {
				ds->Parent()->scroll_to(ds->w() - ds->Parent()->w(), ds->Parent()->yposition());
			}
			if (ds->Parent()->yposition() > (ds->h() - ds->Parent()->h())) {
				ds->Parent()->scroll_to(ds->Parent()->xposition(), ds->h() - ds->Parent()->h());
			}
		}
	}
	if (ds->Gates()->size() > 21) {
		Truth_Table* table = ds->get_table();
		if (dir) {
			((Fl_Widget*)table)->size(((Fl_Widget*)table)->w()+64,((Fl_Widget*)table)->h());
		}
		else {
			((Fl_Widget*)table)->size(((Fl_Widget*)table)->w()-64,((Fl_Widget*)table)->h());
			if (table->get_scroll()->xposition() > (table->w() - table->get_scroll()->w())) {
				table->get_scroll()->scroll_to(table->w() - table->get_scroll()->w(), table->get_scroll()->yposition());
			}
		}
	}
}

void and_callback(Fl_Widget* widget, void*) {
	GUI* gui = ((Button*)widget)->Parent();
	gui->set_gate_button(1);
	gui->Input2()->show();
	gui->Input1()->label("AND In1");
	gui->Input2()->label("AND In2");
	gui->redraw();
}

void or_callback(Fl_Widget* widget, void*) {
	GUI* gui = ((Button*)widget)->Parent();
	gui->set_gate_button(2);
	gui->Input2()->show();
	gui->Input1()->label("OR In1");
	gui->Input2()->label("OR In2");
	gui->redraw();
}

void not_callback(Fl_Widget* widget, void*) {
	GUI* gui = ((Button*)widget)->Parent();
	gui->set_gate_button(3);
	gui->Input2()->hide();
	gui->Input1()->label("NOT In");
	gui->redraw();
}

void check_callback(Fl_Widget* widget, void*) {
	
	Canvas* ds = ((Button*)widget)->Parent()->Parent();
	GUI* gui = ((Button*)widget)->Parent();
	Gate* last_gate = ds->Gates()->operator[](ds->Gates()->size()-1);
	vector<bool> last_output = last_gate->get_output();
	
	for (int i=0;i<8;i++) {
		string input = gui->get_input(i)->value();
		bool in = false;
		if (input == "0"){
			in = false;}
		else if (input == "1"){
			in = true;}
		else {
			gui->set_message("Bad Input.");
			gui->redraw();
			return;
		}
		if (in != last_output[i]) {
			gui->set_message("Incorrect.");
			gui->redraw();
			return;
		}
	}
	gui->set_message("Correct!");
	gui->redraw();
}

void remove_callback(Fl_Widget* widget, void*) {
	Canvas* ds = ((Button*)widget)->Parent()->Parent();
	resize(ds,false);
	if (ds->Gates()->size()>3)
		ds->Gates()->erase(ds->Gates()->end() - 1);
	ds->get_table()->get_scroll()->redraw();
	ds->Parent()->redraw();
}

void accept_callback(Fl_Widget* widget, void*) {
	GUI* gui = ((Button*)widget)->Parent();
	//Canvas* ds = gui->Parent();
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
			gui->Parent()->add_gate(0,gui->Parent()->Gates()->operator[](i1-1),gui->Parent()->Gates()->operator[](i2-1));
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
			gui->Parent()->add_gate(1,gui->Parent()->Gates()->operator[](i1-1),gui->Parent()->Gates()->operator[](i2-1));
			break;
		case 3:
			if (i1==0 || gui->Parent()->num_gates() < i1) {
				cout<<"Bad Input\n";
				return;
			}
			gui->Parent()->add_gate(0,gui->Parent()->Gates()->operator[](i1-1));
			break;
		default: break;
	}
	resize(gui->Parent(),true);
	gui->Parent()->get_table()->get_scroll()->redraw();
	gui->Parent()->Parent()->redraw();
}

//-----------------------------------------------------------------------

GUI::GUI(int X, int Y, int W, int H, const char*L) : Fl_Widget(X,Y,W,H,L){
	gate_button = 0;

	and_button = new Button(0,Y,H,H,"AND");
	and_button->set_parent(this);
	((Fl_Button*)and_button)->callback((Fl_Callback*)and_callback);
	
	or_button = new Button(H,Y,H,H,"OR");
	or_button->set_parent(this);
	((Fl_Button*)or_button)->callback((Fl_Callback*)or_callback);
	
	not_button = new Button(H*2,Y,H,H,"NOT");
	not_button->set_parent(this);
	((Fl_Button*)not_button)->callback((Fl_Callback*)not_callback);
	
	input1 = new Fl_Input(H*4 + H/2,Y + H/4,H,H/2,"Input1");
	input2 = new Fl_Input(H*7,Y + H/4,H,H/2,"Input2");
	
	accept_button = new Button((H*9)-H/2,Y+H/4,H/2,H,"Accept");
	accept_button->set_parent(this);
	((Fl_Button*)accept_button)->callback((Fl_Callback*)accept_callback);

	check_button = new Button(W-192,Y+H/4,H/2,H,"Check");
	check_button->set_parent(this);
	((Fl_Button*)check_button)->callback((Fl_Callback*)check_callback);

	remove_button = new Button((H*10),Y + H/4,H/2,H,"Remove");
	remove_button->set_parent(this);
	((Fl_Button*)remove_button)->callback((Fl_Callback*)remove_callback);
	
	int yy = 500;
	int ww = 1600;
	int hh = 300;
	for (int i=0;i<8;++i) {
		//string s = "Input " + to_string(i+1);
		Fl_Input* input = new Fl_Input(ww-64,i*((int)(hh/8.0)) + yy,64,(int)(hh/8.0),"");
		inputs.push_back(input);
	}
}

void GUI::draw() {
	fl_color(fl_rgb_color(128,128,128));
	fl_rectf(x(), y(), w(), h());
	((Fl_Widget*)and_button)->redraw();
	((Fl_Widget*)not_button)->redraw();
	((Fl_Widget*)or_button)->redraw();
	input1->redraw();
	input2->redraw();
	((Fl_Widget*)accept_button)->redraw();
	((Fl_Widget*)remove_button)->redraw();
	((Fl_Widget*)check_button)->redraw();
	//for (int i=0;i<inputs.size();++i) {
		//inputs[i]->redraw();
	//}
	fl_color(fl_rgb_color(255,255,255));
	fl_draw(message.c_str(), w()-92, y()+32);
}

//-----------------------------------------------------------------------

Canvas::Canvas(int X, int Y, int W, int H, Fl_Scroll* sc, const char*L): Fl_Widget(X,Y,W,H,L) {
	vector<bool> out;
	parent = sc;
	table = NULL;
	gui = NULL;
	
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