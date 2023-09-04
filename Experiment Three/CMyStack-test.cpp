// Create a class, CMyStack, to save double elements and implement the operations on the stack as follow members :
// 创建一个类CMyStack来保存浮点型元素，并将堆栈上的操作实现为以下成员：

// encoding using GBK !!!

#include <bits/stdc++.h>
using namespace std;

class CMyStack
{
private:
    double *m_pTop;  // Top pointer of stack
    int m_iSize;     // Number of actual elements
    int m_iCapacity; // Capacity of stack
public:
    CMyStack(int size);
    ~CMyStack();
    double Pop();
    double Peek(); // Get top element
    bool Push(double ch);
    bool isEmpty(); // Stack is empty?
    bool isFull();  // Stack is full?
    int GetSize();  // Get number of actual elements
    void Clear();   // Clear stack
};

CMyStack::CMyStack(int size)
{
    m_iCapacity = size;
    m_iSize = 0;
    m_pTop = new double[m_iCapacity + 1];
}

CMyStack::~CMyStack()
{
    delete[] m_pTop;
}

double CMyStack::Pop()
{
    if (!isEmpty())
    {
        double pop = Peek();
        m_iSize--;
        return pop;
    }
    else
    {
        cout << "Pop error! Stack is already Empty!" << endl;
        return -1;
    }
}

double CMyStack::Peek()
{
    if (!isEmpty())
    {
        return m_pTop[m_iSize];
    }
    else
    {
        cout << "Peek error! Stack is Empty!" << endl;
        return -1;
    }
}

bool CMyStack::Push(double ch)
{
    if (!isFull())
    {
        m_iSize++;
        m_pTop[m_iSize] = ch;
        return true;
    }
    else
    {
        cout << "Push error! Stack is already Full!" << endl;
        return false;
    }
}

bool CMyStack::isEmpty()
{
    if (m_iSize == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CMyStack::isFull()
{
    if (m_iSize == m_iCapacity)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int CMyStack::GetSize()
{
    return m_iSize;
}

void CMyStack::Clear()
{
    while (!isEmpty())
    {
        Pop();
    }
}

int main() // 测试
{
    CMyStack stack(4);
    stack.Push(1);
    stack.Push(2);
    int actualelement = stack.GetSize();
    cout << "当前栈中元素数量为：";
    cout << actualelement << endl;
    stack.Push(3);
    stack.Push(4);
    stack.Push(5); // stack最大承载量为4，当push第五个数时报错！
    double pop = stack.Pop();
    double top = stack.Peek();
    cout << "被弹出的数为：";
    cout << pop << endl;
    cout << "当前栈顶元素为：";
    cout << top << endl;
    stack.Clear();
    actualelement = stack.GetSize();
    cout << "当前栈中元素数量为：";
    cout << actualelement << endl;
}
