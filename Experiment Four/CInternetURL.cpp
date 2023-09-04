#include "stdc++.h"
#include "CMyString.h"
using namespace std;

//使用release x64可以运行!

class CInternetURL
{
private:
	CMyString url;
	int urllength;
public:
	
	CInternetURL(const char* s) : url(s), urllength(url.getlen()) {} //使用成员初始化列表初始成员

	//观察url网址结构可以发现，Domain位于//和/之间，并且将//和第一个'.'之间的内容改为了www
	//同样地，DomainCountry位于第三个'.'和/之间，
	//DomainType位于第二个'.'和第三个'.'之间
	//HomePage位于/之后
	//只要利用CMyString中的Find函数寻找到//和/和每个'.'的位置（找到第一个点的位置，一之为新的起点利用Mid构造一个新的CMyString再进行次Find寻找下一个关键点的位置）
	//并做好记录，结合简单的数学计算就可以得到结果，并将每个结果以CMyString的形式输出

    CMyString GetDomain()
	{
		int p1 = url.Find("//");
		int dot1 = url.Find('.');
		int p2 = (url.Mid(p1 + 2, urllength - (p1 + 2))).Find("/");
		return "www." + url.Mid(dot1 + 1, p2 - 4);
	}

	CMyString GetDomainCountry()
	{
		int dot1 = url.Find(".");
		int dot2 = (url.Mid(dot1 + 1, urllength - (1 + dot1))).Find('.');
		int dot3 = (url.Mid(dot1 + dot2 + 2, urllength - (dot1 + dot2 + 2))).Find('.');
		int p1 = (url.Mid(dot1 + dot2 + dot3 + 3, urllength - (dot1 + dot2 + dot3 + 3))).Find('/');
		return url.Mid(dot1 + dot2 + dot3 + 3, p1);
	}

	CMyString GetDomainType()
	{
		int dot1 = url.Find(".");
		int dot2 = (url.Mid(dot1 + 1, urllength - (1 + dot1))).Find('.');
		int dot3 = (url.Mid(dot1 + dot2 + 2, urllength - (dot1 + dot2 + 2))).Find('.');
		return url.Mid(dot1 + dot2 +2, dot3);
	}

	CMyString GetHomePage()
	{
		int dot1 = url.Find(".");
		int dot2 = (url.Mid(dot1 + 1, urllength - (1 + dot1))).Find('.');
		int dot3 = (url.Mid(dot1 + dot2 + 2, urllength - (dot1 + dot2 + 2))).Find('.');
		int p1 = (url.Mid(dot1 + dot2 + dot3 + 3, urllength - (dot1 + dot2 + dot3 + 3))).Find('/');
		return url.Mid(dot1 + dot2 + dot3 + p1 + 4, urllength - (dot1 + dot2 + dot3 + p1 + 4));
	}

	CMyString geturl()  //输出url链接，便于debug和验证
	{
		return url;
	}

	int getlen()  //输出url链接长度，便于debug和验证
	{
		return urllength;
	}
};

int main()
{
	//CInternetURL URL("https://www.tsinghua.edu.cn/jyjx.htm");  //使用清华大学教育教学网站进一步验证，成功
	CInternetURL URL("https://jwc.bit.edu.cn/index.htm");
	cout << URL.geturl() << endl; //输出url链接
	cout << URL.getlen() << endl; //输出url链接长度
	cout << URL.GetDomain()<<endl; // The result is: www.bit.edu.cn
	cout << URL.GetDomainCountry()<< endl; // The result is: cn
	cout << URL.GetDomainType() << endl; // The result is: edu
	cout << URL.GetHomePage(); // The result is: index.htm
	return 0;
}
