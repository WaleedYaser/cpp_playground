#include <map>
#include <string>
#include <iostream>


using namespace std;


template <typename In1, typename In2, typename T, typename Bin_Op1, typename Bin_Op2>
T inner_product(In1 first1, In1 last1, In2 first2, T init, Bin_Op1 op1, Bin_Op2 op2)
{
	while (first1 != last1) {
		init = op1(init, op2(*first1, *first2));
		++first1;
		++first2;
	}
	return init;
}

int main()
{
	map<string, double> dow_price = {
		{"MMM", 81.86},
		{"AA", 34.69},
		{"MO", 54.45}
	};

	map<string, double> dow_weight = {
		{"MMM", 5.8549},
		{"AA", 2.4808},
		{"MO", 3.8940}
	};

	map<string, string> dow_name = {
		{"MMM", "3M Co."},
		{"AA", "Alcoa Inc."},
		{"MO", "Altria Group Inc."}
	};

	double dji_index = inner_product(dow_price.begin(), dow_price.end(),
									 dow_weight.begin(), 0.0,
									 [](double a, double b) { return a + b; },
									 [](const pair<string, double> &a, const pair<string, double> &b) -> double { return a.second * b.second; });
	cout << dji_index << endl;
}