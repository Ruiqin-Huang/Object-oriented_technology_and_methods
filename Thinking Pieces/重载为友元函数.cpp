//˵�������������Ϊ�����Ԫ����ʱ������û��������thisָ��(��Ԫ�������������࣬��������棬���Բ���������ʹ��this)����ˣ��������ĸ���û�б仯�����еĲ�����������ͨ�������βν��д��ݣ������Ĳ���������� �������ұ���һһ��Ӧ��
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