//�����operator=����Ҫ��ʽ���ø����operator=��ɸ���ĸ�ֵ��
//��Ϊ����͸�����������������Ĭ�ϸ�����ͬһ�����֣����Թ��������أ�����ÿ�ε��� = �����ֵ���������һֱ�������࣬�����ѭ������������ĸ�ֵҪֱ�������޶�����
#include <iostream>
using namespace std;	

class human {
public:
	human(string name = "С��")
		:_name(name)
	{
	}
	human& operator=(const human& p)
	{
		if (this != &p)//if (this != &p) ��һ�д�����������ڼ�鵱ǰ������ this ָ��ָ���Ƿ��봫��Ĳ��� p ָ��ͬһ������
			//�������ָ��ͬһ��������ô�Ͳ���Ҫ���и�ֵ��������Ϊ�����Ѿ�����ˡ�����Ϊ�˷�ֹ���Ҹ�ֵ�������
		{
			cout << "���ø���" << endl;
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
			cout << "����������" << endl;
			human::operator=(s);//������ø��������
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
	student st("С��", 18);
	student st2(st);
	student st3("С��", 16);
	st = st3;
	return 0;
}
