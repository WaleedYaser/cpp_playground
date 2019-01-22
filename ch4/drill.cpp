#include <iostream>
#include <float.h>

int main()
{
	using namespace std;

	double x;
	double min = DBL_MAX, max = DBL_MIN;
	while (cin >> x) {
		cout << x << endl;
		if (x < min) {
			min = x;
			cout << " the smallest so far";
		}
		if (x > max) {
			max = x;
			cout << " the largest so far";
		}
		cout << endl;
	}
}
