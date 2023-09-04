//说明：运算符重载为类的友元函数时，由于没有隐含的this指针(友元函数本身不属于类，在类的外面，所以不能在其中使用this)，因此，操作数的个数没有变化，所有的操作数都必须通过函数形参进行传递，函数的参数与操作数 自左自右保持一一对应。
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
	friend A operator+(const A& a, const A& b);
	void show()
	{
		cout << "x=" << x << "," << "y=" << y << endl;
	}
};
A operator+(const A& a, const A& b)
{
	return A(a.x + b.x, a.y + b.y);
}
int main()
{
	A a1(1, 2), a2(3, 4);
	A c;
	c = a1 + a2;
	c.show();
	return 0;
}