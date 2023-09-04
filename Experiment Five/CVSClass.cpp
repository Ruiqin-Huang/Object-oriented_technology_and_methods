#include <iostream>
#include <string>
using namespace std;

class Human  //���塰�ˡ���һ�࣬�����������Ա𣬳������µȻ�������
{
public:
	string name;
	string sex;
	string birthdate;
};

class Teacher : public Human   //���塰��ʦ���࣬��public��ʽ�̳�human�Ļ�������
{
public :
	string TID;
	Student* studentlist;//��ʦ���а���һ�ݡ�ѧ������ÿλ��ʦͨ����ݡ�ѧ��������ѧ��SID��ȡѧ��������Ϣ����ѧ������һ����Student����ɵı��
	                      //Teacher���Student�����������ϵ
	int ptr;
	int listlength;

	Teacher()
	{
		studentlist = new Student[500];
		ptr = 0;
		listlength = 0;
	}          

	Teacher(string namestr, string sexstr, string birthdatestr, string ID)  //��ʼ����ʦ������Ϣ
	{
		name = namestr;
		sex = sexstr;
		birthdate = birthdatestr;
		TID = ID;
	}

	void setstudentlist(const Student stu)  //��ѧ����Ϣ¼�롰ѧ������
	{
		Student temp = stu;
		studentlist[ptr] = temp;
		listlength++;
		ptr++;
	}

	void GetSInfoByID(string ID)    //ͨ������ѧ��SID��ѧ�������ҵ���Ӧѧ�����������ѧ������ϸ��Ϣ
	{
		for (int i = 0; i < listlength - 1; i++)
		{
			if (studentlist[i].SID == ID)
			{
				cout << "IDΪ " << ID << "��ѧ������ϢΪ" << endl 
					<< "ѧ������:" << studentlist[i].name << endl << "ѧ���Ա�:" 
					<< studentlist[i].sex << endl << "ѧ����������:" << studentlist[i].birthdate << endl;
			}
		}
	}

	void SetScore(Student stu,int num)    //����ѧ���ͳɼ���Ϊ��ѧ���ĸ��ſγ̵ĳɼ�����
	{
		for (int i = 0; i < stu.listlength - 1; i++)
		{
			if (stu.list[i].teacher.name == name)
			{
				stu.list[i].score = num;
				break;
			}
		}
	}
	~Teacher()    //�����ڹ��캯���С�ѧ��������new����ʽ�����ģ�������������������Ҫ�ֶ�����delete�ͷſռ�
	{
		delete[] studentlist;
	}
};

class Student : public Human  //Student��̳���Human�࣬������Human���еĻ�������
{
public:
	string SID;
	Course* list;   //����һ��ѧ�����Զ�Ӧ��ѡ�񣩶��ſγ̣�����һ����ѡ�α�����¼��ѧ����ѡ�޿γ̣�ѡ�α���һ��Course�������
	                //Student���Course�����������ϵ
	int ptr;
	int listlength;

	Student()
	{
		list = new Course[50];
		ptr = 0;
		listlength = 0;
	}
    
	Student(string namestr, string sexstr, string birthdatestr, string ID)  //��ʼ��ѧ��������Ϣ
	{
		list = new Course[50];
		ptr = 0;
		listlength = 0;
		name = namestr;
		sex = sexstr;
		birthdate = birthdatestr;
		SID = ID;
	}

	void Course_selection(Course course)   //����ѧ��ѡ�α�
	{
		Course temp = course;
		list[ptr] = temp;
		listlength++;
		ptr++;
	}

	void GetTeacherByCourse(string name) //ѧ��ͨ���γ������ڡ�ѡ�α����ҵ���Ӧ�γ̣���������Ӧ�Ľ�ʦ����
	{
		for (int i = 0; i < listlength - 1; i++)
		{
			if (list[i].crsname == name)
			{
				cout << "���ſγ̵��ν���ʦ�� " << list[i].teacher.name << endl;
				break;
			}
		}
	}
	
	void GetScoreByCourse(string name)  //ѧ��ͨ���γ������ڡ�ѡ�α����ҵ���Ӧ�γ̣���������ſγ̳ɼ�
	{
		for (int i = 0; i < listlength - 1; i++)
		{
			if (list[i].crsname == name)
			{
				cout << name << " ͬѧ" << "����" <<name<<"���ſγ̵ķ����� " << list[i].score << endl;
				break;
			}
		}
	}
	~Student()//�����ڹ��캯���С�ѡ�α�����new����ʽ�����ģ�������������������Ҫ�ֶ�����delete�ͷſռ�
	{
		delete[] list;
	}
};

class Course
{
public:
	string crsname;
	string crsID;
	int score;    //ÿ�ſγ���һ�����Խ����γ̷���
	Teacher teacher;
	
	Course()
	{

	}

	Course(string ID, string name, Teacher tchID)  //��ʼ���γ̻�����Ϣ
	{
		crsname = name;
		crsID = ID;
		teacher = tchID;
	}


	friend bool operator == (const Course& left, const Course& right) //����==�������ʵ��Course���Course��ĵ��ڱȽ�
	{
		return left.crsID == right.crsID;
	}

	void showname() {};
	void showteacherID() {};
	void showcourseID() {};

};

int main()
{
    //���ݱ�����룬���ݳ�ʼ��
	Teacher sunwukong("�����", "��", "1950.8", "t20011211");
	Teacher zhangsanfeng("������", "��", "1970.10", "t20160708");
	Course A("COM002", "��Ȼ�������", sunwukong);
	Course B("COM016", "������", zhangsanfeng);
	Student likui("����", "��", "1963.8", "20170801");
	Student huaqianyu("��ǧ��", "Ů", "1999.10", "20171011");
	Student TF_BOY("TF-BOY", "��", "2003.9", "20170901");
	Student lengbingbing("�����", "Ů", "2010.12", "20171217");  //���ÿγ̣���ʦ��ѧ��������Ϣ
	likui.Course_selection(A);
	huaqianyu.Course_selection(A);
	TF_BOY.Course_selection(B);
	lengbingbing.Course_selection(B);   //���ò�ͬѧ��ѡ����Ϣ
	sunwukong.setstudentlist(likui);
	sunwukong.setstudentlist(huaqianyu);
	sunwukong.setstudentlist(TF_BOY);
	sunwukong.setstudentlist(lengbingbing);
	zhangsanfeng.setstudentlist(likui);
	zhangsanfeng.setstudentlist(huaqianyu);
	zhangsanfeng.setstudentlist(TF_BOY);
	zhangsanfeng.setstudentlist(lengbingbing);  //��ѧ����Ϣ������λ��ʦ�ġ�ѧ����
	//����������֤
	sunwukong.SetScore(likui, 86);  
	zhangsanfeng.SetScore(TF_BOY, 100);
	likui.GetTeacherByCourse("��Ȼ�������");
	TF_BOY.GetTeacherByCourse("������");
	likui.GetScoreByCourse("��Ȼ���Դ���");
	TF_BOY.GetScoreByCourse("������");  
	
	sunwukong.GetSInfoByID("20170801");
	zhangsanfeng.GetSInfoByID("20171011");
	return 0;
}