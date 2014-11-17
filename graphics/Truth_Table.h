#ifndef TRUTH
#define TRUTH

#include "GUI.h"
using namespace std;

class Truth_Table : public Fl_Widget {
	Canvas* parent;
	Fl_Scroll* scroll;
public:
	Truth_Table(int x, int y, int w, int h, Canvas* p, const char* L=0);
	void draw();
	void set_parent(Canvas* p);
	Canvas* Parent() {return parent;};
	void set_scroll(Fl_Scroll* s){scroll = s;}
	Fl_Scroll* get_scroll() {return scroll;}
};

#endif