#ifndef HELPER
#define HELPER

#include "Classes.h"

using namespace std;

void resize(Canvas *ds);
void and_callback(Fl_Widget* widget, void*);
void or_callback(Fl_Widget* widget, void*);
void not_callback(Fl_Widget* widget, void*);
void check_callback(Fl_Widget* widget, void*);
void remove_callback(Fl_Widget* widget, void*);
void accept_callback(Fl_Widget* widget, void*);
int int_from_string(string s, int pos);
void createGates(const char* filepath, Canvas* canvas);
void load_callback(Fl_Widget* widget, void*);
int find_gate_id(Canvas* canvas, Gate* gate);
void save_callback(Fl_Widget* widget, void*);
void gen_callback(Fl_Widget* widget, void*);

#endif