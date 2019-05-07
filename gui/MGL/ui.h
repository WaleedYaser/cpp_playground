#pragma once

//----------------------------------------------------------------------------//

#include<fltk.h>

//----------------------------------------------------------------------------//

#include <initializer_list>
#include <utility>

//----------------------------------------------------------------------------//

using namespace std;

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

	struct Shape
	{
		void add(Point p);
		Point point(int index) const;

		Color color() const;
		int number_of_points() const;
	};

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

}

