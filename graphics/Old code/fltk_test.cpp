/*
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
#include <vector>
#include "Gate.h"



using namespace std;

class DrawStuff : public Fl_Widget {
	And_Gate ag;
	vector<Gate*> gates;
	
public:
    DrawStuff(int X, int Y, int W, int H, const char*L=0) : Fl_Widget(X,Y,W,H,L) {
		gates.push_back(new Gate(Point(0,0),0));
		gates.push_back(new Gate(Point(64,48),1));
		gates.push_back(new And_Gate(Point(128,96),*gates[0],*gates[1],2));
    }
    void draw() {
		
		fl_color(fl_rgb_color(255,249,234));
		fl_rectf(x(), y(), w(), h());
		
        fl_color(FL_BLACK);
        int x1 = x(),       y1 = y();
        int x2 = x()+w()-1, y2 = y()+h()-1;
		
		int bot_bar_h = 48;
		int top_win_h = (y2 - bot_bar_h)*(3.0/4.0);
		int bot_win_h = (y2 - bot_bar_h) - top_win_h;
		
		double char_offset = (x2/92.0);
		
		for (int i=1; i<= 23; i++) {
			fl_line(((i-1)*x2)/23.0 + char_offset, (i*top_win_h)/24.0, x2, (i*top_win_h)/24.0);
		}
		
		for (int i=4; i< 23; i++) {
			fl_line((i*x2)/23.0, 0, (i*x2)/23.0, bot_win_h+top_win_h);
		}
		
		fl_line_style(FL_SOLID, 4);
		fl_line(0, top_win_h, x2, top_win_h);
		fl_line(0, bot_win_h+top_win_h, x2, bot_win_h+top_win_h);
		fl_line(3*(x2/23), 0, 3*(x2/23), bot_win_h+top_win_h);
		
		char a = 'A';
		const char* c = &a;
		
		for (int i=1; i<= 23; i++) {
			fl_draw(c, 1,((i-1)*x2)/23.0 + 1, (i*top_win_h)/24.0);
			a += 1;
		}
		
		for (int i=1; i<= 23; i++) {
			for (int j=1; j<= 8; j++) {
				fl_draw("0",((i-1)*x2)/23.0 + char_offset, ((j*bot_win_h)/8.0)+top_win_h - 3);
			}
		}
		for (int i=0;i<gates.size();++i) {
			gates[i]->draw();
		}
    }
};

int main() {
    Fl_Double_Window win(1600,900,"Draw X");
    DrawStuff draw_x(0, 0, win.w(), win.h());
    win.resizable(draw_x);
    win.show();
    return(Fl::run());
}
*/