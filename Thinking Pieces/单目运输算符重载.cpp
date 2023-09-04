#include <iostream>
using namespace std;

class A
{
private:
	double x, y;
public:
	A(double x1 = 0, double y1 = 0)
	{
		x = x1;
		y = y1;
	}
	A operator++()//++i 前置++实现
	{
		++x;	//先自增
		++y;
		return *this;	//后引用
	}
	A operator++(int)	//i++ 后置++实现
	{
		//int参数没有任何意义，只是为了区分是前置还是后置形式,无论操作的数字是int还是double都使用(int)标识
		A a = *this;	//保存对象引用
		++(*this);	//自增，调用前面实现的前置++
		return a;	//返回先前保存的对象
	}
	void show()
	{
		cout << "x=" << x << "," << "y=" << y << endl;
	}
};
int main()
{
	A a1(1, 2), a2(3, 4);
	(a1++).show();
	(++a2).show();
	a1.show();
	return 0;
}

