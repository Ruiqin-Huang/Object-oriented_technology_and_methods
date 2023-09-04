#include <bits/stdc++.h>
using namespace std;
// using UTF-8

class CIntChar
{
public:
    CIntChar(const char *string)
    {
        body = 0;
        for (int i = 0; i < strlen(string); i++)
        {
            int shift = 8; // shift表示需要每次做按位或运算时需要向左移动的位数
            body = body << shift;
            body = body | string[i];
        }
    }
    // 遍历字符串中的每个字符，对于每个字符，
    // 都将其ASCII码值与body变量进行按位或运算。由于一个字符占用1个字节(8位)，
    // 所以在进行按位或运算之前，每次需要将body变量左移8位。保证每个字符的ASCII码存在body的不同字节

    void ASC_Print()
    {
        for (int i = 3; i >= 0; i--) //相当于上面的逆向运算
        {
            int shift = i * 8; // shift表示需要每次做按位与运算时需要向右移动的位数
            char c = body >> shift;
            c = c & 0xff; // 0xff就是二进制中的11111111
            if (c != '\0') //按位与运算得到'NULL'时，说明打印结束
                cout << c;
        }
        cout << endl;
    }

    void Binary_Print()
    {
        for (int i = 31; i >= 0; i--) //从31开始倒序遍历到0,保证打印出的二进制数字按从高位到低位顺序排列
        {
            int shift = i; // shift表示需要每次做按位与运算时需要向右移动的位数
            cout << ((body >> shift) & 1); //使用按位与1运算可以取出每位数字，并且能保证高位补0的需求
            if(i % 4 == 0)
            {
                cout << " ";
            } //美化
        }
        cout << endl;
    }

    void Int_Print()
    {
        cout << body << endl;
    }

private:
    int body;
};
int main()
{
    CIntChar IC("Love");
    IC.ASC_Print();    // Print the content with string format:Love
    IC.Binary_Print(); // Print the content with binary format:0100 1100 0110 1111 0111 0110 0110 0101
    IC.Int_Print();    // Print the content with integer format:1282373221
    return 0;
}