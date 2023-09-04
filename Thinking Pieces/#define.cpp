#include <iostream>
using namespace std;

#define f(x) (x)*(x)

int main()
{
	int a = 2;
	int b = f(++a);
	cout << b;
	cout << " " << a;
	return 0;
}