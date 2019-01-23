#include <iostream>
#include <vector>

bool isprime(int n);

int main()
{
	using namespace std;

	vector<int> primes;
	for (int i = 1; i <= 100; ++i)
		if (isprime(i))
			primes.push_back(i);

	for (const int &x : primes)
		cout << x << endl;

	return 0;
}

bool isprime(int n)
{
	if (n == 1)
		return false;

	for (int i = 2; i < n; ++i)
		if (n % i == 0)
			return false;

	return true;
}
