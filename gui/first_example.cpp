#include "Graph_lib/Simple_window.h"
#include "Graph_lib/Graph.h"


#include <vector>

using namespace std;

struct Distribution
{
	int year, young, middle, old;
};

istream & operator >> (istream &is, Distribution &d)
{
	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;
	Distribution dd;

	if (is >> ch1 >> dd.year >> ch2 >> dd.young >> dd.middle >> dd.old >> ch3) {
		if (ch1 != '(' || ch2 != ':' || ch3 != ')') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else
	{
		return is;
	}
	d = dd;
	return is;
	
}

class Scale
{
	int c_base;
	int v_base;
	double scale;
public:
	Scale(int b, int vb, double s) : c_base{b}, v_base{vb}, scale{s} { }
	int operator () (int v) const { return c_base + (v - v_base) * scale; }
};

int main()
{

	string flie_name = "japanese-age-data.txt";
	ifstream ifs {flie_name};
	if (!ifs) error("can't open ", flie_name);

	using namespace Graph_lib;

	constexpr int x_max = 600;
	constexpr int y_max = 400;

	constexpr int x_offset = 100;
	constexpr int y_offset = 60;

	constexpr int x_space = 40;
	constexpr int y_space = 40;

	constexpr int x_len = x_max - x_offset - x_space;
	constexpr int y_len = y_max - y_offset - y_space;

	constexpr int base_year = 1960;
	constexpr int end_year  = 2040;

	constexpr double x_scale = double(x_len) / (end_year - base_year);
	constexpr double y_scale = double(y_len) / 100;

	Scale xs {x_offset, base_year, x_scale};
	Scale ys {y_max - y_offset, 0, -y_scale};


	Simple_window win {Point{100, 100}, x_max, y_max, "Aging Japan"};

	Axis x {Axis::x, Point{x_offset, y_max - y_offset}, x_len,
			(end_year - base_year) / 10,
			"year     1960     1970     1980     1990     "
			"2000     2010     2020     2030     2040"};
	x.label.move(-100, 0);
	win.attach(x);
	Axis y {Axis::y, Point{x_offset, y_max - y_offset}, y_len, 10, "% of population"};
	win.attach(y);

	Line current_year {Point{xs(2019), ys(0)}, Point{xs(2019), ys(100)}};
	current_year.set_style(Line_style::dash);
	win.attach(current_year);

	Open_polyline children;
	Open_polyline adults;
	Open_polyline aged;

	for (Distribution d; ifs >> d; ) {
		if (d.year < base_year || d.year > end_year) error("year out of range");
		if (d.young + d.middle + d.old != 100) error("percentage doesn't add up");

		const int x = xs(d.year);
		children.add(Point{x, ys(d.young)});
		adults.add(Point{x, ys(d.middle)});
		aged.add(Point{x, ys(d.old)});
	}

	Text children_label {Point{20, children.point(0).y}, "age 0-14"};
	children.set_color(Color::dark_red);
	children_label.set_color(Color::dark_red);
	win.attach(children);
	win.attach(children_label);

	Text adults_label {Point{20, adults.point(0).y}, "age 15-64"};
	adults.set_color(Color::dark_blue);
	adults_label.set_color(Color::dark_blue);
	win.attach(adults);
	win.attach(adults_label);

	Text aged_label {Point{20, aged.point(0).y}, "age 65+"};
	aged.set_color(Color::dark_green);
	aged_label.set_color(Color::dark_green);
	win.attach(aged);
	win.attach(aged_label);

	gui_main();

}
