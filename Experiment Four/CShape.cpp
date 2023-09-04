#include "stdc++.h"
using namespace std;
const double PI = 3.14159;

class CShape
{
public:
	virtual double Area() = 0; // area
	virtual double Volume() = 0; // volumn
};

class CSphere :public CShape //定义类：球，通过public方式继承父类CShape
{
public:
	CSphere(double a = 0) { r = a; }
	virtual double Area()    //虚函数复写
	{
		return 4 * PI * r * r;
	}
	virtual double Volume()
	{
		return 4 * PI * r * r * r / 3;
	}
private:
	double r;
};

class CCylinder :public CShape //定义类：圆柱，通过public方式继承父类CShape
{
public:
	CCylinder(double a = 0, double b = 0) { r = a; h = b; }
	virtual double Area()
	{
		return 2 * PI * r * r + 2 * PI * r * h;
	}
	virtual double Volume()
	{
		return h * PI * r * r ;
	}
private:
	double r, h;
};

class CAD
{
private:
	CShape& shape;
public:
	CAD(CShape& S) : shape(S) {}
	double Area() { return shape.Area(); }
	double Volume() { return shape.Volume(); }
};

int main()
{
	CSphere sphere(1);
	CCylinder cylinder(1, 2);
    CAD s(sphere);  
	CAD c(cylinder);
	cout << s.Area() << endl;
	cout << c.Volume() << endl;
}