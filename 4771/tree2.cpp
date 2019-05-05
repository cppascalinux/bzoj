//2019.05.05
//bzoj4771 七彩树 可持久化线段树合并(第一棵:颜色->最小深度 第二棵:深度->颜色数量和)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,tot;
int col[100009];
int hd[100009],eg[100009],nxt[100009];
void rd(int &x)
{
	char c=0;
	x=0;
	while(c<'0'||c>'9')
		c=gc();
	while(c>='0'&&c<='9')
		x=x*10+(c&15),c=gc();
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int t;
	rd(t);
	while(t--)
	{
		rd(n),rd(m);
		for(int i=1;i<=n;i++)
			rd(col[i]);
		for(int i=2,a;i<=n;i++)
		{
			rd(a);
			ins(a,i);
		}
	}
	return 0;
}