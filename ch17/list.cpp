#include <string>
#include <iostream>

using namespace std;

class Link
{
public:
	string value;

	Link(const string &v, Link *p = nullptr, Link *s = nullptr)
		: value{v}, prev{p}, succ{s} { }

	Link * insert(Link *n);
	Link * add(Link *n);
	Link * erase(Link *n);
	Link * find(const string &s) const;
	Link * advance(int n) const;

	Link * next() const { return succ; }
	Link * previous() const { return prev; }
private:
	Link *prev;
	Link *succ;
};

Link * Link::insert(Link *n)
{
	if (!n) return this;

	n->succ = this;
	if (prev) prev->succ = n;
	n->prev = prev;
	prev = n;

	return n;
}

Link * Link::add(Link *n)
{
	if (!n) return this;

	if (succ) succ->prev = n;
	n->succ = succ;
	succ = n;
	n->prev = this;

	return n;
}

Link * Link::erase(Link *p)
{
	if (!p) return nullptr;
	if (p->succ) p->succ->prev = p->prev;
	if (p->prev) p->prev->succ = p->succ;
	return p->succ;
}

Link * Link::find(const string &s) const
{
	Link *p = const_cast<Link *>(this);

	while (p) {
		if (p->value == s) return p;
		p = p->succ;
	}
	return nullptr;
}

Link * Link::advance(int n) const
{
	Link *p = const_cast<Link *>(this);

	if (n > 0) {
		while (n--) {
			if (p->succ == nullptr) return nullptr;
			p = p->succ;
		}
	}
	else if (n < 0) {
		while (n++) {
			if (p->prev == nullptr) return nullptr;
			p = p->prev;
		}
	}
	return p;
}

int main()
{
	Link *norse_gods = new Link("Thor");					// Thor
	norse_gods = norse_gods->insert(new Link("Odin"));
	norse_gods = norse_gods->insert(new Link("Freia"));

	norse_gods->add(new Link("Waleed"));
	Link *res = norse_gods->find("Odin");
	if (res) norse_gods->erase(res);

	for (int i = 0; i < 3; ++i)
		cout << norse_gods->advance(i)->value << endl;

	do {
		cout << norse_gods->value << endl;
	}
	while (norse_gods = norse_gods->next());
	
}