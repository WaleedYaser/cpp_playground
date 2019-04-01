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

#define NUMBER		'8'
#define QUIT		'q'			// quit token 
#define PRINT		';'			// print token

#define PROMPT		"> "
#define RESULT		"= "		// used to indicate that what follow is a result

using namespace std;

void error(string s)
{
	throw runtime_error(s);
}

class Token
{
public:
	char	kind;		/* NUMBER, '+ - * / % ( )' */
	double	value;
};

class Token_Stream {
public:
			Token_Stream();
	Token	get();
	void	putback(Token t);

private:
	bool   full{false};
	Token buffer;
};

Token_Stream::Token_Stream()
{

}

void Token_Stream::putback(Token t)
{
	if (full)
		error("putback() into a full buffer");
	buffer = t;
	full   = true;
}

Token Token_Stream::get()
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
			return Token{ch};
		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			cin.putback(ch);
			double val;
			cin >> val;
			return Token{NUMBER, val};
		default:
			error("bad tocken");
	}
	return Token();
}

double expression();
double term();
double primary();

Token_Stream ts;

double expression()
{
	double left = term();
	Token t = ts.get();
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
	Token t = ts.get();
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
	Token t = ts.get();
	switch (t.kind) {
		case NUMBER:
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
			cout << PROMPT;
			Token t = ts.get();
			if (t.kind == QUIT) break;
			if (t.kind == PRINT)
				cout << RESULT << val << endl;
			else {
				ts.putback(t);
				val = expression();
			}
		}
	}
	catch (runtime_error &e) {
		cerr << e.what() << endl;
		return 1;
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
