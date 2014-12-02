/*
   Canvas.cpp
   Steven G. Leal		November 23, 2014
   Ryan Meyers
   Sahil Dhanju
*/

//
// Handles the drawing of circuit gates.
//

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
void Canvas::add_gate(int gate, Gate* input1, Gate* input2) { //Handles adding And and Or gates
	Gate* last_gate = gates[gates.size()-1];
	switch (gate) {
		case 0 : gates.push_back(new And_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),input1,input2,this)); break;
		case 1 : gates.push_back(new Or_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),input1,input2,this)); break;
		default : break;
	}
	Resize();
}
void Canvas::add_gate(int gate, Gate* input) { //Handles adding Not gates
	Gate* last_gate = gates[gates.size()-1];
	switch (gate) {
		case 0 : gates.push_back(new Not_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),input,this)); break;
		default : break;
	}
	Resize();
}
void Canvas::add_gate(int gate) { // handles default gates
	Gate* last_gate = gates[gates.size()-1];
	switch (gate) {
		case 0 : 
			And_Gate* g;
			g = new And_Gate(Point(last_gate->Pos().x+64,last_gate->Pos().y+48),gates[0],gates[1],this);
			gates.push_back(g);
			break;
		default : break;
	}
	Resize();
}
void Canvas::draw() { //draws canvas
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
}

void Canvas::Resize() { // Resizes the canvas
	if (num_gates()>=9)
		Fl_Widget::size(parent->w() + 64*(num_gates()-9),parent->h() + 48*(num_gates()-9));
	if (parent->xposition() > (w() - parent->w())) {
		parent->scroll_to(w() - parent->w(), parent->yposition());
	}
	if (parent->yposition() > (h() - parent->h())) {
		parent->scroll_to(parent->xposition(), h() - parent->h());
	}
	
	if (num_gates()>=21)
	((Fl_Widget*)get_table())->size(get_table()->get_scroll()->w() + 64*(num_gates()-21),((Fl_Widget*)get_table())->h());

	if (get_table()->get_scroll()->xposition() > (get_table()->w() - get_table()->get_scroll()->w())) {
		get_table()->get_scroll()->scroll_to(get_table()->w() - get_table()->get_scroll()->w(), get_table()->get_scroll()->yposition());
	}

}

void Canvas::generate_circuit() {
	//Create tertiary AND Gates for every (1) in the truth table.
	vector<bool> a = Gates()->operator[](0)->get_output();
	vector<bool> b = Gates()->operator[](1)->get_output();
	vector<bool> c = Gates()->operator[](2)->get_output();
	
	vector<bool> output;
	for (int i=0;i<8;++i) { //check to see if inputs are valid
		int input;
		sscanf(get_gui()->get_input(i)->value(), "%d", &input);
		if (input<0 || input>1) {
			get_gui()->set_message("Bad Gate Input.");
			get_gui()->redraw();
			return;
		}
		output.push_back(input != 0);
	}
	
	while (Gates()->size()>3){//delete existing gates
		Gates()->erase(Gates()->end() - 1);
	}
	
	bool all_zeros = true; // Checks if all the inputs are zero
	for (auto i: output) { //    <------------ THIS IS WHERE WE USED AUTO
		if (i != 0) all_zeros = false; // 	   AND RANGED-BASED FOR LOOP
	}
	if (all_zeros) {
		add_gate(0,get_gate(2));
		add_gate(0,get_gate(2),get_gate(3));
		parent->redraw();
		get_table()->get_scroll()->redraw();
		return;
	}
	
	vector<bool> nots {false,false,false}; //Checks redundant creation of not gates
	vector<vector<int>> ands; //Determines the number of tertiary and gates required
	
	for (auto i: {0,1,2,3,4,5,6,7}) { //    <------------ THIS IS WHERE WE USED AUTO
		if (output[i]) { //                               AND RANGED-BASED FOR LOOP
			vector<int> g_positions = {0,0,0};
			if (!a[i]) {
				nots[0] = true;
				g_positions[0] = 3;
			}
			else {
				g_positions[0] = 0;
			}
			if (!b[i]) {
				nots[1] = true;
				g_positions[1] = 4;
			}
			else {
				g_positions[1] = 1;
			}
			if (!c[i]) {
				nots[2] = true;
				g_positions[2] = 5;
			}
			else {
				g_positions[2] = 2;
			}	
			ands.push_back(g_positions);
		}
	}

	int num_nots = 0;
	for (int i=0;i<3; ++i) { //Generates not gates
		if (nots[i] == true) {
			add_gate(0,get_gate(i));
			++num_nots;
		}
	}
	
	for (int i=0;i<ands.size();++i) { // Generates Tertiary And gates
		if (ands[i][1] == 4 && nots[0] == false)
			add_gate(0,get_gate(ands[i][0]),get_gate(3));
		else if (ands[i][1] == 4 && nots[0] == true)
			add_gate(0,get_gate(ands[i][0]),get_gate(4));
		else 
			add_gate(0,get_gate(ands[i][0]),get_gate(1));
		
		if (ands[i][2] == 2)
			add_gate(0,get_gate(3+num_nots+(i*2)),get_gate(2));
		else
			add_gate(0,get_gate(3+num_nots+(i*2)),get_gate(ands[i][2] - (3-num_nots)));
	}
	if (ands.size()>1) {
		add_gate(1,get_gate(4+num_nots),get_gate(6+num_nots)); //Generates ending Or gates
	}
	for (int i=2;i<ands.size();++i) {
		add_gate(1,get_gate(2+num_nots+((i+1)*2)),get_gate(num_gates()-1));
	}
	parent->redraw();
	get_table()->get_scroll()->redraw();
}



