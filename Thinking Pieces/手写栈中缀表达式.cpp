#include <string>
#include <iostream>
#include <cmath>
using namespace std;

// ---------------------------CMyStack----------------------------------

class CMyStack
{
private:
	double *m_pTop;       // 栈顶指针
	int m_iSize;        // 栈中保存的元素个数
	int m_iCapacity;    // 栈的容量
public:
	CMyStack(int size);
	~CMyStack();
	double Pop();         // 出栈
	double Peek();        // 获得栈顶元素
	bool Push(double ch); // 入栈
	bool isEmpty();       // 判断是否栈空
	bool isFull();        // 判断是否栈满
	int  GetSize();       // 获得栈中元素个数
	void Clear();         // 清空栈
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

	if (m_pTop != NULL)   // 注意：如果没有判断，则VS不出错，但VC6会出错
	{
		m_pTop = NULL;
		delete[] m_pTop;
	}
}

// 出栈
double CMyStack::Pop()
{
	double ch = Peek();

	if (m_iSize > 0) m_iSize--;

	return ch;
}

// 获得栈顶元素
double CMyStack::Peek()
{
	if (isEmpty())
		return ' ';
	else
		return m_pTop[m_iSize - 1];
}

// 入栈
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

// 获得栈中元素个数
int CMyStack::GetSize()
{
	return m_iSize;
}

// 清空栈
void CMyStack::Clear()
{
	m_iSize = 0;
}

// -------------------------CExperession-----------------------------

enum PRIORITY { LOWER, EQUALITY, HIGHER };  // 表示运算符的优先级

class CExpression
{
public:
	CExpression(string s = "");
	double Value();               // 表达式求值
	void SetExpression(string s); // 设置一个计算表达式
	friend ostream& operator<<(ostream& os, const CExpression& expr);// 打印表达式，但不输出值
private:
	string m_strExpr;            // 保存计算的表达式
	CMyStack  stackOperator;     // 保存表达式中的运算符
	CMyStack  stackOperand;      // 保存表达式中的操作数

	PRIORITY Precede(char first, char second);   // 比较两个运算的优先级
	bool isNumber(char ch);                      // 判断一个字符是否是数字字符
	double Compute(double x, double y, char ch); // 计算：x ch y 表达式的值
};

CExpression::CExpression(string s) : stackOperator(20), stackOperand(20)
{
	m_strExpr = s;
	stackOperator.Push('#');  // 设置假定的运算符栈底元素，其优先级最低
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
	// 算法思想：分析表达式，
	// 1. 操作数直接入栈stackOperand；
	//    1.1 需要考虑操作数有小数点的问题
	// 2. 运算符则需要与栈顶元素比较优先级，
	//    2.1 如果优先级低，则入栈stackOperator
	//    2.2 否则操作数栈两个操作数出栈，进行运算后将结果入栈stackOperand
	// 3. 循环1和2，直到表达式分析结束。

	int index = 0;
	while (index < m_strExpr.length())
	{
		// 1. 如果当前字符是运算符
		if (!isNumber(m_strExpr[index]))
		{
			// 1.1 先处理括号
			// 1.1.1 如果是左括号则直接入栈
			if (m_strExpr[index] == '(')
			{
				stackOperator.Push('(');
			}
			// 1.1.2 如果是右括号
			else if (m_strExpr[index] == ')')
			{
				// 当是 ')' 运算符时，循环计算：'(' 和 ')' 之间的表达式值，并将结果入栈（操作数栈）。
				// 直到运算符栈顶元素是 '(' 为止。
				do {
					double x = stackOperand.Pop();
					double y = stackOperand.Pop();
					stackOperand.Push(Compute(y, x, (char)stackOperator.Pop()));
				} while (stackOperator.Peek() != '(');

				stackOperator.Pop();  // 左括号 '(' 出栈
			}
			else // 1.2 其他运算符
			{
				// 1.2.1 比较运算符优先级
				char c = m_strExpr[index];
				switch (Precede(m_strExpr[index], (char)stackOperator.Peek()))
				{
				case HIGHER:     // 当前运算符优先级高，则直接入栈
					stackOperator.Push(m_strExpr[index]);
					break;

				case EQUALITY:  // 运算符优先级相等，实际是左右括号，而左右括号前面已经处理
					break;

				case LOWER:    // 当前运算符优先级低，则运算符栈先出栈运算，之后当前运算符再入栈
					// 1.2.2 运算符栈出栈一个运算符，操作数栈出栈两个操作数，进行计算
					double x = stackOperand.Pop();
					double y = stackOperand.Pop();
					stackOperand.Push(Compute(y, x, (char)stackOperator.Pop()));

					// 1.2.3 运算符入栈
					stackOperator.Push(m_strExpr[index]);
					break;
				}
			}

			index++;
			continue;
		}

		// 2. 如果当前字符是数字字符，生成操作数，并入栈
		double operand = 0;
		while (isNumber(m_strExpr[index]) || m_strExpr[index] == '.')
		{
			// 2.1 当前字符是小数点，则生成小数
			if (m_strExpr[index] == '.')
			{
				index++;

				// 2.1.1 处理小数点后的数字字符
				int i = 1;
				while (isNumber(m_strExpr[index]))
				{
					operand += ((int)(m_strExpr[index] - '0')) / pow(10, i);
					i++;
					index++;
				}
			}
			else // 2.2 当前字符是数字字符，则生成整数
			{
				operand = operand * 10 + (int)(m_strExpr[index] - '0');
				index++;
			}
		}

		// 2.3 操作数入栈
		stackOperand.Push(operand);
	}

	// 3. 计算表达式分析入栈结束，两个栈直接操作即可
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

// 比较运算符优先级
// first：当前运算符；second：栈顶运算符
PRIORITY CExpression::Precede(char first, char second)
{
	// 1. 括号优先级最高
	// 2. 乘除法 * / 优先级次之
	// 3. 加减法 + - 优先级最低

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

// 计算：x ch y 表达式的值
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