#include <iostream>

namespace chrono {

	enum class Month {
		jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date {
	public:
		class Invalid { };				// to throw as exception

		Date (int yy, Month mm, int dd);	// check for valid date and initialize
		Date ();						// default constructor
		// the default copy constructor is fine

		// non-modifying operations
		int day() const { return d; }
		Month month() const { return m; }
		int year() const { return y; }

		// modifying operations
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);

	private:
		int   y;
		Month m;
		int   d;
	};

	const Date & default_date();

	bool is_date(int yy, Month mm, int dd);	// true for valid date
	bool leap_year(int yy);					// true for leap year

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);

	std::ostream & operator<<(std::ostream &os, const Date &dd);
	std::istream & operator>>(std::istream &is, Date &dd);

}
