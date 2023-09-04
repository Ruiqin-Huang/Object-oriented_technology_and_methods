#include "stdc++.h"
using namespace std;

class CMyString {
private:
    char* str;
    int length;   //建立数组长度成员变量，方便后续操作
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
    }   //重载‘=’运算符，让‘=’能将string赋值给CMyString类

    ~CMyString() 
    {
        delete[] str;
    }  //由于str是new得到的，所以在析构函数中应该手动delete


    char& operator[](int i)   //重载[]运算符，使其能够操作CMyString中的数组
    {
        if (i >= 0 && i < length) //检查是否越界
        {
            return str[i];
        }             
    }

    CMyString operator+(const CMyString& other) const  // 将运算符+重载了两次，第二次重载+实现两个CMyString连接
    {
        int newlen = length + other.length;
        char* temp = new char[newlen + 1];  //创建临时数组存储str
        for (int i = 0; i < length; i++)
        {
            temp[i] = str[i];
        }
        for (int i = 0; i < other.length; i++)
        {
            temp[length + i] = other.str[i];
        }
        temp[newlen] = '\0';
        CMyString out(temp); //使用临时数组初始化out，并以out形式返回
        delete[] temp;  
        return out;
    }

    int Find(const char* s)  //寻找子串
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

    int Find(const char s)  //重载Find，寻找子字符
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

	int ToInt() //将string转化为integer并返回
	{
		int count = 0;//用于计算整数大小并输出
		if (Find('-') == -1)//非负整数情况
		{
			int i = length - 1;
			int j = 0;
			for (; i >= 0; i--)
			{
				count += (str[i]-'0') * (int)pow(10, j);  //str[i]是char格式，先要将其转换为int格式再参与运算，pow（）返回double，将其强制转换成int
				j++;
			}
			return count;
		}
		else  //负整数情况
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
		double count1 = 0;//用于计算小数大小并输出
		if (Find('-') == -1)  //非负小数情况
		{
			int dot = Find('.');
			int i = length - (length  - (dot + 1)); //length - (dot + 1)得到小数位数，i从小数第一位开始
			int j = -1;
			for (; i != length; i++)
			{
				count1 += (str[i] - '0') * pow(10, j);
				j--;
			}
			j = 0;
			i = length - (length  - (dot + 1)) - 2;//i指向整数第一位
			for (; i >= 0; i--)
			{
				count1 += (str[i] - '0') * pow(10, j);  
				j++;
			}
			return count1;
		}
		else  //负小数情况
		{
			int dot = Find('.');
			int i = length - (length  - (dot + 1)); //length - (dot + 1)得到小数位数，i从小数第一位开始
			int j = -1;
			for (; i != length; i++)
			{
				count1 += (str[i] - '0') * pow(10, j);
				j--;
			}
			j = 0;
			i = length - (length  - (dot + 1)) - 2;//i指向整数第一位
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

ostream& operator<<(ostream& cout, const CMyString& s)  //重载<<，实现可以直接使用<<输出CMyString，由于含有多个参数（没有*this），只能重载为友元函数
{
    cout << s.str;
    return cout;
}

CMyString operator+(const char* s1, const CMyString& s2) // 将运算符+重载了两次，第一次用char*初始化一个新的CMyString实例，将string+CMyString转化为两个CMyString实例相加
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