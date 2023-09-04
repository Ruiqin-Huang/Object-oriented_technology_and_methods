// encoding using GBK !!!
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