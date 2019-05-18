#include <initializer_list>
#include <iostream>
#include <algorithm>

using namespace std;

class Vector
{
private:
	int sz;
	double *elem;
public:
	Vector() : sz{0}, elem{nullptr} { }

	explicit Vector(int s)
		: sz{s}, elem{new double[s]}
	{
		for (int i = 0; i < s; ++i) elem[i] = 0;
	}

	Vector(initializer_list<double> lst)
		: sz{lst.size()}, elem{new double[sz]}
	{
		copy(lst.begin(), lst.end(), elem);
	}

	Vector(const Vector &v)
		: sz{v.sz}, elem{new double[sz]}
	{
		copy(v.elem, v.elem + sz, elem);
	}

	Vector(Vector &&v)
		: sz{v.sz}, elem{v.elem}
	{
		v.sz = 0;
		v.elem = nullptr;
	}

	int size() const { return sz; }

	double & operator [] (int i) const { return elem[i]; }
	Vector & operator = (const Vector & v)
	{
		double *p = new double[v.sz];
		copy(v.elem, v.elem+sz, p);

		if (elem) delete[] elem;
		elem = p;
		sz = v.sz;

		return *this;
	}
	Vector & operator = (Vector &&v)
	{
		if (elem) delete[] elem;

		elem = v.elem;
		sz = v.sz;

		v.elem = nullptr;
		v.sz = 0;

		return *this;
	}

	~Vector()
	{
		delete[] elem;
	}
};

Vector fill()
{
	Vector v(100);
	for (int i = 0; i < 1000; ++i)
		v[i] = i;
	return v;
}

int main()
{
	Vector v1(5);
	Vector v2 = {1, 2, 3, 4, 5};
	Vector v3 = v2;
	Vector v4 = fill();
	v2[3] = 100;

	for (int i = 0; i < 5; i++)
		cout << v1[i] << ", " << v2[i] << ", " << v3[i] << ", " << v4[i] << endl;
}

