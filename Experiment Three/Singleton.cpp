// encoding using GBK !!!
// ��������Ľ��д��һ��.txt�ı��ļ���
#include <iostream>
using namespace std;
class Singleton
{
private:
    static Singleton *s; // s ��һ��ָ��Singleton���ָ�룬���ھ�̬���ݳ�Ա��Ϊ����Singleton�������������ʼ��Ϊ nullptr��ȷ��ֻ�ܴ���һ�� Singleton �����
    Singleton() {}       // �����캯�����������˽�в��֣��û�����ͨ��������Singleton xxx���ķ�ʽ���ù��캯��ֱ�Ӷ��������

public:
    static Singleton *GetInstance()
    {
        if (s == nullptr)
            s = new Singleton();
        return s;
    } // ��̬��Ա����GetInstance()�������Ƿ������еľ�̬��Աs���õ���ǰ�������󣬲������á����캯��
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
// s ��һ��ָ��Singleton���ָ�룬���ھ�̬���ݳ�Ա��Ϊ����Singleton�������������ʼ��Ϊ nullptr��ȷ��ֻ�ܴ���һ�� Singleton �����

// 1.2 Please describe the meaning above the codes;
// �ô��붨����һ����ѭ�������ģʽ�� Singleton �ࡣ��ģʽȷ��ֻ�ܴ���һ�����ʵ�������ṩ�Ը�ʵ����ȫ�ַ��ʵ㡣GetInstance() ����ͨ����� s �Ƿ�Ϊ nullptr ������Ƿ��Ѿ�������һ�� Singleton ���ʵ��������ǣ��򴴽�һ����ʵ������������ s��Ȼ�󣬸÷������ش洢�� s �е�ʵ����ָ�롣
// ������������������ Singleton ��ʵ��ʱ�ͷž�̬��Ա s ��ָ����ڴ档��� s ��Ϊ nullptr����ʹ�� delete �������ͷ��ڴ棬�����һ����Ϣ��

// ���һ�д��붨���˾�̬��Ա���� s �������ʼ��Ϊ nullptr��
//  1.3 Correct errors you find if any.
