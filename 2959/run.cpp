//2019.02.07
//bzoj2959 长跑 并查集+树状数组
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define pii pair<int,int>
#define fi first
#define se second
#define lb(x) (x&-x)
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,tot,tme;
int v[150009];
int fn[150009],sz[150009];
int c[150009];
pii q[750009];
int typ[750009],ont[750009];
int hd[150009],eg[300009],nxt[300009];
int dep[150009],dfn[150009],ed[150009];
int f[150009][19];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void add(int x,int val)
{
	for(int i=x;i;i-=lb(i))
		c[i]+=val;
}
int ask(int x)
{
	if(!x)
		return 0;
	int ans=0;
	for(int i=x;i<=n;i+=lb(i))
		ans+=c[i];
	return ans;
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
	dfn[x]=ed[x]=++tme;
	f[x][0]=fa;
	for(int i=1;i<=18;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs(eg[i],x);
			ed[x]=max(ed[x],ed[eg[i]]);
		}
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int l=dep[x]-dep[y];
	for(int i=0;i<=18;i++)
		if(l&(1<<i))
			x=f[x][i];
	if(x==y)
		return x;
	for(int i=18;i>=0;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}
void modify(int x,int y)
{
	int fx=fnd(x),fy=fnd(y);
	while(fx!=fy)
	{
		if(dep[fx]<dep[fy])
			swap(fx,fy);
		x=fnd(f[fx][0]);
		add(ed[x],sz[fx]);
		add(dfn[x]-1,-sz[fx]);
		add(ed[fx],-sz[fx]);
		add(dfn[fx]-1,sz[fx]);
		sz[x]+=sz[fx];
		sz[fx]=0;
		fn[fx]=x;
		fx=x;
	}
}
int query(int x,int y)
{
	int lca=getlca(x,y);
	// printf("x:%d y:%d lca:%d\n",x,y,getlca(x,y));
	int ans=ask(dfn[x])+ask(dfn[y])-ask(dfn[lca])-ask(dfn[f[lca][0]]);
	if(fnd(lca)!=lca)
		ans+=sz[fnd(lca)];
	return ans;
}
void init()
{
	for(int i=1;i<=n;i++)
		fn[i]=i;
	for(int i=1;i<=m;i++)
		if(typ[i]==1)
		{
			int a=q[i].fi,b=q[i].se;
			if(fnd(a)!=fnd(b))
			{
				fn[fnd(a)]=fnd(b);
				ins(a,b);
				ins(b,a);
				ont[i]=1;
			}
		}
		else if(typ[i]==3)
		{
			if(fnd(q[i].fi)!=fnd(q[i].se))
				typ[i]=4;
		}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i,0);
	for(int i=1;i<=n;i++)
	{
		add(ed[i],v[i]);
		add(dfn[i]-1,-v[i]);
	}
}
void solve()
{
	for(int i=1;i<=n;i++)
	{
		fn[i]=i;
		sz[i]=v[i];
	}
	for(int i=1;i<=m;i++)
	{
		int x=q[i].fi,y=q[i].se;
		if(typ[i]==1)
		{
			if(ont[i])
				continue;
			modify(x,y);
		}
		else if(typ[i]==2)
		{
			int d=y-v[x];
			v[x]=y;
			x=fnd(x);
			sz[x]+=d;
			add(ed[x],d);
			add(dfn[x]-1,-d);
		}
		else if(typ[i]==3)
			printf("%d\n",query(x,y));
		else
			printf("-1\n");
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("run.in","r",stdin);
	freopen("run.out","w",stdout);
#endif	
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		rd(v[i]);
	for(int i=1,a,b,c;i<=m;i++)
	{
		rd(a),rd(b),rd(c);
		typ[i]=a;
		q[i]=pii(b,c);
	}
	init();
	solve();
	return 0;
}