#include <string>
#include <iostream>
#include <cmath>
using namespace std;

// ---------------------------CMyStack----------------------------------

class CMyStack
{
private:
	double *m_pTop;       // ջ��ָ��
	int m_iSize;        // ջ�б����Ԫ�ظ���
	int m_iCapacity;    // ջ������
public:
	CMyStack(int size);
	~CMyStack();
	double Pop();         // ��ջ
	double Peek();        // ���ջ��Ԫ��
	bool Push(double ch); // ��ջ
	bool isEmpty();       // �ж��Ƿ�ջ��
	bool isFull();        // �ж��Ƿ�ջ��
	int  GetSize();       // ���ջ��Ԫ�ظ���
	void Clear();         // ���ջ
};

CMyStack::CMyStack(int size) : m_iCapacity(size)
{
	m_iSize = 0;

	m_pTop = new double[m_iCapacity];
}

CMyStack::~CMyStack()
{
	m_iSize = 0;
	m_iCapacity = 0;

	if (m_pTop != NULL)   // ע�⣺���û���жϣ���VS��������VC6�����
	{
		m_pTop = NULL;
		delete[] m_pTop;
	}
}

// ��ջ
double CMyStack::Pop()
{
	double ch = Peek();

	if (m_iSize > 0) m_iSize--;

	return ch;
}

// ���ջ��Ԫ��
double CMyStack::Peek()
{
	if (isEmpty())
		return ' ';
	else
		return m_pTop[m_iSize - 1];
}

// ��ջ
bool CMyStack::Push(double ch)
{
	if (isFull())  return false;

	m_pTop[m_iSize++] = ch;
	return true;
}

bool CMyStack::isEmpty()
{
	return m_iSize == 0;
}

bool CMyStack::isFull()
{
	return m_iCapacity == m_iSize;
}

// ���ջ��Ԫ�ظ���
int CMyStack::GetSize()
{
	return m_iSize;
}

// ���ջ
void CMyStack::Clear()
{
	m_iSize = 0;
}

// -------------------------CExperession-----------------------------

enum PRIORITY { LOWER, EQUALITY, HIGHER };  // ��ʾ����������ȼ�

class CExpression
{
public:
	CExpression(string s = "");
	double Value();               // ���ʽ��ֵ
	void SetExpression(string s); // ����һ��������ʽ
	friend ostream& operator<<(ostream& os, const CExpression& expr);// ��ӡ���ʽ���������ֵ
private:
	string m_strExpr;            // �������ı��ʽ
	CMyStack  stackOperator;     // ������ʽ�е������
	CMyStack  stackOperand;      // ������ʽ�еĲ�����

	PRIORITY Precede(char first, char second);   // �Ƚ�������������ȼ�
	bool isNumber(char ch);                      // �ж�һ���ַ��Ƿ��������ַ�
	double Compute(double x, double y, char ch); // ���㣺x ch y ���ʽ��ֵ
};

CExpression::CExpression(string s) : stackOperator(20), stackOperand(20)
{
	m_strExpr = s;
	stackOperator.Push('#');  // ���üٶ��������ջ��Ԫ�أ������ȼ����
}

void CExpression::SetExpression(string s)
{
	m_strExpr = s;

	stackOperand.Clear();
	stackOperator.Clear();
	stackOperator.Push('#');
}

