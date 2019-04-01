/* 
 * 		Simple Calculator
 *
 * 		Revision history:
 *
 * 			Revised by Waleed Yaser April 2019
 * 			Originally written by Waleed Yaser
 * 				(waleedyaser95@gmail.com) March 2019
 *
 * 		This program implements a basic expression calculator.
 * 		input from cin; output to cout.
 * 		The grammar for input is:
 * 			calculation:
 * 				statement
 * 				print
 * 				quit
 * 				calculation statement
 * 			statement:
 * 				declaration
 * 				expression
 * 			declaration:
 * 				'let' name '=' expression
 * 			expression:
 * 				term
 * 				expression '+' term
 * 				expression '-' term
 * 			term:
 * 				primary
 * 				term '*' primary
 * 				term '/' primary
 * 				term '%' primary
 * 			primary:
 * 				number
 * 				'('expression')'
 * 			number:
 * 				floating point literal
 *
 *
 * 		input comes from cin through the Token_stream called ts.
 */

#include <iostream>
#include <string>
#include <vector>

#define NUMBER		'8'
#define QUIT		'q'			// quit token 
#define PRINT		';'			// print token

#define PROMPT		"> "
#define RESULT		"= "		// used to indicate that what follow is a result

#define NAME		'a'
#define LET			'L'
#define DECLKEY		"let"

using namespace std;

void error(string s)
{
	throw runtime_error(s);
}

void error(string s, string t)
{
	throw runtime_error(s + t);
}

class Token
{
public:
	char	kind;		/* NUMBER, '+ - * / % ( )' */
	double	value;
	string	name;

	Token() { }
	Token(char ch) : kind{ch} { }
	Token(char ch, double val) : kind{ch}, value{val} { }
	Token(char ch, string n) : kind{ch}, name{n} { }
};

class Token_Stream {
public:
			Token_Stream();
	Token	get();
	void	putback(Token t);
	void	ignore(char c);		// discard characters up to and including c

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
		case QUIT:
		case PRINT:
		case '=':
		case '+': case '-': case '*': case '/': case '(': case ')':
			return Token(ch);
		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			cin.putback(ch);
			double val;
			cin >> val;
			return Token(NUMBER, val);
		default:
			if (isalpha(ch)) {
				string s;
				s += ch;
				while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
					s += ch;
				cin.putback(ch);
				if (s == DECLKEY)
					return Token(LET);
				return Token(NAME, s);
			}
			error("bad token");
	}
	return Token();
}

void Token_Stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}

	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c)
			return;
}

class Variable {
public:
	string name;
	double value;
};

vector<Variable> var_table;

double get_value(string s) {
	for (const Variable &v : var_table)
		if (v.name == s)
			return v.value;
	error("get: undefined variable ", s);
	return 0;
}

void set_value(string s, double d)
{
	for (Variable &v : var_table)
		if (v.name == s)
			v.value = d;
	error("set: undefined variable ", s);
}

bool is_declared(string var)
{
	for (const Variable &v : var_table)
		if (v.name == var)
			return true;
	return false;
}

double define_name(string var, double val)
{
	if (is_declared(var))
		error(var, " declared twice");
	var_table.push_back(Variable{var, val});
	return val;
}

double statement();
double declaration();
double expression();
double term();
double primary();

Token_Stream ts;

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
		case LET:
			return declaration();
		default:
			ts.putback(t);
			return expression();
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != NAME)
		error ("name expected in declaration");
	string var_name = t.name;

	t = ts.get();
	if (t.kind != '=')
		error("= missing in declaration of ", var_name);
	double d = expression();
	define_name(var_name, d);
	return d;
}

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
		case NAME:
			return get_value(t.name);
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

void clean_up_mess()
{
	ts.ignore(PRINT);
}

void calculate()
{
	while (cin) {
		try {
			cout << PROMPT;
			Token t = ts.get();
			while (t.kind == PRINT)
				t = ts.get();		// discard all prints
			if (t.kind == QUIT)
				return;
			ts.putback(t);
			cout << RESULT << statement() << endl;
		}
		catch (exception &e) {
			cerr << e.what() << endl;
			clean_up_mess();
		}
	}
}

int main()
{
	try {
		define_name("pi", 3.1415926535);
		define_name("e", 2.7182818284);

		calculate();

		return 0;
	}
	catch (runtime_error &e) {
		cerr << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "exception" << endl;
		return 2;
	}
}
