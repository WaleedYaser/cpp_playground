#include <iostream>
#include <string>

int main()
{
	using namespace std;
	cout << "this is a guessing game, select a number between 1 and 100" << endl;
	cout << "you will be asked several questions, please answer 'yes' or 'no'" << endl;

	string ans;
	bool answer_found = false;
	int low = 1;
	int high = 100;
	int n;
	while (!answer_found) {
		n = (high + low) / 2;
		cout << "have you selected " << n << endl;
		cin >> ans;
		if (ans == "yes") {
			cout << "your number is " << n << endl;
			answer_found = true;
		} else {
			cout << "is your guess bigger than " << n << endl;
			cin >> ans;
			if (ans == "yes")
				low = n + 1;
			else
				high = n - 1;
		}
	}
}

