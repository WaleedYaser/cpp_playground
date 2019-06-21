#include <vector>
#include <iostream>

using namespace std;

template <typename In, typename T>
In find(In first, In, In last, const T &val)
{
	while (first != last && *first != val) ++first;
	return first;
}

template <typename In, typename Pred>
In find_if(In first, In last, Pred pred)
{
	while (first != last && !pred(*first)) ++first;
	return first;
}

template <typename In, typename T>
T accumulate(In first, In last, T init)
{
	while (first != last) {
		init += *first;
		++first;
	}
	return init;
}

template <typename In, typename T, typename Bin_Op>
T accumulate(In first, In last, T init, Bin_Op op)
{
	while (first != last) {
		init = op(init, *first);
		++first;
	}
	return init;
}

template <typename In1, typename In2, typename T>
T inner_product(In1 first1, In1 last1, In2 first2, T init)
{
	while (first1 != last1) {
		init = init + (*first1) * (*first2);
		first1++;
		first2++;
	}
	return init;
}

template <typename In1, typename In2, typename T,
		  typename Bin_Op1, typename Bin_Op2>
T inner_product(In1 first1, In1 last1, In2 first2, T init,
				Bin_Op1 op1, Bin_Op2 op2)
{
	while (first != last) {
		init = op1(init, op2(*first1, *first2));
		++first1;
		++first2;
	}
	return init;
}

template <typename In, typename Out>
Out copy(In first, In last, Out res)
{
	while (first != last)
	{
		*res = *first;
		++first;
		++res;
	}
	return res;
}

class Larger_Than {
	int v;
public:
	Larger_Than(int vv) : v{vv} { }
	bool operator()(int x) const { return x > v; }
};

int main()
{
	vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	vector<int>::iterator p = find_if(v.begin(), v.end(),
									  Larger_Than(5));
	if (p != v.end())
		cout << "found " << *p << endl;

	cout << accumulate(v.begin(), v.end(), 1,
					  [](int x, int y) { return x * y; }) << endl;
}