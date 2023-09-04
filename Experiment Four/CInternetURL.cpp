#include "stdc++.h"
#include "CMyString.h"
using namespace std;

//ʹ��release x64��������!

class CInternetURL
{
private:
	CMyString url;
	int urllength;
public:
	
	CInternetURL(const char* s) : url(s), urllength(url.getlen()) {} //ʹ�ó�Ա��ʼ���б��ʼ��Ա

	//�۲�url��ַ�ṹ���Է��֣�Domainλ��//��/֮�䣬���ҽ�//�͵�һ��'.'֮������ݸ�Ϊ��www
	//ͬ���أ�DomainCountryλ�ڵ�����'.'��/֮�䣬
	//DomainTypeλ�ڵڶ���'.'�͵�����'.'֮��
	//HomePageλ��/֮��
	//ֻҪ����CMyString�е�Find����Ѱ�ҵ�//��/��ÿ��'.'��λ�ã��ҵ���һ�����λ�ã�һ֮Ϊ�µ��������Mid����һ���µ�CMyString�ٽ��д�FindѰ����һ���ؼ����λ�ã�
	//�����ü�¼����ϼ򵥵���ѧ����Ϳ��Եõ����������ÿ�������CMyString����ʽ���

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

	CMyString geturl()  //���url���ӣ�����debug����֤
	{
		return url;
	}

	int getlen()  //���url���ӳ��ȣ�����debug����֤
	{
		return urllength;
	}
};

int main()
{
	//CInternetURL URL("https://www.tsinghua.edu.cn/jyjx.htm");  //ʹ���廪��ѧ������ѧ��վ��һ����֤���ɹ�
	CInternetURL URL("https://jwc.bit.edu.cn/index.htm");
	cout << URL.geturl() << endl; //���url����
	cout << URL.getlen() << endl; //���url���ӳ���
	cout << URL.GetDomain()<<endl; // The result is: www.bit.edu.cn
	cout << URL.GetDomainCountry()<< endl; // The result is: cn
	cout << URL.GetDomainType() << endl; // The result is: edu
	cout << URL.GetHomePage(); // The result is: index.htm
	return 0;
}
