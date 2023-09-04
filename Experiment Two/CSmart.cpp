// Define a class of CSmart which can print how many objects of
// CSmart thare are in the program, and explain the results of the
// procedure.

#include <bits/stdc++.h>
using namespace std;
// using UTF-8

class CSmart
{
public:
    CSmart()
    {
        Numofcallsdestructor = 0;   //每次调用构造函数时则初始化析构函数被调用次数为0
        classobjnum++;
        if (classobjnum <= 1)
        {
            cout << classobjnum << "object" << endl;
        }
        else
        {
            cout << classobjnum << "objects" << endl;
        }
    }
    ~CSmart()
    {
        Numofcallsdestructor++;    //记录当前类对象的析构函数被调用次数
        if (Numofcallsdestructor == 1)   //若出现析构函数被多次调用情况则不继续向下执行
        {
            classobjnum--;
            if (classobjnum <= 1)
            {
                cout << classobjnum << "object" << endl;
            }
            else
            {
                cout << classobjnum << "objects" << endl;
            }
        }
    }

private:
    int Numofcallsdestructor;
    static int classobjnum;  //需要统计调用构造函数或者析构函数次数，所以建立static型变量
                             //以在不同类对象中共用
};


int CSmart::classobjnum = 0;

void DoSomething()
{
    CSmart s;
}

CSmart s1;

int main()
{
    CSmart s2;

    DoSomething();

    CSmart *s3 = new CSmart;
    delete s3;
    s2.~CSmart();
    return 0;
}