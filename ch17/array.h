

template <typename T, int N>
struct Array
{
	using value_type     = T;
	using size_type      = unsigned long;
	using iterator       = T*;
	using const_iterator = const T*;

	iterator begin() { return elem; }
	const_iterator begin() const { return elem; }
	iterator end() { return elem + N; }
	const_iterator end() const { return elem + N; }

	size_type size() const { return N; }

	T& operator[](int n) { return elem[n]; }
	const T& operator[](int n) const { return elem[n]; }

	T& at(int n)
	{
		if (n < 0 || n >= N) throw Out_Of_Range();
		return elem[n];
	}

	const T& at(int n) const { return at(n); }

	T* data() { return elem; }
	const T* data() const { return elem; }

private:
	T elem[N];
};