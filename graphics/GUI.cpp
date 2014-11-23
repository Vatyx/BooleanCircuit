#include "Truth_Table.h"
using namespace std;

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

	check_button = new Button(W-96,Y+H/4,H/2,H,"Check");
	check_button->set_parent(this);
	((Fl_Button*)check_button)->callback((Fl_Callback*)check_callback);

	remove_button = new Button((H*10),Y + H/4,H/2,H,"Remove");
	remove_button->set_parent(this);
	((Fl_Button*)remove_button)->callback((Fl_Callback*)remove_callback);
	
	load_button = new Button((H*15)-H/2,Y + H/4,H/2,H,"Load");
	load_button->set_parent(this);
	((Fl_Button*)load_button)->callback((Fl_Callback*)load_callback);
	
	save_button = new Button((H*16),Y + H/4,H/2,H,"Save");
	save_button->set_parent(this);
	((Fl_Button*)save_button)->callback((Fl_Callback*)save_callback);
	
	gen_button = new Button((H*18)-H/2,Y + H/4,H/2,H,"Generate");
	gen_button->set_parent(this);
	((Fl_Button*)gen_button)->callback((Fl_Callback*)gen_callback);
	
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
	((Fl_Widget*)load_button)->redraw();
	((Fl_Widget*)save_button)->redraw();
	((Fl_Widget*)gen_button)->redraw();
	//for (int i=0;i<inputs.size();++i) {
		//inputs[i]->redraw();
	//}
	fl_color(fl_rgb_color(255,255,255));
	if (message.size()>0) {
		fl_draw(message.c_str(), (w()-64) - message.size()*12, y()+36);
		message = "";
	}
}