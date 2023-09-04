#include <iostream>
using namespace std;
inline int f(int x) { return x * x; }
int main() {
	int x(2);
	cout << f(x + 1) << endl;
	cout << f(++x) << endl;
	cout << f(x++) << endl;
	return 0;
}