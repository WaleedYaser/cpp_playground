#include <vector>
#include <list>
#include <iostream>

using namespace std;

using Line = vector<char>;

class Text_Iterator
{
	list<Line>::iterator ln;
	Line::iterator pos;
public:
	Text_Iterator(list<Line>::iterator ll, Line::iterator pp)
		: ln{ll}, pos{pp} { }
	
	char & operator*() { return *pos; }
	Text_Iterator & operator++();
	bool operator==(const Text_Iterator &other) const
	{
		return ln == other.ln && pos == other.pos;
	}
	bool operator!=(const Text_Iterator &other) const
	{
		return !(*this == other);
	}
};

Text_Iterator & Text_Iterator::operator++()
{
	++pos;
	if (pos == ln->end()) {
		++ln;
		pos = ln->begin();
	}
	return *this;
}


struct Document
{
	list<Line> line;
	Document() { line.push_back(Line()); }

	Text_Iterator begin()
	{
		return Text_Iterator(line.begin(), line.begin()->begin());
	}

	Text_Iterator end()
	{
		auto last = line.end();
		--last;
		return Text_Iterator(last, last->end());
	}
};

istream & operator>>(istream &is, Document &d)
{
	for (char ch; is.get(ch); ) {
		d.line.back().push_back(ch);
		if (ch == '\n')
			d.line.push_back(Line());
	}
	if (d.line.back().size()) d.line.push_back(Line());
	return is;
}

void print(Document &d)
{
	for (auto p : d) cout << p;
}

template <typename Iter>
void advance_iter(Iter &p, int n)
{
	while (n > 0) {
		++p; --n;
	}
	while (n < 0) {
		--p; ++n;
	}
}

void erase_line(Document &d, int n)
{
	if (n < 0 || n >= d.line.size()-1) return;
	auto p = d.line.begin();
	advance_iter(p, n);
	d.line.erase(p);
}

bool match(Text_Iterator first, Text_Iterator last, const string &s)
{
	for (auto c : s) {
		if (c != *first || first == last)
			return false;
		++first;
	}
	return true;
}

Text_Iterator find(Text_Iterator first, Text_Iterator last, char c)
{
	while (first != last) {
		if (*first == c)
			return first;
		++first;
	}
	return last;
}

Text_Iterator find_txt(Text_Iterator first, Text_Iterator last, const string &s)
{
	if (s.size()==0) return last;
	char first_char = s[0];
	while (true)
	{
		auto p = find(first, last, first_char);
		if (p==last || match(p, last, s)) return p;
		first = ++p;
	}
	
}

int main()
{
	Document d;
	cin >> d;
	//erase_line(d, 1);
	auto p = find_txt(d.begin(), d.end(), "template <typename T>");
	if (p == d.end())
		cout << "not found\n";
	else
		cout << "found\n";

	// auto p2 = find_txt(d.begin(), d.end(), "Waleed");
	// if (p2 == d.end())
	// 	cout << "Waleed not found\n";
	// else
	// 	cout << "Waleed found\n";

	print(d);
}