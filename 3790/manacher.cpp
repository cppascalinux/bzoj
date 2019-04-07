//bzoj3790 manacher+greedy
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
using namespace std;
int n;
char t[50009],s[100009];
int f[100009];
struct node
{
	int l,r;
	bool operator < (const node &o) const
	{
		return l<o.l;
	}
}q[100009];
void init()
{
	s[0]='@';
	for(rg i=0;i<n;i++)
	{
		s[i*2+1]='#';
		s[i*2+2]=t[i];
	}
	n=n*2+1;
	s[n]='#';
}
void solve()
{
	int mx=0,id=0;
	for(rg i=1;i<=n*2+1;i++)
	{
		int &p=f[i];
		if(i<mx)
			p=min(mx-i,f[2*id-i]);
		else
			p=1;
		while(s[i+p]==s[i-p])
			p++;
		if(i+p>mx)
		{
			mx=i+p;
			id=i;
		}
	}
}
int cal()
{
	for(rg i=1;i<=n;i++)
	{
		q[i].l=i-f[i]+1;
		q[i].r=i+f[i]-1;
	}
	sort(q+1,q+n+1);
	int mx=0,ans=0,tr=0,j=0;
	while(tr<n)
	{
		mx=0;
		while(q[j+1].l<=tr+1&&j+1<=n)
		{
			j++;
			mx=max(mx,q[j].r);
		}
		ans++;
		tr=mx;
	}
	return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("manacher.in","r",stdin);
	freopen("manacher.out","w",stdout);
	#endif
	while(~scanf("%s",t))
	{
		n=strlen(t);
		init();
		solve();
		printf("%d\n",cal()-1);
	}
	return 0;
}