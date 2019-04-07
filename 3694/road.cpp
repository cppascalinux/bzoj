#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define inf 0x7F7F7F7F
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,tot,sm;
int hd[4009],eg[200009],nxt[200009],len[200009];
int f[4009],dep[4009],dist[4009];
int ans[4009];
int fx[4009][20];
struct node
{
	int u,v,l;
	node(){}
	node(int a,int b,int c)
	{
		u=a;
		v=b;
		l=c;
	}
	bool operator < (const node &o) const
	{
		return l<o.l;
	}
}q[100009];
void read(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
int find(int x)
{
//	printf("x:%d f:%d\n",x,f[x]);
	return x==f[x]?x:f[x]=find(f[x]);
}
void dfs(int x,int fa,int suml)
{
	dep[x]=dep[fa]+1;
	dist[x]=suml;
	fx[x][0]=fa;
	for(rg i=1;i<=15;i++)
		fx[x][i]=fx[fx[x][i-1]][i-1];
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]^fa)
			dfs(eg[i],x,suml+len[i]);
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int l=dep[x]-dep[y];
	for(rg i=0;i<=15;i++)
		if(l&(1<<i))
			x=fx[x][i];
	if(x==y)
		return x;
	for(rg i=15;i>=0;i--)
		if(fx[x][i]^fx[y][i])
		{
			x=fx[x][i];
			y=fx[y][i];
		}
	return fx[x][0];
}
void solve()
{
	memset(ans,0x7F,sizeof(ans));
	sort(q+1,q+sm+1);
	for(rg i=1;i<=n;i++)
		f[i]=i;
	int a,b,lc,tl;
	for(rg i=1;i<=sm;i++)
	{
		a=find(q[i].u);
		b=find(q[i].v);
		tl=q[i].l;
		lc=lca(a,b);
//		printf("\nu:%d v:%d l:%d lca:%d\n",q[i].u,q[i].v,q[i].l,lc);
		while(dep[a]>dep[lc])
		{
			ans[a]=tl;
//			int na=find(a);
//			printf("a:%d na:%d\n",a,na);
//			a=find(fx[na][0]);
//			f[na]=find(fx[na][0]);
			a=f[a]=find(fx[a][0]);
		}
		while(dep[b]>dep[lc])
		{
			ans[b]=tl;
//			int nb=find(b);
//			printf("b:%d nb:%d\n",b,nb);
//			b=find(fx[nb][0]);
			b=f[b]=find(fx[b][0]);
		}
//		for(rg i=1;i<=n;i++)
//			printf("i:%d ans:%d f:%d\n",i,ans[i],find(i));
	}
	for(rg i=1;i<=n;i++)
		if(ans[i]==inf)
			ans[i]=-1;
		else
			ans[i]-=dist[i];
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	#endif
	read(n);
	read(m);
	int a,b,c,d;
	for(rg i=1;i<=m;i++)
	{
		read(a);
		read(b);
		read(c);
		read(d);
		if(d)
		{
			ins(a,b,c);
			ins(b,a,c);
		}
		else
			q[++sm]=node(a,b,c);
	}
	dfs(1,0,0);
	for(rg i=1;i<=sm;i++)
		q[i].l+=dist[q[i].u]+dist[q[i].v];
	solve();
	for(rg i=2;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}