//bzoj5427 最长上升子序列 二分+dp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7F7F7F7F
using namespace std;
int n,sm;
int tmp[2000021];
int *f;
char s[10];
void init()
{
	memset(tmp,0x7F,sizeof(tmp));
	for(int i=0;i<=100009;i++)
		tmp[i]=-inf;
	f=tmp+100009;
}
void ins(int x)
{
	*lower_bound(f+1,f+n+1,x-sm)=x-sm;
}
void add()
{
	f--;
	sm++;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("lis.in","r",stdin);
	freopen("lis.out","w",stdout);
#endif
	scanf("%d",&n);
	init();
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		if(s[0]=='K')
		{
			int a;
			scanf("%d",&a);
			ins(a);
		}
		else
			add();
	}
	printf("%d",lower_bound(f+1,f+n+1,inf)-f-1);
	return 0;
}