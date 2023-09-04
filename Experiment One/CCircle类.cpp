#include <bits/stdc++.h>
using namespace std;    
//USING UTF-8 !!

class CCircle
{
    public:
    double x;
    double y;
    double r;

    int relationship(CCircle another)
    {
        double d = sqrt(pow(x - another.x, 2) + pow(y - another.y, 2));
        if(d > r + another.r) 
        {
            return 0; //返回0表示两圆相离(Indicates that two circles are separated)
        } 
        else if(d == r + another.r || d == abs(r - another.r))
        {
            return 1; //返回1表示两圆相切（包括内切和外切）(Indicates that two circles are tangent (including inscribed and circumscribed))
        }
        else if(d < r + another.r && d > abs(r - another.r))
        {
            return 2; //返回2表示两圆相交(Indicates that two circles intersect)
        }
        else if(d < abs(r - another.r))
        {
            return 3; //返回3表示两圆内含(Indicates that two circles contain)
        }
        else
        {
            return -1;
        }
    }
};


int main() {
    CCircle circle1,circle2;  //使用创建的类创建两个园用于测试
    circle1.x = 0;
    circle1.y = 0;
    circle1.r = 2;

    circle2.x = 3;
    circle2.y = 0;
    circle2.r = 1;       //样例测试（Sample test）

    int relation = circle1.relationship(circle2);     //调用circle1的relationship成员函数并将circle2作为参数传递（调用circle1的relationship成员函数并将circle2作为参数传递）
    if(relation == 0) {
        cout << "两圆相离(two circles are separated)" << endl;
    } 
    else if(relation == 1) {
        cout << "两圆相切(two circles are tangent (including inscribed and circumscribed))" << endl;
    }
    else if(relation == 2) {
        cout << "两圆相交(two circles intersect)" << endl;
    }
    else if(relation == 3) {
        cout << "两圆内含(two circles contain)" << endl;
    }
    //得到输出"两圆相切"
    return 0;
}