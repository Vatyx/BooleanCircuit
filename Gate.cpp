#include "Gate.h"

	void Gate::calculate_output()
	{
		auto t = get_type();
		vector<int> ou (8);
		for (int i = 0; i < 8; ++i)
		{
			switch (t)
			{
			case 'a':
				ou[i] = ((total_gates[get_first_input()].get_output()[i]) && (total_gates[get_second_input()].get_output()[i]));
				break;
			case 'o':
				ou[i] = (total_gates[get_first_input()].get_output()[i] || total_gates[get_second_input()].get_output()[i]);
				break;
			case 'n':
				ou[i] = !(total_gates[get_first_input()].get_output()[i]);
				break;
			}

		}
		
		set_output(ou);
	}

	void print_all_gates()
	{
		for (int i = 0; i < 8; ++i)
		{
			int counter = 0;
			for (string n : gate_names)
			{		
				cout << total_gates[n].get_output()[i];
				if (counter > 1)
					cout << "\t";
				else
					cout << " ";
				++counter;
			}
			cout << endl;
		}
	}
	
	/* int main(){
	return 0;} */
