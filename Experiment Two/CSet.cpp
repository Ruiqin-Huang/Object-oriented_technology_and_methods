#include <bits/stdc++.h>
using namespace std;
// using UTF-8

class CSet
{
private:
    int *str;
    int ptr, max_size;

public:
    bool IsExist(int x);
    bool IsEqual(CSet another);
    void RemoveItem(int x);
    CSet Intersection(CSet another);
    CSet Union(CSet another);
    void AddItem(int x);
    void Show();
    CSet()
    {
        max_size = 50;
        str = new int[max_size];
        ptr = 0; // 定义数组元素指针
    }               //定义构造函数，集合的最大容量是50个int型数据
};

bool CSet::IsExist(int x)
{
    for (int i = 0; i < ptr; i++)
    {
        if (str[i] == x)
        {
            return true;
        }
    }
    return false;
}

bool CSet::IsEqual(CSet another)
{
    if (ptr != another.ptr)
    {
        return false;
    }
    for (int i = 0; i < ptr; i++)
    {
        if (another.IsExist(str[i]) == false)
        {
            return false;
        }
    }
    return true;
} // 使用排除法，先判断两个集合元素数量是否相等，不相等则两集合不等，相等则进一步比较集合元素是否相等

void CSet::AddItem(int x)
{
    if (IsExist(x))
    {
        cout << "ERROR!This item already exists!" << endl;
    }
    else
    {
        if (ptr == max_size)
        {
            cout << "ERROR!This set is full!" << endl;
        }
        else
        {
            str[ptr] = x;
            ptr++;
            cout << "NO ERROR!ADD SUCCESSFULLY!" << endl;
        }
    }
}

void CSet::RemoveItem(int x)
{
    for (int i = 0; i < ptr; i++)
    {
        if (x == str[i])
        {
            for (int j = i + 1; j < ptr; j++)
            {
                str[j - 1] = str[j];
            }
            ptr--; // 注意该集合ptr要随之改变
            break;
        }
    }
}

CSet CSet::Intersection(CSet another)
{
    CSet y;
    for (int i = 0; i < ptr; i++)
    {
        if (another.IsExist(str[i]))
        {
            y.AddItem(str[i]);   //将另一个CSet的集合中与本CSet的集合中相同的元素加入y的集合中，建造交集
        }
    }
    return y;
}

CSet CSet::Union(CSet another)
{
    CSet y;
    for (int i = 0; i < ptr; i++)
    {
        y.AddItem(str[i]);         //先将本CSet类中的集合复制给y中的集合
    }
    for (int i = 0; i < another.ptr; i++)
    {
        if (!y.IsExist(another.str[i]))
        {
            y.AddItem(another.str[i]);       //将另一个集合中与y中不同的元素加入y的集合中，建造并集
        }
    }
    return y;
}

void CSet::Show()
{
    cout << "{";
    for (int i = 0; i < ptr; i++)
    {
        cout << str[i];
    }
    cout << "}" << endl;
}

int main() 
{
    CSet a, b; // 创建CSet类 a,b 用于测试
    cout << "向a中加入元素" << endl;
    a.AddItem(1);
    a.AddItem(2);
    a.AddItem(3);
    a.AddItem(3); // 存在重复元素，报错
    cout << "向b中加入元素" << endl;
    b.AddItem(3);
    b.AddItem(4);
    b.AddItem(5);
    // 现在a是{1，2，3}，b是{3，4，5}
    cout << endl;
    CSet d = a.Intersection(b);
    d.Show();//求a,b交集，得到结果{3},正确！
    CSet c = a.Union(b);
    c.Show();//求a,b并集，得到结果{1,2,3,4,5},正确！
}
