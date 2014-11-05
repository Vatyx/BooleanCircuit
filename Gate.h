#include "std_lib_facilities_4.h"
#include <map>

using namespace std;

	const vector<int> A_OUTPUT = { 0, 0, 0, 0, 1, 1, 1, 1 };
	const vector<int> B_OUTPUT = { 0, 0, 1, 1, 0, 0, 1, 1 };
	const vector<int> C_OUTPUT = { 0, 1, 0, 1, 0, 1, 0, 1 };
	
	vector<string> gate_names;
	
	class Gate
	{
	private:
		char type;	//type can be: a: and, o: or, n: not, d: default (inital input, a, b, c)
		string name;
		string first_input, second_input;
		vector<int> output;

	public:
		Gate(char t, string n, string fi, string si) { type = t; name = n; first_input = fi; second_input = si; };
		Gate(char t, string n, string fi) { type = t; name = n; first_input = fi; }; //for the not gate. Should only have one input
		Gate(char t, string n, vector<int> o) { type = t; name = n; output = o; };
		Gate() { type = 'd', name = "default"; };

		char get_type() { return type; }
		string get_name() { return name; }
		string get_first_input() { return first_input; }
		string get_second_input() { return second_input; }
		vector<int> get_output() { return output; }

		void set_type(char t) { type = t; }
		void set_name(string n){ name = n; }
		void set_first_input(string fi) { first_input = fi; }
		void set_second_input(string si) { second_input = si; }
		void set_output(vector<int> o) { output = o; }

		void calculate_output();
		
	};
	
	//vector<string> gate_names;
	map<string, Gate> total_gates;
	
	void print_all_gates();

