#include "stdc++.h"
using namespace std;

class CMyString {
private:
    char* str;
    int length;   //�������鳤�ȳ�Ա�����������������
public:
    CMyString()
    {
        str = nullptr;
        length = 0; 
    }

    CMyString(const char* s)
    {
        length = strlen(s);
        str = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            str[i] = s[i];
        }
        str[length] = '\0';
    }

    CMyString& operator = (const char* s)
    {
        if (str != nullptr) {
            delete[] str;
        }
        length = strlen(s);
        str = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            str[i] = s[i];
        }
        str[length] = '\0';
        return *this;
    }   //���ء�=����������á�=���ܽ�string��ֵ��CMyString��

    ~CMyString() 
    {
        delete[] str;
    }  //����str��new�õ��ģ�����������������Ӧ���ֶ�delete


    char& operator[](int i)   //����[]�������ʹ���ܹ�����CMyString�е�����
    {
        if (i >= 0 && i < length) //����Ƿ�Խ��
        {
            return str[i];
        }             
    }

    CMyString operator+(const CMyString& other) const  // �������+���������Σ��ڶ�������+ʵ������CMyString����
    {
        int newlen = length + other.length;
        char* temp = new char[newlen + 1];  //������ʱ����洢str
        for (int i = 0; i < length; i++)
        {
            temp[i] = str[i];
        }
        for (int i = 0; i < other.length; i++)
        {
            temp[length + i] = other.str[i];
        }
        temp[newlen] = '\0';
        CMyString out(temp); //ʹ����ʱ�����ʼ��out������out��ʽ����
        delete[] temp;  
        return out;
    }

    int Find(const char* s)  //Ѱ���Ӵ�
    {
        int len = strlen(s);
        int ptr = 0,temp;
        bool flag = false;
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] == s[ptr])
            {
                ptr++;
                if (ptr == len)
                {
                    flag = true;
                    temp = i;
                    break;
                }
                continue;
            }
            ptr = 0;
        }
        if (flag == true)
        {
            return temp - ptr + 1;
        }
        else
        {
            return -1;
        }
    }

    int Find(const char s)  //����Find��Ѱ�����ַ�
    {
        int temp;
        bool flag = false;
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] == s)
            {
                flag = true;
                temp = i;
                break;
            }
        }
        if (flag == true)
        {
            return temp;
        }
        else
        {
            return -1;
        }
    }

    CMyString Mid(int pos,int len)const
    {
        CMyString out;
        char* temp = new char[len + 1];
        for (int i = 0; i < len; i++)
        {
            temp[i] = str[pos + i];
        }
        temp[len] = '\0';
        out = temp;
        delete[] temp;
        return out;
    }

	int ToInt() //��stringת��Ϊinteger������
	{
		int count = 0;//���ڼ���������С�����
		if (Find('-') == -1)//�Ǹ��������
		{
			int i = length - 1;
			int j = 0;
			for (; i >= 0; i--)
			{
				count += (str[i]-'0') * (int)pow(10, j);  //str[i]��char��ʽ����Ҫ����ת��Ϊint��ʽ�ٲ������㣬pow��������double������ǿ��ת����int
				j++;
			}
			return count;
		}
		else  //���������
		{
			int i = length - 1;
			int j = 0;
			for (; i >= 1; i--)
			{
				count += (str[i] - '0') * (int)pow(10, j);
				j++;
			}
			return -count;
		}
	}
    

	double ToDouble()
	{
		double count1 = 0;//���ڼ���С����С�����
		if (Find('-') == -1)  //�Ǹ�С�����
		{
			int dot = Find('.');
			int i = length - (length  - (dot + 1)); //length - (dot + 1)�õ�С��λ����i��С����һλ��ʼ
			int j = -1;
			for (; i != length; i++)
			{
				count1 += (str[i] - '0') * pow(10, j);
				j--;
			}
			j = 0;
			i = length - (length  - (dot + 1)) - 2;//iָ��������һλ
			for (; i >= 0; i--)
			{
				count1 += (str[i] - '0') * pow(10, j);  
				j++;
			}
			return count1;
		}
		else  //��С�����
		{
			int dot = Find('.');
			int i = length - (length  - (dot + 1)); //length - (dot + 1)�õ�С��λ����i��С����һλ��ʼ
			int j = -1;
			for (; i != length; i++)
			{
				count1 += (str[i] - '0') * pow(10, j);
				j--;
			}
			j = 0;
			i = length - (length  - (dot + 1)) - 2;//iָ��������һλ
			for (; i >= 1; i--)
			{
				count1 += (str[i] - '0') * pow(10, j);
				j++;
			}
			return -count1;
		}
	}

    int getlen() const
    {
        return length;
    }

    friend ostream& operator<<(ostream& cout, const CMyString& s);
    friend CMyString operator+(const char* s1, const CMyString& s2);
};

ostream& operator<<(ostream& cout, const CMyString& s)  //����<<��ʵ�ֿ���ֱ��ʹ��<<���CMyString�����ں��ж��������û��*this����ֻ������Ϊ��Ԫ����
{
    cout << s.str;
    return cout;
}

CMyString operator+(const char* s1, const CMyString& s2) // �������+���������Σ���һ����char*��ʼ��һ���µ�CMyStringʵ������string+CMyStringת��Ϊ����CMyStringʵ�����
{
    CMyString temp(s1);
    return temp + s2;
}

int main()
{
    CMyString s1("BIT"), s2;
    s2 = "love";
    s2[0] = 'L';
    cout << s2 << endl;
    cout << "I " + s2 << " " << s1 << endl << endl;             // The output is: I Love BIT
    int pos = s1.Find('T');                               // pos is 2, or -1 if 'T' is not found.
    cout << pos << endl;
    pos = s1.Find("IT");                                  // pos is 1, or -1 if "IT" is not found.
    cout << pos << endl;
    pos = s1.Find("b");                                   // pos is -1
    cout << pos << endl;
    cout << endl;
    int startPos = 1, len = 2;
    //startPos represents starting position, len represents the length of substring. So Mid can
    // get a substring : ov.
    CMyString my = s2.Mid(startPos, len);
    cout << my << endl;
    cout << endl;
    CMyString str_num("123");
    int a = str_num.ToInt();
    cout << a << endl;
    cout << endl;
    str_num = "-123.456";
    double b = str_num.ToDouble();
    cout << b << endl;
    return 0;
}