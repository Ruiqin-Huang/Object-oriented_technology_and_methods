// encoding using GBK !!!

#include <bits/stdc++.h>
#include "CMyStack.h"

using namespace std;

// Create a class , CExpression，to calculate the value of an expression which consists of numbers
// and operators such as +、-、*、/ and ( )。
// 创建一个类CExpression来计算由数字组成的表达式的值
// 以及运算符，如+、-、*、/和（）
class CExpression
{
private:
    int len;

public:
    string temp;
    double Value();
    int SetOutsidePriority(char op);
    int SetInsidePriority(double op);
    void SetExpression(string str);
    CExpression(string str)
    {
        temp = str;
        len = temp.length();
    }
    friend ostream &operator<<(ostream &os, const CExpression &expr); // 对输出流操作符进行重载   print only expression except its value
};

ostream &operator<<(ostream &os, const CExpression &expr)
{
    cout << expr.temp;
    return os;
}

double CExpression::Value()
{
    CMyStack num(len);
    CMyStack zhengshu(len);
    CMyStack xiaoshu(len); // 建立两个栈专门用于处理多位数字和小数情况
    CMyStack ope(len);
    num.Clear();
    ope.Clear();
    for (int i = 0; i < len; i++)
    {
        int count1; // 整数位数
        int count2; // 小数位数
        double integer = 0;
        double decimal = 0;                                                                                                                                                                      // 建立整数部分和小数部分值，用于最后将CMyStack zhengshu和CMyStack xiaoshu合成一个double型数字存入CMyStack num
        if (temp[i] >= '0' && temp[i] <= '9' && temp[i + 1] != '+' && temp[i + 1] != '-' && temp[i + 1] != '*' && temp[i + 1] != '/' && temp[i + 1] != '(' && temp[i + 1] != ')' && i + 1 < len) // 如果扫描到当前为数字并且下一个不是运算符，说明这个数字还没有扫描完成（是多位数或者小数）
        {
            zhengshu.Clear(); // 清空zhengshu以准备存储当前多位数或者小数
            xiaoshu.Clear();
            int count1 = 0; // 整数位数
            int count2 = 0; // 小数位数
            zhengshu.Push(static_cast<double>(temp[i] - '0'));
            count1++;
            while (temp[i + 1] >= '0' && temp[i + 1] <= '9' && i + 1 < len) // 下一个是数字，则入栈,i++
            {
                i++;
                count1++;
                zhengshu.Push(static_cast<double>(temp[i] - '0'));
            }
            // 现在i指向最后一个数字，i+1不是数字，可能是小数点，可能是运算符，我们分类讨论
            if (temp[i + 1] == '.' && i + 1 < len && i + 2 < len) // 小数情况
            {
                xiaoshu.Clear();
                i += 2;
                count2++;
                xiaoshu.Push(static_cast<double>(temp[i] - '0'));
                while (temp[i + 1] >= '0' && temp[i + 1] <= '9' && i + 1 < len)
                {
                    i++;
                    count2++;
                    xiaoshu.Push(static_cast<double>(temp[i] - '0'));
                }
                i++; // 此时i指向运算符
            }
            else // 仅仅是多位数但不是小数
            {
                i++; // 此时i指向运算符
            }
            // 执行合成
            for (int j = 0; j < count1; j++)
            {
                double temp = zhengshu.Pop();
                double powtemp = pow(10, j);
                integer += temp * powtemp;
            }
            for (int k = count2; k > 0; k--)
            {
                double temp = xiaoshu.Pop();
                double powtemp = pow(10, -k);
                decimal += temp * powtemp;
            }
            num.Push(integer + decimal); // 数字入栈
        }
        else if (temp[i] >= '0' && temp[i] <= '9' && (temp[i + 1] == '+' || temp[i + 1] == '-' || temp[i + 1] == '*' || temp[i + 1] == '/' || temp[i + 1] == '(' || temp[i + 1] == ')') && i + 1 < len) // i指向为数字，且i+1指向为运算符，说明为一位整数
        {
            zhengshu.Clear();
            xiaoshu.Clear();
            int count1 = 0; // 整数位数
            int count2 = 0; // 小数位数
            count1++;
            zhengshu.Push(static_cast<double>(temp[i] - '0'));
            i++; // 此时i指向运算符
            // 执行合成
            for (int l = 0; l < count1; l++)
            {
                double temp = zhengshu.Pop();
                double powtemp = pow(10, i);
                integer += temp * powtemp;
            }
            for (int m = count2; m > 0; m--)
            {
                double temp = xiaoshu.Pop();
                double powtemp = pow(10, -i);
                decimal += temp * powtemp;
            }
            num.Push(integer + decimal); // 数字入栈
        }
        else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '(' || temp[i] == ')' && i + 1 < len) // i指向运算符情况
        {
            if (ope.isEmpty()) // ope栈为空则直接入栈
            {
                ope.Push(static_cast<double>(temp[i])); // 运算符入栈
                i++;                                    // 此时i指向下一个对象，数字或者运算符
            }
            else // ope栈不为空情况
            {
                int thispriority = SetOutsidePriority(temp[i]);
                int peekpriority = SetInsidePriority(ope.Peek());
                if (thispriority > peekpriority) // 当前运算符优先级大于栈顶运算符
                {
                    ope.Push(static_cast<double>(temp[i]));
                    i++; // 此时i指向下一个对象，数字或者运算符
                }
                else // 当前运算符优先级小于或等于栈顶运算符，开始运算
                {
                    double num1, num2, out;
                    num1 = num.Pop();
                    num2 = num.Pop();
                    double op = ope.Pop();
                    if (op == static_cast<double>('+'))
                    {
                        out = num1 + num2;
                    }
                    else if (op == static_cast<double>('-'))
                    {
                        out = num1 - num2;
                    }
                    else if (op == static_cast<double>('*'))
                    {
                        out = num1 * num2;
                    }
                    else if (op == static_cast<double>('/'))
                    {
                        out = num1 / num2;
                    }
                    num.Push(out);
                    // 此时i指向的运算符尚未入栈，i仍保持指向该运算符
                }
            }
        }
    }
    return num.Peek();
}

