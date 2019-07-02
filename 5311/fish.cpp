//2019.07.02
//bzoj5311 CF321E 贞鱼 首先不难发现,每次增加一辆车,对答案的贡献是单调不增的,也就是下凸的,因此可以直接wqs二分,然后暴力dp,时间复杂度O(n^2logn)
//然而这样还是过不了,于是发现写出dp转移方程:f[i]=min(f[j]-s[i,j])+s[i,i]-w,不难发现如果j<k,且f[j]-s[i,j]>=f[k]-s[i,k],那么j将永远不会比k优
//因此对于两个数j<k,可以通过二分求出k比j优的最早时间,于是可以用单调队列去维护所有的决策点,队列内位置单调增,dp值单调增,同时q[i+1]比q[i]优的最早时间也单调增
//(因为假如时间不单调增的话,它在到达队首之间就被取代了,一定没有用),这样队首就是最优决策点,算dp值之前弹队首,算完之后再把dp值插入队尾即可(决策单调性优化)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define pii pair<int,int>
#define fi first
#define se second
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
int s[4009][4009];
int f[4009],g[4009];
pii q[4009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
int gett(int a,int b)//the earliest time for b to be better than a
{
	int l=1,r=n+1,v=f[b]-f[a];
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(s[mid][b]-s[mid][a]!=v?s[mid][b]-s[mid][a]>v:g[b]>g[a])
			r=mid;
		else
			l=mid+1;
	}
	return l;
}
int check(int w)
{
	int hd=1,bk=0;
	memset(f,0x7F,sizeof(f));
	memset(g,0,sizeof(g));
	f[0]=0;
	q[++bk]=pii(0,n+1);
	for(int i=1;i<=n;i++)
	{
		while(hd<=bk&&q[hd].se<=i)
			hd++;
		int x=q[hd].fi;
		f[i]=f[x]+s[i][i]-s[i][x]-w;
		g[i]=g[x]+1;
		while(hd<=bk-1&&gett(q[bk].fi,i)<=q[bk-1].se)
			bk--;
		q[bk].se=gett(q[bk].fi,i);
		q[++bk]=pii(i,n+1);
	}
	return g[n]>=m;
}
void solve()
{
	int l=-1000000000,r=1000000000;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	// printf("l:%d\n",l);
	check(l);
	printf("%d",f[n]+l*m);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("fish.in","r",stdin);
	freopen("fish.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			rd(s[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			s[i][j]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
	// for(int i=1;i<=n;i++)
	// {
	// 	for(int j=1;j<=n;j++)
	// 		printf("%d ",s[i][j]);
	// 	printf("\n");
	// }
	solve();
	return 0;
}