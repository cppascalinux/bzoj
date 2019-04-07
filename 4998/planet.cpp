//2019.02.07
//bzoj4998 星球联盟 并查集
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define pii pair<int,int>
#define fi first
#define se second
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,p,tot;
int fn[200009],sz[200009];
pii e[400009];
int ont[400009];
int hd[200009],eg[400009],nxt[400009];
int fat[200009],dep[200009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
int fnd(int x)
{
	return x==fn[x]?x:fn[x]=fnd(fn[x]);
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	fat[x]=fa;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
			dfs(eg[i],x);
}
void init()
{
	for(int i=1;i<=n;i++)
		fn[i]=i;
	for(int i=1;i<=p;i++)
	{
		int x=e[i].fi,y=e[i].se;
		if(fnd(x)!=fnd(y))
		{
			fn[fnd(x)]=fnd(y);
			ins(x,y);
			ins(y,x);
			ont[i]=1;
		}
	}
	for(int i=1;i<=n;i++)
		if(fn[i]==i)
			dfs(i,0);
}
void solve()
{
	for(int i=1;i<=n;i++)
	{
		fn[i]=i;
		sz[i]=1;
	}
	for(int i=1;i<=p;i++)
	{
		if(ont[i])
		{
			if(i>m)
				printf("No\n");
			continue;
		}
		int x=e[i].fi,y=e[i].se;
		int fx=fnd(x),fy=fnd(y);
		while(fx!=fy)
		{
			if(dep[fx]<dep[fy])
				swap(fx,fy);
			x=fnd(fat[fx]);
			fn[fx]=x;
			sz[x]+=sz[fx];
			sz[fx]=0;
			fx=x;
		}
		if(i>m)
			printf("%d\n",sz[fx]);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("planet.in","r",stdin);
	freopen("planet.out","w",stdout);
#endif
	rd(n),rd(m),rd(p);
	p+=m;
	for(int i=1;i<=p;i++)
		rd(e[i].fi),rd(e[i].se);
	init();
	solve();
	return 0;
}