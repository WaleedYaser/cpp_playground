#include "Graph_lib/Simple_window.h"
#include "Graph_lib/Graph.h"


#include <vector>

using namespace std;

struct A
{
	virtual void f1() { cout << "A::f1()\n"; }
	virtual void f2() { cout << "A::f2()\n"; }
	virtual void f3() { cout << "A::f3()\n"; }
	virtual void f4() { cout << "A::f4()\n"; }
};

struct B : A
{
	void f1() override { cout << "B::f1()\n"; }
	void f2() override { cout << "B::f2()\n"; }
	void f3() override { cout << "B::f3()\n"; }
	void f4() override { cout << "B::f4()\n"; }
};

int main()
{

	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;

	using namespace Graph_lib;

	Point tl {100, 100};

	Simple_window win {tl, 600, 400, "Canvas"};

	vector<Rectangle*> vr;

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			vr.push_back(new Rectangle{Point{i*20, j*20}, 20, 20});
			vr[vr.size()-1]->set_fill_color(Color{i*16 + j});
			win.attach(*vr[vr.size() - 1]);
		}
	}

	win.wait_for_button();
	
}
