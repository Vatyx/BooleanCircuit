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

int int_from_string(string s, int pos) {
	int output = 0;
	bool reading = false;
	int reading_point = 0;

	for (int i=0; i<pos; ++i) {
		for (int j=reading_point; j<s.size(); ++j) {
			if (isdigit(s[j])) {
				reading = true;
			}
			else {
				if (reading) {
					reading_point = j;
					reading = false;
					break;
				}
			}
		}
	}
	for (int i=reading_point; i<s.size(); ++i) {
		if (isdigit(s[i])) {
			int digit = s[i]- 48;
			output = output*10 + digit;
			reading = true;
		}
		else {
			if (reading) {
				break;
			}
		}
		
	}
	return output-1;
}

void createGates(const char* filepath, Canvas* canvas) {
	string line;
	int a,b;
	ifstream data_in;
	data_in.open(filepath);
	
	while (getline(data_in,line)) {
		a = int_from_string(line, 0);
		b = int_from_string(line, 1);
		switch(line[0]) {
			case 'A':
				canvas->add_gate(0, canvas->Gates()->operator[](a), canvas->Gates()->operator[](b));
				break;
			case 'O':
				canvas->add_gate(1, canvas->Gates()->operator[](a), canvas->Gates()->operator[](b));
				break;
			case 'N':
				canvas->add_gate(0, canvas->Gates()->operator[](a));
				break;
		}
		resize(canvas,true);
    }
	canvas->Parent()->redraw();
	canvas->get_table()->get_scroll()->redraw();
}

void load_callback(Fl_Widget* widget, void*) {
	Canvas* ds = ((Button*)widget)->Parent()->Parent();
	Fl_File_Chooser chooser(".", "*.txt", Fl_File_Chooser::SINGLE, "Title Of Chooser");
	chooser.show();
	while(chooser.shown())
		{ Fl::wait(); }

    if ( chooser.value() == NULL )
		{ cout<<"User hit Cancel\n"; return; }
	const char* s = chooser.value(0);
	while (ds->Gates()->size()>3){
		resize(ds,false);
		ds->Gates()->erase(ds->Gates()->end() - 1);
	}
	createGates(s,ds);
	ds->get_gui()->set_message("Loading Complete");
	ds->get_gui()->redraw();
}

int find_gate_id(Canvas* canvas, Gate* gate) {
	for (int i=0; i < canvas->Gates()->size(); ++i) {
		if (gate == canvas->Gates()->operator[](i)) {
			return i+1;
		}
	}
	return -1;
}

void save_callback(Fl_Widget* widget, void*) {
	Canvas* ds = ((Button*)widget)->Parent()->Parent();
	
	const char* path = fl_file_chooser("Enter name and directory", "*.txt","Goober.txt",0);
	cout << path<<"\n";
	
	ofstream file;
	file.open (path, std::fstream::trunc);
	for (int i=3;i<ds->Gates()->size();++i) {
		if (dynamic_cast<And_Gate*>(ds->Gates()->operator[](i))) {
			int in1 = find_gate_id(ds,(((And_Gate*)(ds->Gates()->operator[](i)))->get_input1()));
			int in2 = find_gate_id(ds,(((And_Gate*)(ds->Gates()->operator[](i)))->get_input2()));
			file<<"AND(" << in1 << "," << in2 << ")\r\n";
		}
		else if (dynamic_cast<Or_Gate*>(ds->Gates()->operator[](i))) {
			int in1 = find_gate_id(ds,(((Or_Gate*)(ds->Gates()->operator[](i)))->get_input1()));
			int in2 = find_gate_id(ds,(((Or_Gate*)(ds->Gates()->operator[](i)))->get_input2()));
			file<<"OR(" << in1 << "," << in2 << ")\r\n";
		}
		else if (dynamic_cast<Not_Gate*>(ds->Gates()->operator[](i))) {
			int in1 = find_gate_id(ds,(((Not_Gate*)(ds->Gates()->operator[](i)))->get_input1()));
			file<<"NOT(" << in1 << ")\r\n";
		}
	}
	//fl_message("Saving Complete.");
	ds->get_gui()->set_message("Saving Complete");
	ds->get_gui()->redraw();
	file.close();
}

void gen_callback(Fl_Widget* widget, void*) {
	
	Canvas* canvas = ((Button*)widget)->Parent()->Parent();
	GUI* gui = ((Button*)widget)->Parent();
	Gate* last_gate = canvas->Gates()->operator[](canvas->Gates()->size()-1);
	vector<bool> last_output = last_gate->get_output();
	
	for (int i=0;i<8;i++) {
		string input = gui->get_input(i)->value();
		if (!(input == "0" || input == "1")){
			gui->set_message("Bad Input.");
			gui->redraw();
			return;
		}
	}
	gui->set_message("Correct!");
	canvas->generate_circuit();
	gui->redraw();
}