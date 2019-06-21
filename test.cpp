#include <stdio.h>

struct A {
	char *s = "Hello, A!";

	A() {
		printf("%s\n", s);
	}
};


struct B : A {
	char *s = "Hello, B!";

	B() {
		printf("%s\n", s);
	}
};


int main()
{
	A a;
	B b;

	printf("A::s = %s\n", a.s);
	printf("B::s = %s\n", b.s);
	return 0;
}