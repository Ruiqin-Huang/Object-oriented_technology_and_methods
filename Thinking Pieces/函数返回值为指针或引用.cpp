#include <iostream>
using namespace std;

int* f(int* x)
{
	(*x)++;
	// Safe, x is outside
	return x;
}
int& g(int& x)
{
	x++; // Same effect as in f()
	return x; // Safe
}

int main() {
	int a = 0, b;
	int* p;
	// Ugly (but explicit)
	p = f(&a);
	// Clean (but hidden)
	b = g(a);
	++*(p);
	++b;//��Ч,b������a������
	cout << a;
	return 0;
}