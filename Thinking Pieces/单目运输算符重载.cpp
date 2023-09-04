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
	A operator++()//++i ǰ��++ʵ��
	{
		++x;	//������
		++y;
		return *this;	//������
	}
	A operator++(int)	//i++ ����++ʵ��
	{
		//int����û���κ����壬ֻ��Ϊ��������ǰ�û��Ǻ�����ʽ,���۲�����������int����double��ʹ��(int)��ʶ
		A a = *this;	//�����������
		++(*this);	//����������ǰ��ʵ�ֵ�ǰ��++
		return a;	//������ǰ����Ķ���
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

