#include <iostream>
#include <cmath>

int main()
{
	using namespace std;

	int n = 0;
	int sum = 0;

	while (sum < 1000000000) {
		sum += pow(2, n);
		n++;
	}

	cout << n + 1 << endl;
}
