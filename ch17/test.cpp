#include "vector.h"
#include "unique_ptr.h"
#include "array.h"

using namespace std;

Vector<int> fill()
{
	Vector<int> v(100);
	for (int i = 0; i < 100; ++i)
		v[i] = i;
	return v;
}


Unique_Ptr<Vector<int>> make_vec()
{
	Unique_Ptr<Vector<int>> p {new Vector<int>};

	for (int i = 0; i < 10; ++i) {
		p->push_back(i);
	}

	return p;
}


int main()
{
	Array<int, 10> a;
	for (auto &i : a) i = 5;
	for (const auto &i : a) cout << i << endl;
	Vector<int> v1(5, 4);
	Vector<int> v2 = {1, 2, 3, 4, 5};
	Vector<int> v3 = v2;
	Vector<int> v4 = fill();

	Unique_Ptr<Vector<int>> v5 = make_vec();
	v2[3] = 100;


	Vector<Vector<int>> v6 = { {10, 20, 30}, {40, 50, 60}, {1, 22, 46} };
	v6.insert(v6.begin()+1, {1, 2, 3});
	// v6.erase(v6.begin()+1);
	cout << v6.size() << endl;
	for (int i = 0; i < v6.size(); ++i)
		for (int j = 0; j < v6[i].size(); ++j)
			cout << v6[i][j] << endl;

	for (int i = 0; i < 4; i++)
		cout << v1[i] << ", " << v2[i] << ", " << v3[i] << ", " << v4[i] << ", " << v5->at(i) << endl;
}

