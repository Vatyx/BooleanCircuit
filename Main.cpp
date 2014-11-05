#include "Gate.cpp"

//using namespace BooleanGate;

int main()
{
	//put the first 3 inputs into the map to be able to access.
	Gate a{ 'd', "A", A_OUTPUT };
	gate_names.push_back("A");
	total_gates["A"] = a;
	
	Gate b{ 'd', "B", B_OUTPUT };
	gate_names.push_back("B");
	total_gates["B"] = b;
	
	Gate c{ 'd', "C", C_OUTPUT };
	gate_names.push_back("C");
	total_gates["C"] = c;

	int gate_added_counter = 1;
	while (true)
	{
		cout << "Please enter the gate you want to add (and, or, not) and the input(s) for the gate (format: Type first_input second_input): ";
		string input_t;
		string input_f;
		string input_s;
		cin >> input_t >> input_f >> input_s;

		string created_name;
		switch (input_t[0])
		{
		case 'a':
			created_name += "AND";
			break;
		case 'o':
			created_name += "OR";
			break;
		case 'n':
			created_name += "NOT";
			break;
		}
		ostringstream convert;   // stream used for the conversion
		convert << gate_added_counter;      // insert the textual representation of 'Number' in the characters in the stream
		created_name += convert.str();
		cout << "This gate's name is " << created_name << endl;
		gate_names.push_back(created_name);

		Gate g{ input_t[0], created_name, input_f, input_s };
		g.calculate_output();
		total_gates[created_name] = g;
		

		print_all_gates();
	
		++gate_added_counter;
		
		cout << endl << endl;
	}

	return 0;
}