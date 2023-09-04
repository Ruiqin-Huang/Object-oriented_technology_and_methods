#include <iostream>
using namespace std;

class human {
public:
	human(string name = "小明")
		:_name(name)
	{
		cout << name << endl;
	}
protected:
	string _name;
};
class student :public human {
public:
	student(string name, int age)
		:_age(age)
	{
		cout << name << endl << age << endl;
	}
	student(student& s)
		:human(s)//直接将st传过来通过切片拿到父类中的值
		, _age(s._age)//拿除了父类之外的值
	{
		cout << s._age << endl << s._name << endl;
	}
protected:
	int _age;
};
int main()
{
	student st("小红", 18);
	student st2(st);
	return 0;
}