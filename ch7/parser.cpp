/* grammars:
 * 	expression:
 * 		term
 * 		expression '+' term
 * 		expression '-' term
 * 	term:
 * 		primary
 * 		term '*' primary
 * 		term '/' primary
 * 		term '%' primary
 * 	primary:
 * 		number
 * 		'('expression')'
 * 	number:
 * 		floating point literal
 */

#include <iostream>
#include <string>

using namespace std;

void error(string s)
{
	throw runtime_error(s);
}

class Tocken
{
public:
	char	kind;		/* '8': number, '+ - * / % ( )' */
	double	value;
};

class Tocken_Stream {
public:
			Tocken_Stream();
	Tocken	get();
	void	putback(Tocken t);

private:
	bool   full{false};
	Tocken buffer;
};

Tocken_Stream::Tocken_Stream()
{

}

void Tocken_Stream::putback(Tocken t)
{
	if (full)
		error("putback() into a full buffer");
	buffer = t;
	full   = true;
}

Tocken Tocken_Stream::get()
{
	if (full) {
		full = false;
		return buffer;
	}
	char ch;
	cin >> ch;
	switch (ch) {
		case 'q':
		case ';':
		case '+': case '-': case '*': case '/': case '(': case ')':
			return Tocken{ch};
		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			cin.putback(ch);
			double val;
			cin >> val;
			return Tocken{'8', val};
		default:
			error("bad tocken");
	}
	return Tocken();
}

double expression();
double term();
double primary();

Tocken_Stream ts;

double expression()
{
	double left = term();
	Tocken t = ts.get();
	while (true) {
		switch (t.kind) {
			case '+':
				left += term();
				t = ts.get();
				break;
			case '-':
				left -= term();
				t = ts.get();
				break;
			default:
				ts.putback(t);
				return left;
		}
	}
}

double term()
{
	double left = primary();
	Tocken t = ts.get();
	while (true) {
		switch (t.kind) {
			case '*':
				left *= primary();
				t = ts.get();
				break;
			case '/':
			{
				double right = primary();
				if (right == 0)
					error("zero division");
				left /= right;
				t = ts.get();
				break;
			}
			default:
				ts.putback(t);
				return left;
		}
	}
}

double primary()
{
	Tocken t = ts.get();
	switch (t.kind) {
		case '8':
			return t.value;
			break;
		case '(':
		{
			double d = expression();
			t = ts.get();
			if (t.kind != ')')
				error("')' expected");
			return d;
		}
		default:
			error("primary expected");
	}
	return 0;
}

int main()
{
	try {
		double val = 0;
		while (cin) {
			Tocken t = ts.get();
			if (t.kind == 'q') break;
			if (t.kind == ';')
				cout << "=" << val << endl;
			else {
				ts.putback(t);
				val = expression();
			}
		}
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "exception" << endl;
		return 2;
	}
}
