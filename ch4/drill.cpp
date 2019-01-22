#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <float.h>

int main()
{
	using namespace std;

	double value;
	string unit;
	vector<double> values;

	while (cin >> value >> unit) {
		if (unit == "m")
			values.push_back(value);
		else if (unit == "cm")
			values.push_back(value / 100);
		else if (unit == "in")
			values.push_back(value * 2.54 / 100);
		else if (unit == "ft")
			values.push_back(value * 2.54 * 12 / 100);
		else {
			cout << "illegal unit: " << unit << endl;
		}
	}

	sort(values.begin(), values.end());
	for (const double &x : values)
		cout << x << endl;

	return 0;
}