double CExpression::Value()
{
	// �㷨˼�룺�������ʽ��
	// 1. ������ֱ����ջstackOperand��
	//    1.1 ��Ҫ���ǲ�������С���������
	// 2. ���������Ҫ��ջ��Ԫ�رȽ����ȼ���
	//    2.1 ������ȼ��ͣ�����ջstackOperator
	//    2.2 ���������ջ������������ջ����������󽫽����ջstackOperand
	// 3. ѭ��1��2��ֱ�����ʽ����������

	int index = 0;
	while (index < m_strExpr.length())
	{
		// 1. �����ǰ�ַ��������
		if (!isNumber(m_strExpr[index]))
		{
			// 1.1 �ȴ�������
			// 1.1.1 �������������ֱ����ջ
			if (m_strExpr[index] == '(')
			{
				stackOperator.Push('(');
			}
			// 1.1.2 �����������
			else if (m_strExpr[index] == ')')
			{
				// ���� ')' �����ʱ��ѭ�����㣺'(' �� ')' ֮��ı��ʽֵ�����������ջ��������ջ����
				// ֱ�������ջ��Ԫ���� '(' Ϊֹ��
				do {
					double x = stackOperand.Pop();
					double y = stackOperand.Pop();
					stackOperand.Push(Compute(y, x, (char)stackOperator.Pop()));
				} while (stackOperator.Peek() != '(');

				stackOperator.Pop();  // ������ '(' ��ջ
			}
			else // 1.2 ���������
			{
				// 1.2.1 �Ƚ���������ȼ�
				char c = m_strExpr[index];
				switch (Precede(m_strExpr[index], (char)stackOperator.Peek()))
				{
				case HIGHER:     // ��ǰ��������ȼ��ߣ���ֱ����ջ
					stackOperator.Push(m_strExpr[index]);
					break;

				case EQUALITY:  // ��������ȼ���ȣ�ʵ�����������ţ�����������ǰ���Ѿ�����
					break;

				case LOWER:    // ��ǰ��������ȼ��ͣ��������ջ�ȳ�ջ���㣬֮��ǰ���������ջ
					// 1.2.2 �����ջ��ջһ���������������ջ��ջ���������������м���
					double x = stackOperand.Pop();
					double y = stackOperand.Pop();
					stackOperand.Push(Compute(y, x, (char)stackOperator.Pop()));

					// 1.2.3 �������ջ
					stackOperator.Push(m_strExpr[index]);
					break;
				}
			}

			index++;
			continue;
		}

		// 2. �����ǰ�ַ��������ַ������ɲ�����������ջ
		double operand = 0;
		while (isNumber(m_strExpr[index]) || m_strExpr[index] == '.')
		{
			// 2.1 ��ǰ�ַ���С���㣬������С��
			if (m_strExpr[index] == '.')
			{
				index++;

				// 2.1.1 ����С�����������ַ�
				int i = 1;
				while (isNumber(m_strExpr[index]))
				{
					operand += ((int)(m_strExpr[index] - '0')) / pow(10, i);
					i++;
					index++;
				}
			}
			else // 2.2 ��ǰ�ַ��������ַ�������������
			{
				operand = operand * 10 + (int)(m_strExpr[index] - '0');
				index++;
			}
		}

		// 2.3 ��������ջ
		stackOperand.Push(operand);
	}

	// 3. ������ʽ������ջ����������ջֱ�Ӳ�������
	while (stackOperator.Peek() != '#')
	{
		double x = stackOperand.Pop();
		double y = stackOperand.Pop();
		stackOperand.Push(Compute(y, x, (char)stackOperator.Pop()));
	}

	return stackOperand.Pop();
}

ostream& operator<<(ostream& os, const CExpression& expr)
{
	return os << expr.m_strExpr;
}

// �Ƚ���������ȼ�
// first����ǰ�������second��ջ�������
PRIORITY CExpression::Precede(char first, char second)
{
	// 1. �������ȼ����
	// 2. �˳��� * / ���ȼ���֮
	// 3. �Ӽ��� + - ���ȼ����

	if (first == '#')  return LOWER;

	if (second == '#') return HIGHER;

	if (first == '+' || first == '-')
	{
		if (second == '(')
			return HIGHER;
		else
			return LOWER;
	}

	if (first == '*' || first == '/')
	{
		if (second == '+' || second == '-' || second == '(')
			return HIGHER;
		else
			return LOWER;
	}
}

// ���㣺x ch y ���ʽ��ֵ
double CExpression::Compute(double x, double y, char ch)
{
	double value;
	switch (ch)
	{
	case '+':
		value = x + y;
		break;
	case '-':
		value = x - y;
		break;
	case '*':
		value = x * y;
		break;
	case '/':
		value = x / y;
		break;
	}

	return value;
}

bool CExpression::isNumber(char ch)
{
	return ch >= '0' && ch <= '9';
}

int main()
{
	CExpression expr("50.3-20.12+8*8/2");
	cout << expr << " = " << expr.Value() << endl;      // 50.3-20.12+8*8/2 = 62.18

	expr.SetExpression("55.99-88.11+77.12");
	cout << expr << " = " << expr.Value() << endl;      // 55.99-88.11+77.12 = 45

	expr.SetExpression("(39+11)*30+10/5");
	cout << expr << " = " << expr.Value() << endl;     // (39+11)*30+10/5 = 1502

	expr.SetExpression("39+12*(47+33)");
	cout << expr << " = " << expr.Value() << endl;     // 39+12*(47+33) = 999

	expr.SetExpression("20/(112-(10*1.2))/10-1.01");
	cout << expr << " = " << expr.Value() << endl;     // 20/(112-(10*1.2))/10-1.01 = -0.99

	expr.SetExpression("20/(112-10*1.2)/10-1.01");
	cout << expr << " = " << expr.Value() << endl;     // 20/(112-10*1.2)/10-1.01 = -0.99

	cout << "ENDING..." << endl;
	return 0;
}