#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct X
{
	int val;

	void out(const string &s, int nv)
	{
		cerr << this << "->" << s << ": " << val << " (" << nv << ")\n";
	}

	X() {out("X()", 0); val = 0; }
	X(int v) { val = v; out("X(int)", v); }
	X(const X &x) { val = x.val; out("X(X&)", x.val); }
	X& operator = (const X &x) { out("X::operator = ()", x.val); val = x.val; return *this;}
	~X() { out("~X()", 0); }
};

X glob(2);				// X(int), 2

X copy(X a) { return a; }
X copy2(X a) { X aa = a; return aa; }
X& ref_to(X &a) { return a; }
X* make(int i) {X a(i); return new X(a); }

int main()
{
	cout << "\n";
	X loc {4};			// X(int), 4
	cout << "\n";
	X loc2 {loc};		// X(X&), 4
	cout << "\n";
	loc = X{5};			// X(int), 5, X::operator = (), ~X()
	cout << "\n";
	loc2 = copy(loc);	// X(X&), 5, X(X&), 5, X::operator = (), 5, ~X(), ~X()
	cout << "\n";
	loc2 = copy2(loc);	// X(X&), 5, X(X&) 5, X::operator = (), 5, ~X(), ~X()
	cout << "\n";
	X loc3 {6};			// X(int), 6
	cout << "\n";
	X &r = ref_to(loc);
	cout << "\n";
	delete make(7);		// X(int), 7, X(&x), 7, ~x(), ~X()
	cout << "\n";
	delete make(8);		// X(int), 8, X(&x), 8, ~x(), ~X()
	cout << "\n";

	vector<X> v(4);		// X(), 0, X(), 0, X(), 0, X(), 0
	cout << "\n";
	X loc4;				// X(), 0
	cout << "\n";
	X *p = new X(9);	// X(int), 9
	cout << "\n";
	delete p;			// ~X()
	cout << "\n";
	X *pp = new X[5];	// X(), 0, X(), 0, X(), 0, X(), 0, X(), 0
	cout << "\n";
	delete[] pp;		// ~X()
	cout << "\n";
}
