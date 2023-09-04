#include <bits/stdc++.h>
using namespace std;
//USING UTF-8 !!

int get_len(string data, int length)
{
	int cout = 0, i;
    for(i=0;i<length;i=i)
    {
        if(data[i] < 0)       //中文的ASCⅡ码占两个字节，且小于零
		{
			if((data[i] == -93)&&(data[i+1] == -84))
			{
			    i+=2;	
			} 
			else if((data[i] == -95)&&(data[i+1] == -93))
			{
				i+=2;
			}
			else if((data[i] == -93)&&(data[i+1] == -95))
			{
				i+=2;
			}
			else if((data[i] == -95)&&(data[i+1] == -80))
			{
				i+=2;
			}
			else if((data[i] == -95)&&(data[i+1] == -79))
			{
				i+=2;
			}
			else if((data[i] == -95)&&(data[i+1] == -82))
			{
				i+=2;
			}
			else if((data[i] == -95)&&(data[i+1] == -81))
			{
				i+=2;
			}
			else if((data[i] == -93)&&(data[i+1] == -65))
			{
				i+=2;
			}
			else if((data[i] == -95)&&(data[i+1] == -94))
			{
				i+=2;
			}
			else if((data[i] == -93)&&(data[i+1] == -69))
			{
				i+=2;
			}
			else if((data[i] == -93)&&(data[i+1] == -70))
			{
				i+=2;
			}
			else if((data[i] == -95)&&(data[i+1] == -86))
			{
				i+=2;
			}
			else
			{
				cout++;
			    i+=2;	
			}
		}                       //上述操作排除了文章中的中文标点符号，只计算了汉字个数
		else i++;
	}
    return cout;
} 

int main()
{
	string tx;
	tx = "，。、！？— “” ‘’；：";
	int j = 0;
	int lengthtx = tx.length();
	for(j=0;j<lengthtx;j++)
    {
		if(j == 0)
		{
		    printf("输出常见中文符号对应的ASCⅡ码:\n"); 
		} 
        printf("%d",tx[j]);
        if(j%2 == 1)
        {
        	printf("\n");
		}
	}
	
    ifstream ifobject("JourneyToWest.txt",ios_base::in);     //建立ifobject流读取文件内容
    string JTW,temp;
    int len = 0;
    while(getline(ifobject, temp))                          //按照行将文件内容读入JTW中
    {
        JTW+=temp;
        JTW+='\n';
    }
    ifobject.close();
    len = get_len(JTW, JTW.length());
	printf("\n\n\n");
	cout << "本文中汉字的数量为：" << endl;
    cout << len << endl;
	ifstream file("file.txt");            //再次打开文件，开始词频统计
    string word;
    map<string, int> wordcout;         //建立map统计不同词语的词频
    set<string> words_to_count = {"大圣", "玉帝", "王母娘娘", "仙女", "天王"};   //创建包含所有要统计的词语的集合
    while (file >> word) 
	{
        if (words_to_count.count(word)) 
		{
            wordcout[word]++;
        }
    }
    vector<pair<string, int>> word_vec(wordcout.begin(), wordcout.end());     
    sort(word_vec.begin(), word_vec.end(),[](const auto &a, const auto &b) { return a.second > b.second; });
     //使用sort对包含这五个词语及其计数的向量（vector）进行排序
    cout << "词频最高的两个词是：(The top 2 words with the highest frequency are:) " << endl;
    for (int i = 0; i < 2; ++i) 
	{
        cout << word_vec[i].first << ": " << word_vec[i].second << '\n';
    }                                        //结论，大圣，仙女为词频最高的两个词语
    return 0;
}
