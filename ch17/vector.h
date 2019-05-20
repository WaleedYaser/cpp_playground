#pragma once

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T, typename A = allocator<T>>
class Vector
{
private:
	A alloc;
	size_t sz;
	size_t space;
	T *elem;
public:
	Vector() : sz{0}, space{0}, elem{nullptr} { }

	explicit Vector(size_t s, T def = T())
		: sz{s}, space{s}, elem{alloc.allocate(sz)}
	{
		for (int i = 0; i < sz; ++i) alloc.construct(&elem[i], def);
	}

	Vector(initializer_list<T> lst)
		: sz{lst.size()}, elem{alloc.allocate(sz)}
	{ 
		for (int i = 0; i < sz; ++i) alloc.construct(&elem[i], lst.begin()[i]);
	}


	Vector(const Vector &v);
	Vector & operator = (const Vector &v);

	Vector(Vector &&v);
	Vector & operator = (Vector &&v);

	~Vector();

	T& operator [] (int i) { return elem[i]; }
	const T& operator [] (int i) const { return elem[i]; }

	T& at(int n);
	const T& at(int n) const;

	int size() const { return sz; }
	int capacity() const { return space; }

	void reserve(int newalloc);
	void resize(int newsize, T def = T());
	void push_back(const T& d);
};

template <typename T, typename A>
Vector<T, A>::Vector(const Vector<T, A> &v)
	: sz{v.sz}, elem{alloc.allocate(sz)}
{
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elem[i], v[i]);
}

template <typename T, typename A>
Vector<T, A> & Vector<T, A>::operator = (const Vector<T, A> &v)
{
	if (this == &v) return *this;

	if (space >= v.sz) {
		for (int i = 0; i < v.sz; ++i) alloc.construct(&elem[i], v[i]);
		sz = v.sz;
		return *this;
	}

	T *p = alloc.allocate(v.sz);
	for (int i = 0; i < v.sz; ++i) alloc.construct(&elem[i], v[i]);

	if (elem) {
		for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
		alloc.deallocate(elem);
	}
	elem = p;
	space = sz = v.sz;

	return *this;
}

template <typename T, typename A>
Vector<T, A>::Vector(Vector<T, A> &&v)
{
	elem = v.elem;
	sz = v.sz;
	space = v.space;

	v.elem = nullptr;
	v.sz = 0;
	v.space = 0;
}

template <typename T, typename A>
Vector<T, A> & Vector<T, A>::operator = (Vector<T, A> &&v)
{
	if (elem) {
		for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
		alloc.deallocate(elem);
	}

	elem = v.elem;
	sz = v.sz;
	space = v.space;

	v.elem = nullptr;
	v.sz = 0;
	v.space = 0;

	return *this;
}

template <typename T, typename A>
Vector<T, A>::~Vector()
{
	for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
	alloc.deallocate(elem, space);
}

template <typename T, typename A>
T& Vector<T, A>::at(int i)
{
	if (i < 0 || i >=sz) throw out_of_range();
	return elem[i];
}

template <typename T, typename A>
const T& Vector<T, A>::at(int i) const
{
	if (i < 0 || i >= sz) throw out_of_range();
	return elem[i]; 
}

template <typename T, typename A>
void Vector<T, A>::reserve(int newalloc)
{
	if (newalloc <= space) return;
	T *p = alloc.allocate(newalloc);
	for (int i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]);
	for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
	alloc.deallocate(elem, space);

	elem = p;
	space = newalloc;
}

template <typename T, typename A>
void Vector<T, A>::resize(int newsize, T def)
{
	reserve(newsize);
	for (int i = sz; i < newsize; ++i) alloc.construct(&elem[i], def);
	for (int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]);
	sz = newsize;
}

template <typename T, typename A>
void Vector<T, A>::push_back(const T&d)
{
	if (space == 0) reserve(8);
	else if (sz == space) reserve(2 * space);
	alloc.construct(&elem[sz++], d);
}