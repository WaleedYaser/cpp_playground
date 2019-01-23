#include <iostream>
#include <vector>
#include <string>

int main()
{
	using namespace std;

	vector<string> str_values = {"zero", "one", "two", "three", "four",
								 "five", "six", "seven", "eight", "nine"};

	for (string s; cin >> s; ) {
		if (s.length() == 1) {
			if (s[0] >= '0' && s[0] <= '9')
				cout << s[0] - '0' << endl;
			else
				cout << "wrong input: " << s << endl;
		} else {
			int i;
			for (i = 0; i < 10; ++i)
				if (s == str_values[i])
					break;
			if (i < 10)
				cout << i << endl;
			else
				cout << "wrong input: " << s << endl;
		}
	}

	return 0;
}
