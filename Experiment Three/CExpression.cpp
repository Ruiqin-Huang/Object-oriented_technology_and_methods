// encoding using GBK !!!

#include <bits/stdc++.h>
#include "CMyStack.h"

using namespace std;

// Create a class , CExpression��to calculate the value of an expression which consists of numbers
// and operators such as +��-��*��/ and ( )��
// ����һ����CExpression��������������ɵı��ʽ��ֵ
// �Լ����������+��-��*��/�ͣ���
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
    friend ostream &operator<<(ostream &os, const CExpression &expr); // ���������������������   print only expression except its value
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
    CMyStack xiaoshu(len); // ��������ջר�����ڴ����λ���ֺ�С�����
    CMyStack ope(len);
    num.Clear();
    ope.Clear();
    for (int i = 0; i < len; i++)
    {
        int count1; // ����λ��
        int count2; // С��λ��
        double integer = 0;
        double decimal = 0;                                                                                                                                                                      // �����������ֺ�С������ֵ���������CMyStack zhengshu��CMyStack xiaoshu�ϳ�һ��double�����ִ���CMyStack num
        if (temp[i] >= '0' && temp[i] <= '9' && temp[i + 1] != '+' && temp[i + 1] != '-' && temp[i + 1] != '*' && temp[i + 1] != '/' && temp[i + 1] != '(' && temp[i + 1] != ')' && i + 1 < len) // ���ɨ�赽��ǰΪ���ֲ�����һ�������������˵��������ֻ�û��ɨ����ɣ��Ƕ�λ������С����
        {
            zhengshu.Clear(); // ���zhengshu��׼���洢��ǰ��λ������С��
            xiaoshu.Clear();
            int count1 = 0; // ����λ��
            int count2 = 0; // С��λ��
            zhengshu.Push(static_cast<double>(temp[i] - '0'));
            count1++;
            while (temp[i + 1] >= '0' && temp[i + 1] <= '9' && i + 1 < len) // ��һ�������֣�����ջ,i++
            {
                i++;
                count1++;
                zhengshu.Push(static_cast<double>(temp[i] - '0'));
            }
            // ����iָ�����һ�����֣�i+1�������֣�������С���㣬����������������Ƿ�������
            if (temp[i + 1] == '.' && i + 1 < len && i + 2 < len) // С�����
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
                i++; // ��ʱiָ�������
            }
            else // �����Ƕ�λ��������С��
            {
                i++; // ��ʱiָ�������
            }
            // ִ�кϳ�
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
            num.Push(integer + decimal); // ������ջ
        }
        else if (temp[i] >= '0' && temp[i] <= '9' && (temp[i + 1] == '+' || temp[i + 1] == '-' || temp[i + 1] == '*' || temp[i + 1] == '/' || temp[i + 1] == '(' || temp[i + 1] == ')') && i + 1 < len) // iָ��Ϊ���֣���i+1ָ��Ϊ�������˵��Ϊһλ����
        {
            zhengshu.Clear();
            xiaoshu.Clear();
            int count1 = 0; // ����λ��
            int count2 = 0; // С��λ��
            count1++;
            zhengshu.Push(static_cast<double>(temp[i] - '0'));
            i++; // ��ʱiָ�������
            // ִ�кϳ�
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
            num.Push(integer + decimal); // ������ջ
        }
        else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '(' || temp[i] == ')' && i + 1 < len) // iָ����������
        {
            if (ope.isEmpty()) // opeջΪ����ֱ����ջ
            {
                ope.Push(static_cast<double>(temp[i])); // �������ջ
                i++;                                    // ��ʱiָ����һ���������ֻ��������
            }
            else // opeջ��Ϊ�����
            {
                int thispriority = SetOutsidePriority(temp[i]);
                int peekpriority = SetInsidePriority(ope.Peek());
                if (thispriority > peekpriority) // ��ǰ��������ȼ�����ջ�������
                {
                    ope.Push(static_cast<double>(temp[i]));
                    i++; // ��ʱiָ����һ���������ֻ��������
                }
                else // ��ǰ��������ȼ�С�ڻ����ջ�����������ʼ����
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
                    // ��ʱiָ����������δ��ջ��i�Ա���ָ��������
                }
            }
        }
    }
    return num.Peek();
}

int CExpression::SetOutsidePriority(char op) // �����������ջ�����ȼ�
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

int CExpression::SetInsidePriority(double op) // �����������ջ�����ȼ�
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
