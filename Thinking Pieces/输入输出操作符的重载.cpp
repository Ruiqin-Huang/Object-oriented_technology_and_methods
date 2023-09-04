#include <iostream>
using namespace std;

class A
{
private:
	int x, y;
public:
	A(int x1 = 0, int y1 = 0)
	{
		x = x1;
		y = y1;
	}
	friend istream& operator>>(istream& is, A& a);
	friend ostream& operator<<(ostream& os, const A& a);
};
istream& operator>>(istream& is, A& a)
{
	is >> a.x >> a.y;
	return is;
}
ostream& operator<<(ostream& os, const A& a)
{
	os << "x=" << a.x << "," << "y=" << a.y;
	return os;
}
int main()
{
	A a1(1, 2);
	cin >> a1;
	cout << a1;
	return 0;
}