int CExpression::SetOutsidePriority(char op) // 定义运算符在栈外优先级
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    else if (op == '(')
    {
        return 4;
    }
    else if (op == ')')
    {
        return -1;
    }
}

int CExpression::SetInsidePriority(double op) // 定义运算符在栈内优先级
{
    if (op == static_cast<double>('+') || op == static_cast<double>('-'))
    {
        return 1;
    }
    else if (op == static_cast<double>('*') || op == static_cast<double>('/'))
    {
        return 2;
    }
    else if (op == static_cast<double>('('))
    {
        return 0;
    }
    else if (op == static_cast<double>(')'))
    {
        return -1;
    }
}

void CExpression::SetExpression(string str)
{
    temp = str;
    len = temp.length();
}

int main()
{
    CExpression expr("50.3-20.12+8*8/2");
    cout << expr << " = " << expr.Value() << endl; // 50.3-20.12+8*8/2 = 62.18

    expr.SetExpression("55.99-88.11+77.12");
    cout << expr << " = " << expr.Value() << endl; // 55.99-88.11+77.12 = 45

    expr.SetExpression("(39+11)*30+10/5");
    cout << expr << " = " << expr.Value() << endl; // (39+11)*30+10/5 = 1502

    expr.SetExpression("39+12*(47+33)");
    cout << expr << " = " << expr.Value() << endl; // 39+12*(47+33) = 999

    expr.SetExpression("20/(112-(10*1.2))/10-1.01");
    cout << expr << " = " << expr.Value() << endl; // 20/(112-(10*1.2))/10-1.01 = -0.99

    expr.SetExpression("20/(112-10*1.2)/10-1.01");
    cout << expr << " = " << expr.Value() << endl; // 20/(112-10*1.2)/10-1.01 = -0.99

    cout << "ENDING..." << endl;
    return 0;
}
