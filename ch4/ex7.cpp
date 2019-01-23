#include <iostream>
#include <vector>
#include <string>

int str_to_int(std::string &s);

int main()
{
	using namespace std;

	int n1, n2;
	string s1, s2;
	char op;

	cin >> s1 >> s2 >> op;
	n1 = str_to_int(s1);
	n2 = str_to_int(s2);
	if (n1 == -1) {
		cout << "wrong input: " << n1 << endl;
		return 1;
	}
	if (n2 == -1) {
		cout << "wrong input: " << n2 << endl;
		return 1;
	}

	switch (op) {
		case '+':
			cout << n1 + n2 << endl;
			break;
		case '-':
			cout << n1 - n2 << endl;
			break;
		case '*':
			cout << n1 * n2 << endl;
			break;
		case '/':
			if (n2 != 0)
				cout << (double) n1 / (double) n2 << endl;
			else
				cout << "zeor division!" << endl;
			break;
		default:
			cout << "wrong input: " << op << endl;
	}

	return 0;
}

int str_to_int(std::string &s)
{
	static std::vector<std::string>
	str_values = {"zero", "one", "two", "three", "four",
		 		  "five", "six", "seven", "eight", "nine"};

	if (s.length() == 1) {
		if (s[0] >= '0' && s[0] <= '9')
			return s[0] - '0';
		else
			return -1;
	} else {
		int i;
		for (i = 0; i < 10; ++i)
			if (s == str_values[i])
				break;
		if (i < 10)
			return i;
		else
			return -1;
	}
}
