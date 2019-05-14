#include "Graph_lib/Simple_window.h"
#include "Graph_lib/Graph.h"


#include <vector>

using namespace std;
using namespace Graph_lib;

struct Lines_Window : Window
{
	Lines_Window(Point xy, int w, int h, const string &title);

private:
	Open_polyline lines;

	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;
	Button menu_button;
	Menu color_menu;

	void change(Color c) { lines.set_color(c); redraw(); }

	void hide_menu() {color_menu.hide(); menu_button.show(); }


	void red_pressed() { change(Color::red); hide_menu(); }
	void blue_pressed() { change(Color::blue); hide_menu(); }
	void black_pressed() { change(Color::black); hide_menu(); }
	void menu_pressed() { menu_button.hide(); color_menu.show(); }


	void next();
	void quit();

	static void cb_red(Address, Address wp);
	static void cb_blue(Address, Address);
	static void cb_black(Address, Address);
};

Lines_Window::Lines_Window(Point xy, int w, int h, const string &title)
	: Window{xy, w, h, title},
	next_button{Point{x_max()-150, 0}, 70, 20, "Next Point",
		[](Address, Address pw) { reference_to<Lines_Window>(pw).next(); }},
	quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit",
		[](Address, Address pw) { reference_to<Lines_Window>(pw).quit(); }},
	next_x{Point{x_max() - 310, 0}, 50, 20, "next x:"},
	next_y{Point{x_max() - 210, 0}, 50, 20, "next y:"},
	xy_out{Point{100, 0}, 100, 20, "current (x, y):"},
	color_menu{Point{x_max() - 70, 40}, 70, 20, Menu::vertical, "color"},
	menu_button{Point{x_max() - 80, 30}, 80, 20, "color menu",
		[](Address, Address pw) { reference_to<Lines_Window>(pw).menu_pressed(); }}
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no point");

	color_menu.attach(new Button{Point{0, 0}, 0, 0, "red", cb_red});
	color_menu.attach(new Button{Point{0, 0}, 0, 0, "blue", cb_blue});
	color_menu.attach(new Button{Point{0, 0}, 0, 0, "black", cb_black});
	attach(color_menu);
	color_menu.hide();
	attach(menu_button);

	attach(lines);
}

void Lines_Window::cb_red(Address, Address wp)
{
	reference_to<Lines_Window>(wp).red_pressed();
}

void Lines_Window::cb_blue(Address, Address wp)
{
	reference_to<Lines_Window>(wp).blue_pressed();
}

void Lines_Window::cb_black(Address, Address wp)
{
	reference_to<Lines_Window>(wp).black_pressed();
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
