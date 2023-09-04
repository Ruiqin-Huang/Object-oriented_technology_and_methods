// encoding using GBK !!!
// 将三道题的解答写在一个.txt文本文件里
#include <iostream>
using namespace std;
class Singleton
{
private:
    static Singleton *s; // s 是一个指向Singleton类的指针，属于静态数据成员，为所有Singleton类对象共享，它被初始化为 nullptr，确保只能创建一个 Singleton 类对象。
    Singleton() {}       // 将构造函数定义在类的私有部分，用户不能通过类名“Singleton xxx”的方式调用构造函数直接定义类对象

public:
    static Singleton *GetInstance()
    {
        if (s == nullptr)
            s = new Singleton();
        return s;
    } // 静态成员函数GetInstance()，作用是访问类中的静态成员s，得到当前类名对象，并“调用”构造函数
    static void ReleaseInstance()
    {
        if (s != nullptr)
        {
            delete s;
            s = nullptr;
            cout << "Realease the static s." << endl;
        }
    }
};
Singleton *Singleton::s = nullptr;
int main()
{
    Singleton *ps;
    ps = Singleton::GetInstance();
    cout << ps << endl;
    Singleton::ReleaseInstance();
    return 0;
}

// 1.1 Please explain the member variable s;
// s 是一个指向Singleton类的指针，属于静态数据成员，为所有Singleton类对象共享，它被初始化为 nullptr，确保只能创建一个 Singleton 类对象。

// 1.2 Please describe the meaning above the codes;
// 该代码定义了一个遵循单例设计模式的 Singleton 类。该模式确保只能创建一个类的实例，并提供对该实例的全局访问点。GetInstance() 方法通过检查 s 是否为 nullptr 来检查是否已经创建了一个 Singleton 类的实例。如果是，则创建一个新实例并将其分配给 s。然后，该方法返回存储在 s 中的实例的指针。
// 析构函数用于在销毁 Singleton 类实例时释放静态成员 s 所指向的内存。如果 s 不为 nullptr，则使用 delete 操作符释放内存，并输出一条消息。

// 最后一行代码定义了静态成员变量 s 并将其初始化为 nullptr。
//  1.3 Correct errors you find if any.
