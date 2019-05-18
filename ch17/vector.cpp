#include "vector.h"

Vector<int> fill()
{
	Vector<int> v(100);
	for (int i = 0; i < 1000; ++i)
		v[i] = i;
	return v;
}

int main()
{
	Vector<int> v1(5, 4);
	Vector<int> v2 = {1, 2, 3, 4, 5};
	Vector<int> v3 = v2;
	Vector<int> v4 = fill();
	v2[3] = 100;

	Vector<int> v5;
	for (int i = 0; i < 5; ++i)
		v5.push_back(i);
	v5.resize(100);

	for (int i = 0; i < 5; i++)
		cout << v1[i] << ", " << v2[i] << ", " << v3[i] << ", " << v4[i] << ", " << v5[i] << endl;
}

