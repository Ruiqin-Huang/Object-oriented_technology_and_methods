#include <iostream>
using namespace std;

class human {
public:
	human(string name = "С��")
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
		:human(s)//ֱ�ӽ�st������ͨ����Ƭ�õ������е�ֵ
		, _age(s._age)//�ó��˸���֮���ֵ
	{
		cout << s._age << endl << s._name << endl;
	}
protected:
	int _age;
};
int main()
{
	student st("С��", 18);
	student st2(st);
	return 0;
}