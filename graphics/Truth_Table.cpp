#include "Truth_Table.h"

using namespace std;

Truth_Table::Truth_Table(int x, int y, int w, int h, Canvas* p, const char* L) : Fl_Widget(x,y,w,h,L) {
	parent = p;
	//size(p->w()+1,this->h());

}
void Truth_Table::draw() {

	fl_color(fl_rgb_color(255,255,255));
	fl_rectf(x(), y(), w(), h());

	vector<Gate*>* gates = Parent()->Gates();
	for (int i=0;i<gates->size();++i) {
		vector<bool> output = (*gates)[i]->get_output();
		
		if (gates->size() > 3 && i == gates->size()-1 && Parent()->Accepted() == false)
			fl_color(fl_rgb_color(255,0,0));
		else if (gates->size() > 3 && i == gates->size()-1)
			fl_color(fl_rgb_color(255,255,0));
		else if (i%2 == 1)
			fl_color(fl_rgb_color(220,220,220));
		else
			fl_color(fl_rgb_color(180,180,180));
			
		fl_rectf(x() + (i+1)*64 - 6 , y() + 4, 56 , h() - 28);
		
		fl_color(FL_BLACK);
		
		string s = "Gate " + to_string(i+1);
		fl_draw(s.c_str(), s.size(), (i+1)*64 + x() - 4, y()+24);
		
		char a = 'A';
		for (int j=1; j<= output.size(); j++) {
			if (output[j-1]) {
				a='1';
			}
			else {
				a='0';
			}
			fl_draw(&a, 1, (i+1)*64+this->x(), y()+((j+1)*24));
		}
	}
}