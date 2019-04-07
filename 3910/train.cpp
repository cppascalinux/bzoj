#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define get(a,b) (d[a]<d[b]?a:b)
using namespace std;
char *p1,*p2,buffer[10000010];
int n,m,s,top,tot;
ll ans;
int head[500010],edge[1000010],nxt[1000010];
int d[500010],pos[500010];
int st[1000010];
int f[1000010][30];
void read(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x<<3)+(x<<1)+(ch&15),ch=gc();
}
void ins(int a,int b)
{
	edge[++tot]=b;
	nxt[tot]=head[a];
	head[a]=tot;
}
void dfs(int x,int fa)
{
	d[x]=d[fa]+1;
	st[++top]=x;
	pos[x]=top;
	for(int i=head[x];i;i=nxt[i])
		if(edge[i]^fa)
		{
			dfs(edge[i],x);
			st[++top]=x;
		}
}
void init()
{
	for(rg i=1;i<=top;i++)
		f[i][0]=st[i];
	for(rg k=1;(1<<k)<=top;k++)
		for(rg i=1;i<=top-(1<<k)+1;i++)
			f[i][k]=get(f[i][k-1],f[i+(1<<(k-1))][k-1]);
}
int lca(rg a,rg b)
{
	if(pos[a]>pos[b])
		swap(a,b);
	int l=pos[a],r=pos[b];
	int len=r-l+1;
	int k=-1;
	while(1<<(k+1)<=len)
		k++;
	return get(f[l][k],f[r-(1<<k)+1][k]);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("train.in","r",stdin);
	freopen("train.out","w",stdout);
	#endif
	read(n);
	read(m);
	read(s);
	// printf("n:%d m:%d s:%d\n",n,m,s);
	// fflush(stdout);
	rg a,b;
	for(rg i=1;i<=n-1;i++)
	{
		read(a);
		read(b);
		ins(a,b);
		ins(b,a);
	}
	dfs(1,0);
	init();
	a=s;
	for(rg i=1;i<=m;i++)
	{
		read(b);
		ans+=d[a]+d[b]-d[lca(a,b)]*2;
		a=b;
	}
	printf("%lld",ans);
	return 0;
}