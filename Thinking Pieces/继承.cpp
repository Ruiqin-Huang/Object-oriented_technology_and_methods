#include <iostream>
using namespace std;

class human {//������һ�����࣬���ֽ�human
public:
	string name = "С��";//�������涨����һ��string���͵ĺ�һ��int����
	int age = 18;
};
class student :public human {//������һ����public��ʽ�̳и��������student
public:
	int schoolnum = 666;//�ڸ����name��age�Ļ�����������һ��schoolnum
	void print()
	{
		cout << name << endl << age << endl << schoolnum << endl;//���
	}
};
int main()
{
	student st;
	st.print();
	return 0;
}