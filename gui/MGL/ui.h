#pragma once

//----------------------------------------------------------------------------//

#include<fltk.h>

//----------------------------------------------------------------------------//

#include <iostream>
#include <fstream>
#include <initializer_list>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include <math.h>

//----------------------------------------------------------------------------//

using namespace std;

//----------------------------------------------------------------------------//

namespace UTL
{
	//--------------------------------------------------------------------//

	inline void error(const string &s)
	{
		throw runtime_error(s);
	}

	inline void error(const string &s1, const string &s2)
	{
		error(s1 + s2);
	}

	//--------------------------------------------------------------------//

	template <class T>
	class Vector_Ref
	{
		vector<T*> v;
		vector<T*> owned;

	public:
		Vector_Ref() { }

		Vector_Ref(T *a, T *b = 0, T *c = 0, T *d = 0)
		{
			if (a) push_back(a);
			if (b) push_back(b);
			if (c) push_back(c);
			if (d) push_back(d);
		}

		~Vector_Ref()
		{
			for (int i = 0; i < owned.size(); ++i)
				delete owned[i];
		}

		void push_back(T &s) { v.push_back(&s); }
		void push_back(T *p) { v.push_back(p); owned.push_back(p); }

		T& operator [] (int i) { return *v[i]; }
		const T& operator [] (int i) { return *v[i]; }
		int size() const { return v.size(); }
	};

	//--------------------------------------------------------------------//

	typedef void * Address;
	typedef void (*Callback) (Address, Address);

	template <class T>
	T& reference_to(Address pw)
	{
		return *static_cast<T*>(pw);
	}

	//--------------------------------------------------------------------//

}

//----------------------------------------------------------------------------//

namespace MGL
{
	//--------------------------------------------------------------------//

	struct Point
	{
		int x;
		int y;
	};

	bool operator == (Point a, Point b) { return a.x == b.x && a.y == b.y; }
	bool operator != (Point a, Point b) { return !(a == b); }

	//--------------------------------------------------------------------//

	struct Color
	{
		enum Color_Type
		{
			red				= FL_RED,
			blue			= FL_BLUE,
			green			= FL_GREEN,
			yellow			= FL_YELLOW,
			white			= FL_WHITE,
			black			= FL_BLACK,
			magenta			= FL_MAGENTA,
			cyan			= FL_CYAN,
			dark_red		= FL_DARK_RED,
			dark_blue		= FL_DARK_BLUE,
			dark_green		= FL_DARK_GREEN,
			dark_yellow 	= FL_DARK_YELLOW,
			dark_magenta	= FL_DARK_MAGENTA,
			dark_cyan		= FL_DARK_CYAN
		};

		enum Transparency { invisible = 0, visible = 255 };

		Color(Color_Type cc) : c{Fl_Color(cc)}, v{visible} { }
		Color(Color_Type cc, Transparency vv) : c{Fl_Color(cc)}, v{vv} { }
		Color(int cc) : c{Fl_Color(cc)}, v{visible} { }
		Color(Transparency vv) : c{Fl_Color()}, v{vv} { }

		int as_int() const { return c; }

		char visibility() const { return v; }
		void set_visibility(Transparency vv) { v = vv; }

	private:
		char v;
		Fl_Color c;
	};

	//--------------------------------------------------------------------//

	struct Line_Style
	{
		enum Line_Style_Type {
			solid		= FL_SOLID,
			dash		= FL_DASH,
			dot			= FL_DOT,
			dashdot		= FL_DASHDOT,
			dashdotdot	= FL_DASHDOTDOT
		};

		Line_Style(Line_Style_Type ss) : s{ss}, w{0} { }
		Line_Style(Line_Style_Type ss, int ww) : s{ss}, w{0} { }
		Line_Style(int ss) : s{ss}, w{0} { }

		int width() const { return w; }
		int style() const { return s; }

	private:
		int s;
		int w;
	};

	//--------------------------------------------------------------------//

