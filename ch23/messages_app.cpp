#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

// line iterator
typedef vector<string>::const_iterator Line_Iter;

/*
 * Class for iterating over the message
 */
class Message
{
	Line_Iter first;
	Line_Iter last;

public:
	Message(Line_Iter p1, Line_Iter p2) : first{p1}, last{p2} { }
	Line_Iter begin() const { return first; }
	Line_Iter end() const { return last; }
};

// message iterator
using Mess_Iter = vector<Message>::const_iterator;

/*
 * class for iterating over the mail
 */
struct Mail_File
{
	string name;
	vector<string> lines;
	vector<Message> m;

	Mail_File(const string &n);

	Mess_Iter begin() const { return m.begin(); }
	Mess_Iter end() const { return m.end(); }
};

Mail_File::Mail_File(const string &n)
{
	ifstream in {n};
	if (!in) {
		cerr << "no " << n << "\n";
		exit(1);
	}

	for (string s; getline(in ,s); )
		lines.push_back(s);
	
	auto first = lines.begin();
	for (auto p = lines.begin(); p != lines.end(); ++p)
		if (*p == "----") {
			m.push_back(Message(first, p));
			first = p+1;
		}
}

int is_prefix(const string &s, const string &p)
{
	int n = p.size();
	if (string(s, 0, n)==p) return n;
	return 0;
}

bool find_from_addr(const Message &m, string &s)
{
	for (const auto &x : m)
		if (int n = is_prefix(x, "From: ")) {
			s = string(x, n);
			return true;
		}
	return false;
}

string find_subject(const Message &m)
{
	for (const auto &x : m)
		if (int n = is_prefix(x, "Subject: ")) return string(x, n);
	return "";
}

int main()
{
	Mail_File mfile {"my_mail_file.txt"};

	multimap<string, const Message*> sender;

	for (const auto &m : mfile) {
		string s;
		if (find_from_addr(m, s))
			sender.insert(make_pair(s, &m));
	}

	auto pp = sender.equal_range("John Doe <jdoe@machine.example>");
	for (auto p = pp.first; p != pp.second; ++p)
		cout << find_subject(*(p->second)) << '\n';
}