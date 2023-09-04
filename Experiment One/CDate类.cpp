#include <bits/stdc++.h>
using namespace std;
//using UTF-8 !! 
class CDate {
public:
    int Year;
    int Month;
    int Day;

    CDate(int year, int month, int day) :Year(year), Month(month), Day(day) {}  //使用year month day初始化类中的成员变量

    int span(CDate date)      //定义计算某两天间距的函数（calculate the number of days between two dates）
    {               
        return abs(dis(*this) - dis(date));  
    }

private:
    static int dis(CDate date) 
    {
        int daydatainmonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  //定义一个数组存储每月的天数
        int days = date.Day;
        for(int i = date.Month - 2; i >=0; --i)
            days += daydatainmonth[i];
        if(date.Month > 2 && IsLeapYear(date.Year))
            ++days;
        for(int i = date.Year -1; i >=1; --i)
            days += IsLeapYear(i) ? 366 :365;
        return days;
    }
    static bool IsLeapYear(int year) 
    {
        return ((year %4 ==0 && year %100 !=0) || (year %400 ==0)); //用于判断年份是否为闰年，返回一个布尔值（check if a year is a leap year）
    }
};

int main()           //定义测试函数，输出结果正确
{          
   CDate date1(2019, 7, 17);
   CDate date2(2023, 3, 10);
   cout << "The span between the two dates is: " << date2.span(date1) << endl;
}
