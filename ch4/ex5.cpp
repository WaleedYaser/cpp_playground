#include <iostream>

int main()
{
	using namespace std;

	double n1, n2;
	char op;

	cout << "please enter two double values and an operation: + - * /" << endl;
	cin >> n1 >> n2 >> op;
	switch (op) {
		case '+':
			cout << "the sum of " << n1 << " and " << n2 << " is "
				 << n1 + n2 << endl;
			break;
		case '-':
			cout << "the difference of " << n1 << " and " << n2 << " is "
				 << n1 - n2 << endl;
			break;
		case '*':
			cout << "the multiplication of " << n1 << " and " << n2 << " is "
				 << n1 * n2 << endl;
			break;
		case '/':
			if (n2 != 0)
				cout << "the division of " << n1 << " and " << n2 << "is "
					 << n1 / n2 << endl;
			else
				cout << "error: zero division!" << endl;
			break;
		default:
			cout << "wrong operation: " << op << endl;
			break;
	}
}