	class Font
	{
	public:
		enum Font_Type {
			helvetica=FL_HELVETICA,
			helvetica_bold=FL_HELVETICA_BOLD,
			helvetica_italic=FL_HELVETICA_ITALIC,
			helvetica_bold_italic=FL_HELVETICA_BOLD_ITALIC,
			courier=FL_COURIER,
			courier_bold=FL_COURIER_BOLD,
			courier_italic=FL_COURIER_ITALIC,
			courier_bold_italic=FL_COURIER_BOLD_ITALIC,
			times=FL_TIMES,
			times_bold=FL_TIMES_BOLD,
			times_italic=FL_TIMES_ITALIC,
			times_bold_italic=FL_TIMES_BOLD_ITALIC,
			symbol=FL_SYMBOL,
			screen=FL_SCREEN,
			screen_bold=FL_SCREEN_BOLD,
			zapf_dingbats=FL_ZAPF_DINGBATS
		};

		Font(Font_Type ff) : f{ff} { }
		Font(int ff) : f{ff} { }

		int as_int() const { return f; }
	private:
		int f;
	};

	//--------------------------------------------------------------------//

	class Shape
	{
	public:
		void draw() const;
		virtual void move(int dx, int dy);

		void set_color(Color c) { lcolor = c; }
		Color color() const { return lcolor; }

		void set_fill_color(Color c) { fcolor = c; }
		Color fill_color() const { return fcolor; }

		void set_style(Line_Style style) { lstyle = style; }
		Line_Style style() const { return lstyle; }

		Point point(int i) const { return points[i]; }
		int number_of_points() const { return points.size(); }

		Shape(const Shape &) = delete;
		Shape& operator = (const Shape &) = delete;

		virtual ~Shape();

	protected:
		Shape() { }
		Shape(initializer_list<Point> lst);

		virtual void draw_lines() const;
		void add(Point p) { points.push_back(p); }
		void set_point(int i, Point p) { points[i] = p; }

	private:
		vector<Point> points;
		Color lcolor {fl_color()};
		Color fcolor {Color::invisible};
		Line_Style lstyle {0};
	};

	void Shape::draw() const
	{
		Fl_Color oldc = fl_color();
		fl_color(lcolor.as_int());
		fl_line_style(lstyle.style(), lstyle.width());
		draw_lines();
		fl_color(oldc);
		fl_line_style(0);
	}

	void Shape::move(int dx, int dy)
	{
		for (Point &p : points)
		{
			p.x += dx;
			p.y += dy;
		}
	}

	Shape::Shape(initializer_list<Point> lst)
	{
		for (const Point &p : lst) add(p);
	}

	void Shape::draw_lines() const
	{
		if (color().visibility() && points.size() > 1)
			for (int i = 1; i < points.size(); ++i)
				fl_line(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
	}

	//--------------------------------------------------------------------//

	struct Line : Shape
	{
		Line(Point p1, Point p2);
	};

	Line::Line(Point p1, Point p2)
	{
		add(p1);
		add(p2);
	}

	//--------------------------------------------------------------------//

	struct Lines : Shape
	{
		Lines() {}
		Lines(initializer_list<pair<Point, Point>> points);

		void draw_lines() const;
		void add(Point p1, Point p2);
	};

	Lines::Lines(initializer_list<pair<Point, Point>> points)
	{
		for (auto p : points)
			add(p.first, p.second);
	}

	void Lines::add(Point p1, Point p2)
	{
		Shape::add(p1);
		Shape::add(p2);
	}

	void Lines::draw_lines() const
	{
		if (color().visibility())
			for (int i=0; i <number_of_points(); i+=2)
				fl_line(point(i-1).x, point(i-1).y, point(i).x, point(i).y);

	}

	//--------------------------------------------------------------------//

	struct Open_Polyline : Shape {
		using Shape::Shape;				// using shape constructor
		void  add(Point p) { Shape::add(p); }
	};

	//--------------------------------------------------------------------//

	struct Closed_Polyline : Open_Polyline
	{
		using Open_Polyline::Open_Polyline;

		void draw_lines() const override;
	};

	void Closed_Polyline::draw_lines() const
	{
		Open_Polyline::draw_lines();

		int n = number_of_points();
		if (n > 2 && color().visibility())
			fl_line(point(n-1).x, point(n-1).y, point(0).x, point(0).y);
	}

	//--------------------------------------------------------------------//

	inline pair<double, double> line_intersect(Point p1, Point p2, Point p3,
											   Point p4, bool &parallel)
	{
		double denom = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);
		if (denom == 0) {
			parallel = true;
			return pair<double, double>(0,0);
		}

		parallel = false;
		double dx = ((p4.x - p3.x)*(p1.y - p3.y) - (p4.y - p3.y)*(p1.x - p3.x));
		double dy = ((p2.x - p1.x)*(p1.y - p3.y) - (p2.y - p1.y)*(p1.x - p3.x));
		return pair<double, double>(dx / denom, dy / denom);
	}

	bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4,
								Point &intersection)
	{
		bool parallel;
		pair<double, double> u = line_intersect(p1, p2, p3, p4, parallel);

		if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1)
			return false;

		intersection.x = p1.x + u.first  * (p2.x - p1.x);
		intersection.y = p1.y + u.second * (p2.y - p1.y);

		return true;
	}

	struct Polygon : Closed_Polyline
	{
		using Closed_Polyline::Closed_Polyline;

		void add(Point p);
		void draw_lines() const override;
	};

	void Polygon::add(Point p)
	{
		int np = number_of_points();

		if (np > 1) {
			if (p == point(np-1))
				UTL::error("Polygon point equal to previous point");
			bool parallel;
			line_intersect(point(np-1), p, point(np-2), point(np-1), parallel);
			if (parallel)
				UTL::error("two polygon points lie in a straight line");
		}

		for (int i = 1; i < np - 1; ++i) {
			Point ignore{0, 0};
			if (line_segment_intersect(point(np-1), p, point(i-1), point(i), ignore))
				UTL::error("intersect in polygon");
		}

		Closed_Polyline::add(p);
	}

	void Polygon::draw_lines() const
	{
		if (number_of_points() < 3)
			UTL::error("intersect in polygon");
		Closed_Polyline::draw_lines();
	}

	//--------------------------------------------------------------------//

	struct Rectangle : Shape
	{
		Rectangle(Point xy, int ww, int hh);
		Rectangle(Point p1, Point p2);

		void draw_lines() const override;

		int height() const { return h; }
		int width()  const { return w; }

	private:
		int h;
		int w;
	};

	Rectangle::Rectangle(Point xy, int ww, int hh)
		: h{hh}, w{ww}
	{
		if (h <= 0 || w <= 0)
			UTL::error("bad rectangle: non-positive side");
		add(xy);
	}

	Rectangle::Rectangle(Point p1, Point p2)
		: w{p2.x - p1.x}, h{p2.y - p1.y}
	{
		if (h <= 0 || w <= 0)
			UTL::error("bad rectangle: first point is not top left");
		add(p1);
	}

	void Rectangle::draw_lines() const
	{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_rect(point(0).x, point(0).y, w, h);
		}

		if (color().visibility()) {
			fl_color(color().as_int());
			fl_rect(point(0).x, point(0).y, w, h);
		}
	}

	//--------------------------------------------------------------------//

	struct Text : Shape
	{
		Text(Point p, const string &s)
			: lab{s}
		{
			add(p);
		}

		void draw_lines() const override;

		void set_label(const string &s) { lab = s; }
		string label() const { return lab; }

		void set_font(Font f) { fnt = f; }
		Font font() const { return fnt; }

		void set_font_size(int s) { fnt_sz = s; }
		int  font_size() const { return fnt_sz; }

	private:
		string lab;
		Font fnt {fl_font()};
		int  fnt_sz {fl_size() < 14 ? 14 : fl_size()};
	};

	void Text::draw_lines() const
	{
		fl_draw(lab.c_str(), point(0).x, point(0).y);
	}

	//--------------------------------------------------------------------//

	struct Circle : Shape
	{
		Circle(Point p, int rr);

		void draw_lines() const override;

		Point center() const;
		int radius() const { return r; }
		void set_radius(int rr);

	private:
		int r;
	};

	Circle::Circle(Point p, int rr)
		: r{rr}
	{
		add(Point{p.x - r, p.y - r});
	}

	void Circle::draw_lines() const
	{
		if (color().visibility())
			fl_arc(point(0).x, point(0).y, r+r, r+r, 0, 360);
	}

	Point Circle::center() const
	{
		return {point(0).x + r, point(0).y +r};
	}

	void Circle::set_radius(int rr)
	{
		set_point(0, Point{center().x - rr, center().y - rr});
		r = rr;
	}

	//--------------------------------------------------------------------//

	struct Ellipse : Shape
	{
		Ellipse(Point p, int ww, int hh);

		void draw_lines() const override;

		Point center() const;
		Point focus1() const;
		Point focus2() const;

		int major() const { return w; }
		void set_major(int ww);
		int minor() const { return h; }
		void set_minor(int hh);
		
	private:
		int w;
		int h;
	};

	Ellipse::Ellipse(Point p, int ww, int hh)
		: w{ww}, h{hh}
	{
		add(Point{p.x - w, p.y - h});
	}

	void Ellipse::draw_lines() const
	{
		if (color().visibility())
			fl_arc(point(0).x, point(0).y, w+w, h+h, 0, 360);
	}

	Point Ellipse::center() const
	{
		return {point(0).x + w, point(0).y +h};
	}

	Point Ellipse::focus1() const
	{
		if (h < w)
			return {center().x + int(sqrt(double(w*w - h*h))), center().y};
		else
			return {center().x, center().y + int(sqrt(double(h*h - w*w)))};
	}

	Point Ellipse::focus2() const
	{
		if (h < w)
			return {center().x - int(sqrt(double(w*w - h*h))), center().y};
		else
			return {center().x, center().y - int(sqrt(double(h*h - w*w)))};
	}

	void Ellipse::set_major(int ww)
	{
		set_point(0, {center().x - ww, center().y});
		w = ww;
	}

	void Ellipse::set_minor(int hh)
	{
		set_point(0, {center().x, center().y - hh});
		h = hh;
	}

	//--------------------------------------------------------------------//

	void draw_mark(Point p, char c)
	{
		constexpr int dx = 4;
		constexpr int dy = 4;

		string m {1, c};
		fl_draw(m.c_str(), p.x-dx, p.y+dy);
	}

	struct Marked_Polyline : Open_Polyline
	{
		Marked_Polyline(const string &m);

		Marked_Polyline(const string &m, initializer_list<Point> lst);

		void draw_lines() const override;

	private:
		string mark;
	};

	Marked_Polyline::Marked_Polyline(const string &m)
		: mark{m}
	{
		if (m == "") mark = "*";
	}

	Marked_Polyline::Marked_Polyline(const string &m, initializer_list<Point> lst)
		: Open_Polyline{lst}, mark{m}
	{
		if (m == "") mark = "*";
	}

	void Marked_Polyline::draw_lines() const
	{
		Open_Polyline::draw_lines();
		for (int i = 0; i < number_of_points(); ++i)
			draw_mark(point(i), mark[i % mark.size()]);
	}

	//--------------------------------------------------------------------//

	struct Marks : Marked_Polyline
	{
		Marks(const string &m)
			: Marked_Polyline{m}
		{
			set_color(Color{Color::invisible});
		}

		Marks(const string &m, initializer_list<Point> lst)
			: Marked_Polyline{m, lst}
		{
			set_color(Color{Color::invisible});
		}
	};

	struct Mark : Marks
	{
		Mark(Point p, char c)
			: Marks(string{1, c})
		{
			add(p);
		}
	};
	

	//--------------------------------------------------------------------//

	enum class Suffix { none, jpg, gif };

	map<string, Suffix> suffix_map;

	int init_suffix_map()
	{
		suffix_map["jpg"] = Suffix::jpg;
		suffix_map["JPG"] = Suffix::jpg;
		suffix_map["jpeg"] = Suffix::jpg;
		suffix_map["JPEG"] = Suffix::jpg;
		suffix_map["gif"] = Suffix::gif;
		suffix_map["GIF"] = Suffix::gif;
		return 0;
	}


	Suffix get_encoding(const string &s)
	{
		static int x = init_suffix_map();

		string::const_iterator p = find(s.begin(), s.end(), '.');
		if (p == s.end()) return Suffix::none;
 
		string suf(p+1, s.end());
		return suffix_map[suf];
	}

	bool can_open(const string &s)
	{
		ifstream ff{s};
		return (bool) ff;
	}

	struct Image : Shape {
		Image(Point xy, string file_name, Suffix e = Suffix::none);
		~Image() { delete p; }

		void draw_lines() const override;

		void set_mask(Point xy, int ww, int hh)
		{
			w = ww; h = hh; cx = xy.x; cy = xy.y;
		}

	private:
		int w, h;
		int cx, cy;
		Fl_Image *p;
		Text fn;
	};

	Image::Image(Point xy, string file_name, Suffix e)
		: w{0}, h{0}, fn{xy, ""}
	{
		add(xy);
		if (!can_open(file_name)) {
			fn.set_label("cannot open \"" + file_name + '"');
			p = new Bad_Image{30, 20};
			return;
		}

		if (e == Suffix::none) e = get_encoding(file_name);

		switch (e) {
			case Suffix::jpg:
				p = new Fl_JPEG_Image{file_name.c_str()};
				break;
			case Suffix::gif:
				p = new Fl_GIF_Image{file_name.c_str()};
				break;
			default:
				fn.set_label("unsupported file type\"" + file_name + '"');
				p = new Bad_Image{30, 20};
		}
	}


	struct Bad_Image : Fl_Image {
		Bad_Image(int h, int w) : Fl_Image{h, w, 0} { }
		void draw(int x, int y, int, int, int) { draw_empty(x, y); }
	};

	//--------------------------------------------------------------------//

	using Fct = double (*) (double);

	struct Function : Shape
	{
		Function(Fct f, double r1, double r2, Point orig, int count = 100,
				 double x_scale = 35, double y_scale = 25);
	};

	Function::Function(Fct f, double r1, double r2, Point orig,int count = 100,
					   double x_scale = 35, double y_scale = 25)
	{
		if (r2 - r1 <= 0) UTL::error("bad graphics range");
		if (count <= 0) UTL::error("non-positive graphing count");
		double dist = (r2 - r1) / count;
		double r = r1;
		for (int i = 0; i < count; ++i) {
			add(Point{orig.x+int(r*x_scale), orig.y-int(f(r)*y_scale)});
			r += dist;
		}
	}

	//--------------------------------------------------------------------//

	struct Axis : Shape
	{
		enum Orientation { x, y, z };

		Axis(Orientation d, Point xy, int lenght, int number_of_notches=0,
			 string label = "");

		void draw_lines() const override;
		void move(int dx, int dy) override;
		void set_color(Color c);

		Text label;
		Lines notches;
	};

	Axis::Axis(Orientation d, Point xy, int lenght, int number_of_notches, string lab)
		: label(Point{0, 0}, lab)
	{
		if (lenght < 0) UTL::error("bad axis length");

		switch (d) {
			case Axis::x:
			{
				Shape::add(xy);
				Shape::add(Point{xy.x + lenght, xy.y});

				if (number_of_notches > 0) {
					int dist = lenght / number_of_notches;
					int x = xy.x + dist;
					for (int i = 0; i < number_of_notches; ++i) {
						notches.add(Point{x, xy.y}, Point{x, xy.y - 5});
						x += dist;
					}

				}

				label.move(lenght/3, xy.y + 20);
				break;
			}
			case Axis::y:
			{
				Shape::add(xy);
				Shape::add(Point{xy.x, xy.y - lenght});

				if (number_of_notches > 0) {
					int dist = lenght / number_of_notches;
					int y = xy.y - dist;
					for (int i = 0; i < number_of_notches; ++i) {
						notches.add(Point{xy.x, y}, Point{xy.x + 5, y});
						y -= dist;
					}

				}

				label.move(xy.x - 10, xy.y -lenght - 10);
				break;
			}
			case Axis::z:
				UTL::error("z axis not implemented");
		}
	}

	void Axis::draw_lines() const
	{
		Shape::draw_lines();
		notches.draw();
		label.draw();
	}

	void Axis::set_color(Color c)
	{
		Shape::set_color(c);
		notches.set_color(c);
		label.set_color(c);
	}

	void Axis::move(int dx, int dy)
	{
		Shape::move(dx, dy);
		notches.move(dx, dy);
		label.move(dx, dy);
	}

	//--------------------------------------------------------------------//

	using namespace UTL;

	class Widget
	{
	public:
		Widget(Point xy, int w, int h, const string &s, Callback cb);

		virtual void move(int dx, int dy);
		virtual void hide();
		virtual void show();
		virtual void attach(Window &) = 0;

		Point loc;
		int width;
		int height;
		string label;
		Callback do_it;
	protected:
		Window *own;
		Fl_Widget *pw;
	};

	//--------------------------------------------------------------------//

	class Button : public Widget
	{
	public:
		Button(Point xy, int w, int h, const string &label, Callback cb)
		: Widget{xy, w, h, label, cb} { }

		void attach(Window &) override;

	};

	//--------------------------------------------------------------------//

	struct Window
	{
		Window(Point xy, int w, int h, const string &title);

		int x_max() const;

		void attach(Widget &d);
	};

	struct Simple_Window : Window
	{
		Simple_Window(Point xy, int w, int h, const string &title);

		void wait_for_button();
	private:
		Button next_button;
		bool button_pushed;

		static void cb_next(Address, Address);
		void next();
	};

	Simple_Window::Simple_Window(Point xy, int w, int h, const string &title)
		: Window(xy, w, h, title),
		next_button{Point{x_max() - 70, 0}, 70, 20, "Next", cb_next},
		button_pushed{false}
	{
		attach(next_button);
	}

	void Simple_Window::cb_next(Address, Address pw)
	{
		reference_to<Simple_Window>(pw).next();
	}

	void Simple_Window::wait_for_button()
	{
		while(!button_pushed) Fl::wait();
		button_pushed = false;
		Fl::redraw();
	}

	void Simple_Window::next()
	{
		button_pushed = true;
	}

	//--------------------------------------------------------------------//

	struct In_Box : Widget
	{
		In_Box(Point xy, int w, int h, const string &s)
			: Widget{xy, w, h, s, 0} { }
		int get_int();
		string get_string();

		void attach(Window &w) override;
	};

	struct Out_Box : Widget
	{
		Out_Box(Point xy, int w, int h, const string & s)
			: Widget{xy, w, h, s, 0} { }
		void put(int);
		void put(const string &);

		void attach(Window &w) override;
	};

	//--------------------------------------------------------------------//

	struct Menu : Widget
	{
		enum Kind { horizontal, vertical };
		Menu(Point xy, int w, int h, Kind kk, const string & label);
		Vector_Ref<Button> selection;
		Kind k;
		int offset;
		int attach(Button &b);
		int attach(Button &p);

		void show() override
		{
			for (int i = 0; i < selection.size(); ++i ) 
				selection[i].show();
		}

		void hide() override;
		void move(int dx, int dy) override;

		void attach(Window &w);
	};

	//--------------------------------------------------------------------//

}

//----------------------------------------------------------------------------//