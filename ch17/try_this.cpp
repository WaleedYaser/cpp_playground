#include "vector.h"

#include <iostream>

template <typename Iterator>
Iterator high(Iterator first, Iterator last)
{
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
		if (*p > *high) high = p;
	return high;
}

int main()
{
	double jack[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Vector<double> jill = {1, 2, 3, 4, 5, 6, 7};

	double *jack_high = high(jack, jack+9);
	double *jill_hight = high(&jill[0], &jill[0]+jill.size());

	cout << *jack_high << ", " << *jill_hight << endl;
}