#include <bits/stdc++.h>
using namespace std;

void Show()
{
	cout << "Call Show function" << endl;
}

void Popmenu()
{
    cout << "Call Popmenu function"	<< endl;
}

void PressButton(void (*func)())   //将函数名（函数头指针）传入PressButton函数，以实现对函数的调用
{
    func();
}

int main()
{
	PressButton(Show);
	PressButton(Popmenu);          //PressButton作为函数的“按钮”存在
	return 0;
}
	
	
	
	

