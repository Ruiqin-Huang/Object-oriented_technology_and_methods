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

	CStudent(string namestr, int ageint)   //初始化学生基本信息
	{
		name = namestr;
		age = ageint;
	}

	friend bool operator == (CStudent left, CStudent right)   //再次重载==运算符，将CStudent类和CStudent类的比较重载为对应年龄的比较
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
	CList(int capacityint)  //初始化Clist，使用new创建list，list是一个以CStudent类为元素的数组
	{
		capacity = capacityint;
		list = new K[capacity];
		ptr = 0;
		listlength = 0;
	}
	bool IsFULL()   //判断list是否已经满了
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
	bool IsEMPTY()  //判断list是否为空
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
	}//使用一个循环来查找要删除的元素 x 的索引。如果找到了这个元素，使用另一个循环来将其后面的所有元素向前移动一位实现delete。最后，更新 listlength 和 ptr 的值
	int getlistlength()
	{
		return listlength;
	}

	K& operator[](int i)   //重载[]运算符，使其能够操作CMyString中的数组
	{
		return list[i];
	}
	friend bool operator == (const K& left, const K& right)//第一次重载==运算符，实现CStudent类和CStudent类的比较
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
	listStudent.Add(s1);//验证add函数
	listStudent.Add(s2);
	if (listStudent[0] == listStudent[1]) // Two students have same age.
		cout << "Equal." << endl;
	else
		cout << "Not equal." << endl;
	CStudent s3("Mike", 34), s4("Julia", 26);
	listStudent.Add(s3);
	listStudent.Add(s4);
	listStudent.Delete(s3);//验证delete函数
	return 0;
}
