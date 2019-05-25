
template <typename T>
struct Link
{
	Link *prev;
	Link *succ;
	T    val;
};

template <typename T>
class List
{
public:
	class Iterator;

	Iterator begin()
	Iterator end();

	Iterator insert(Iterator p, const T &v);
	Iterator erase(Iterator p);

	void push_back(const T &v);
	void push_front(const T &v);
	void pop_front();
	void pop_back();

	T & front();
	T & back();

	Link<T> *first;
	Link<T> *last;
};

template <typename T>
class List<T>::Iterator
{
	Link<T>  *curr;
public:
	Iterator(Link<T> *p) : curr(p) { }

	Iterator & operator++() { curr = curr->succ; return *this; }
	Iterator & operator--() { curr = curr->prev; return *this; }
	T & operator*() { return curr->val; }

	bool operator==(const Iterator &b) const {return curr == b.curr; }
	bool operator!=(const Iterator &b) const { return curr != b.curr; }
};