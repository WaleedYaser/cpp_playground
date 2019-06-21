#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
	string from, to;
	cin >> from >> to;

	ifstream is {from};
	ofstream os {to};

	istream_iterator<string> ii{is};
	istream_iterator<string> eos;
	ostream_iterator<string> oo {os, "\n"};

	set<string> b {ii, eos};
	copy(b.begin(), b.end(), oo);
}