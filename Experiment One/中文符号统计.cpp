#include <bits/stdc++.h>
using namespace std;

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
		    printf("常见中文符号对应的ASCⅡ码:\n"); 
		} 
        printf("%d",tx[j]);
        if(j%2 == 1)
        {
        	printf("\n");
		}
	}
	return 0;
}
