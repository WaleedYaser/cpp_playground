#include <iostream>
#include <cmath>

int main()
{
	using namespace std;

	int n = 0;
	double sum = 0;

	while (n < 64) {
		sum += pow(2, n);
		cout << n << ": " << sum << endl;
		n++;
	}

	cout << sum << endl;
}
