//子类的operator=必须要显式调用父类的operator=完成父类的赋值。
//因为子类和父类的运算符，编译器默认给与了同一个名字，所以构成了隐藏，所以每次调用 = 这个赋值运算符都会一直调用子类，会造成循环，所以这里的赋值要直接修饰限定父类
#include <iostream>
using namespace std;	

class human {
public:
	human(string name = "小明")
		:_name(name)
	{
	}
	human& operator=(const human& p)
	{
		if (this != &p)//if (this != &p) 这一行代码的意义在于检查当前对象（由 this 指针指向）是否与传入的参数 p 指向同一个对象。
			//如果它们指向同一个对象，那么就不需要进行赋值操作，因为它们已经相等了。这是为了防止自我赋值的情况。
		{
			cout << "调用父类" << endl;
			_name = p._name;
		}
		return *this;
	}
protected:
	string _name;
};
class student :public human {
public:
	student(string name, int age)
		:_age(age)
	{
	}
	student(student& s)
		:human(s)
		, _age(s._age)
	{
	}
	student& operator=(const student& s)
	{
		if (this != &s)
		{
			cout << "调用了子类" << endl;
			human::operator=(s);//必须调用父类运算符
			_age = s._age;
			_name = s._name;
		}
		return *this;
	}
protected:
	int _age;
};
int main()
{
	student st("小红", 18);
	student st2(st);
	student st3("小刚", 16);
	st = st3;
	return 0;
}
