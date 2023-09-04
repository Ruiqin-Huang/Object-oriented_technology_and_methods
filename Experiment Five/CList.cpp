#include "stdc++.h"
using namespace std;

class CStudent
{
private:
	string name;
	int age;
public:
	string getname()
	{
		return name;
	}
	int getage()
	{
		return age;
	}

	CStudent()
	{

	}

	CStudent(string namestr, int ageint)   //��ʼ��ѧ��������Ϣ
	{
		name = namestr;
		age = ageint;
	}

	friend bool operator == (CStudent left, CStudent right)   //�ٴ�����==���������CStudent���CStudent��ıȽ�����Ϊ��Ӧ����ıȽ�
	{
		return left.getage() == right.getage();
	}
};

template<class K>
class CList
{
private:
	int capacity;
	K* list;
	int ptr;
	int listlength;

public:
	CList(int capacityint)  //��ʼ��Clist��ʹ��new����list��list��һ����CStudent��ΪԪ�ص�����
	{
		capacity = capacityint;
		list = new K[capacity];
		ptr = 0;
		listlength = 0;
	}
	bool IsFULL()   //�ж�list�Ƿ��Ѿ�����
	{
		if (listlength == capacity)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsEMPTY()  //�ж�list�Ƿ�Ϊ��
	{
		if (listlength == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Add(const K& x)
	{
		if (!IsFULL())
		{
			list[ptr] = x;
			listlength++;
			ptr++;
		}
		else
		{
			cout << "ADD ERROR!THIS LIST IS ALREADY FULL!" << endl;
		}
	}
	void Delete(const K& x)
	{
		if (!IsEMPTY())
		{
			int index = -1;
			for (int i = 0; i < listlength; i++)
			{
				if (list[i] == x)
				{
					index = i;
					break;
				}
			}
			if (index == -1)
			{
				cout << "THE GIVEN STUDENT IS NOT FOUND IN THE LIST!" << endl;
			}
			else
			{
				for (int i = index; i < listlength - 1; i++)
				{
					list[i] = list[i + 1];
				}
				listlength--;
				ptr--;
				cout << "delete SUCCESSFULLY!" << endl;
			}
		}
	}//ʹ��һ��ѭ��������Ҫɾ����Ԫ�� x ������������ҵ������Ԫ�أ�ʹ����һ��ѭ����������������Ԫ����ǰ�ƶ�һλʵ��delete����󣬸��� listlength �� ptr ��ֵ
	int getlistlength()
	{
		return listlength;
	}

	K& operator[](int i)   //����[]�������ʹ���ܹ�����CMyString�е�����
	{
		return list[i];
	}
	friend bool operator == (const K& left, const K& right)//��һ������==�������ʵ��CStudent���CStudent��ıȽ�
	{
		return left == right;
	}

	~CList()
	{
		delete[] list;
	}
};


int main()
{
	CStudent s1("Joan", 22), s2("John", 19);
	CList<CStudent> listStudent(50); // 50 is capcity of List
	listStudent.Add(s1);//��֤add����
	listStudent.Add(s2);
	if (listStudent[0] == listStudent[1]) // Two students have same age.
		cout << "Equal." << endl;
	else
		cout << "Not equal." << endl;
	CStudent s3("Mike", 34), s4("Julia", 26);
	listStudent.Add(s3);
	listStudent.Add(s4);
	listStudent.Delete(s3);//��֤delete����
	return 0;
}
