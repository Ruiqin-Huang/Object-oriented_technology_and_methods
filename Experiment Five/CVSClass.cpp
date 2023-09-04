#include <iostream>
#include <string>
using namespace std;

class Human  //定义“人”这一类，包含姓名，性别，出生年月等基本属性
{
public:
	string name;
	string sex;
	string birthdate;
};

class Teacher : public Human   //定义“教师”类，以public方式继承human的基本属性
{
public :
	string TID;
	Student* studentlist;//教师类中包含一份“学生表”，每位教师通过这份“学生表”根据学生SID获取学生基本信息，“学生表”是一个由Student类组成的表格
	                      //Teacher类和Student类存在依赖关系
	int ptr;
	int listlength;

	Teacher()
	{
		studentlist = new Student[500];
		ptr = 0;
		listlength = 0;
	}          

	Teacher(string namestr, string sexstr, string birthdatestr, string ID)  //初始化教师个人信息
	{
		name = namestr;
		sex = sexstr;
		birthdate = birthdatestr;
		TID = ID;
	}

	void setstudentlist(const Student stu)  //将学生信息录入“学生表”中
	{
		Student temp = stu;
		studentlist[ptr] = temp;
		listlength++;
		ptr++;
	}

	void GetSInfoByID(string ID)    //通过输入学生SID在学生表上找到对应学生，并输出该学生的详细信息
	{
		for (int i = 0; i < listlength - 1; i++)
		{
			if (studentlist[i].SID == ID)
			{
				cout << "ID为 " << ID << "的学生的信息为" << endl 
					<< "学生姓名:" << studentlist[i].name << endl << "学生性别:" 
					<< studentlist[i].sex << endl << "学生出生年月:" << studentlist[i].birthdate << endl;
			}
		}
	}

	void SetScore(Student stu,int num)    //输入学生和成绩，为该学生的该门课程的成绩赋分
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
	~Teacher()    //由于在构造函数中“学生表”是以new的形式创建的，所以在析构函数中需要手动调用delete释放空间
	{
		delete[] studentlist;
	}
};

class Student : public Human  //Student类继承了Human类，保留了Human类中的基本属性
{
public:
	string SID;
	Course* list;   //由于一名学生可以对应（选择）多门课程，建立一个“选课表”，记录该学生的选修课程，选课表是一个Course类的数组
	                //Student类和Course类存在依赖关系
	int ptr;
	int listlength;

	Student()
	{
		list = new Course[50];
		ptr = 0;
		listlength = 0;
	}
    
	Student(string namestr, string sexstr, string birthdatestr, string ID)  //初始化学生个人信息
	{
		list = new Course[50];
		ptr = 0;
		listlength = 0;
		name = namestr;
		sex = sexstr;
		birthdate = birthdatestr;
		SID = ID;
	}

	void Course_selection(Course course)   //创建学生选课表
	{
		Course temp = course;
		list[ptr] = temp;
		listlength++;
		ptr++;
	}

	void GetTeacherByCourse(string name) //学生通过课程名字在“选课表”中找到相应课程，并输出其对应的教师姓名
	{
		for (int i = 0; i < listlength - 1; i++)
		{
			if (list[i].crsname == name)
			{
				cout << "这门课程的任教老师是 " << list[i].teacher.name << endl;
				break;
			}
		}
	}
	
	void GetScoreByCourse(string name)  //学生通过课程名字在“选课表”中找到相应课程，并输出该门课程成绩
	{
		for (int i = 0; i < listlength - 1; i++)
		{
			if (list[i].crsname == name)
			{
				cout << name << " 同学" << "，你" <<name<<"这门课程的分数是 " << list[i].score << endl;
				break;
			}
		}
	}
	~Student()//由于在构造函数中“选课表”是以new的形式创建的，所以在析构函数中需要手动调用delete释放空间
	{
		delete[] list;
	}
};

class Course
{
public:
	string crsname;
	string crsID;
	int score;    //每门课程有一个属性叫做课程分数
	Teacher teacher;
	
	Course()
	{

	}

	Course(string ID, string name, Teacher tchID)  //初始化课程基本信息
	{
		crsname = name;
		crsID = ID;
		teacher = tchID;
	}


	friend bool operator == (const Course& left, const Course& right) //重载==运算符，实现Course类和Course类的等于比较
	{
		return left.crsID == right.crsID;
	}

	void showname() {};
	void showteacherID() {};
	void showcourseID() {};

};

int main()
{
    //数据表格输入，数据初始化
	Teacher sunwukong("孙悟空", "男", "1950.8", "t20011211");
	Teacher zhangsanfeng("张三丰", "男", "1970.10", "t20160708");
	Course A("COM002", "自然语言理解", sunwukong);
	Course B("COM016", "大数据", zhangsanfeng);
	Student likui("李逵", "男", "1963.8", "20170801");
	Student huaqianyu("花千羽", "女", "1999.10", "20171011");
	Student TF_BOY("TF-BOY", "男", "2003.9", "20170901");
	Student lengbingbing("冷冰冰", "女", "2010.12", "20171217");  //设置课程，教师，学生基本信息
	likui.Course_selection(A);
	huaqianyu.Course_selection(A);
	TF_BOY.Course_selection(B);
	lengbingbing.Course_selection(B);   //设置不同学生选课信息
	sunwukong.setstudentlist(likui);
	sunwukong.setstudentlist(huaqianyu);
	sunwukong.setstudentlist(TF_BOY);
	sunwukong.setstudentlist(lengbingbing);
	zhangsanfeng.setstudentlist(likui);
	zhangsanfeng.setstudentlist(huaqianyu);
	zhangsanfeng.setstudentlist(TF_BOY);
	zhangsanfeng.setstudentlist(lengbingbing);  //将学生信息存入两位老师的“学生表”
	//函数功能验证
	sunwukong.SetScore(likui, 86);  
	zhangsanfeng.SetScore(TF_BOY, 100);
	likui.GetTeacherByCourse("自然语言理解");
	TF_BOY.GetTeacherByCourse("大数据");
	likui.GetScoreByCourse("自然语言处理");
	TF_BOY.GetScoreByCourse("大数据");  
	
	sunwukong.GetSInfoByID("20170801");
	zhangsanfeng.GetSInfoByID("20171011");
	return 0;
}