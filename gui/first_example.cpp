#include "Graph_lib/Simple_window.h"
#include "Graph_lib/Graph.h"


#include <vector>

using namespace std;
using namespace Graph_lib;

struct Lines_Window : Window
{
	Lines_Window(Point xy, int w, int h, const string &title);
	Open_polyline lines;

private:
	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;

	void next();
	void quit();
};

Lines_Window::Lines_Window(Point xy, int w, int h, const string &title)
	: Window{xy, w, h, title},
	next_button{Point{x_max()-150, 0}, 70, 20, "Next Point",
		[](Address, Address pw) { reference_to<Lines_Window>(pw).next(); }},
	quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<Lines_Window>(pw).quit(); }},
	next_x{Point{x_max() - 310, 0}, 50, 20, "next x:"},
	next_y{Point{x_max() - 210, 0}, 50, 20, "next y:"},
	xy_out{Point{100, 0}, 100, 20, "current (x, y):"}
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	attach(lines);
}

void Lines_Window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();

	lines.add(Point{x, y});

	ostringstream ss;
	ss << '(' << x << " ," << y << ')';
	xy_out.put(ss.str());

	redraw();
}

void Lines_Window::quit()
{
	hide();
}

int main()
{
	try {
		Lines_Window win {Point{100, 100}, 600, 400, "lines"};
		return gui_main();
	}
	catch (exception &e) {
		cerr << "exception: " << e.what() << "\n";
		return 1;
	}
	catch (...) {
		cerr << "Some Exception\n";
		return 2;
	}
}
