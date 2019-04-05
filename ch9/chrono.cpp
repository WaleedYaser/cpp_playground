#include "Chrono.h"

namespace chrono {

	Date::Date(int yy, Month mm, int dd)
		: y{yy}, m{mm}, d{dd}
	{
		if (!is_date(yy, mm, dd)) throw Invalid{};
	}

	const Date & default_date()
	{
		const static Date dd {2001, Month::jan, 1};
		return dd;
	}

	Date::Date()
		: y{default_date().year()},
		  m{default_date().month()},
		  d{default_date().day()}
	{
	}

	void Date::add_day(int n)
	{
	}

	void Date::add_month(int n)
	{
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leap_year(y+n)) {
			m = Month::mar;
			d = 1;
		}
		y += n;
	}

	bool is_date(int yy, Month mm, int dd)
	{
		// assume y is valid

		if (dd <= 0) return false;
		if (mm < Month::jan || mm > Month::dec) return false;

		int days_in_month = 31;

		switch (mm) {
			case Month::feb:
				days_in_month = (leap_year(yy)) ? 29 : 28;
				break;
			case Month::apr: case Month::jun: case Month::sep: case Month::nov:
				days_in_month = 30;
				break;
		}

		if (days_in_month < dd) return false;

		return true;
	}

	bool leap_year(int y)
	{
	}

	bool operator==(const Date &a, const Date &b)
	{
		return a.year() == b.year() &&
			   a.month() == b.month() &&
			   a.day() == b.day();
	}

	bool operator!=(const Date &a, const Date &b)
	{
		return !(a == b);
	}

	std::ostream & operator<<(std::ostream &os, const Date &dd)
	{
		return os << '(' << dd.year() << ',' << int(dd.month()) << ',' << dd.day() << ')';
	}

	std::istream & operator>>(std::istream &is, Date &dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') {
			is.clear(std::ios_base::failbit);		// set the fail bit
			return is;
		}

		dd = Date{y, Month(m), d};

		return is;
	}

	enum class Day {
		sunday, monday, tuesday, wednessday, thursday, friday, saturday
	};

	Day day_of_weak(const Date &d)
	{
	}

	Date next_sunday(const Date &d)
	{
	}

	Date next_weekday(const Date &d)
	{
	}

}


int main()
{
	chrono::Date d;
	std::cout << d << std::endl;
	return 0;
}
