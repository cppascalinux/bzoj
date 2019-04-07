//2019.02.09
//bzoj2594 [Wc2006]水管局长数据加强版 边权LCT+kruskal
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) x==lc(f[x])||x==rc(f[x])
#define pni pair<node,int>
#define pii pair<int,int>
#define fi first
#define se second
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define getmx(a,b) (v[a]>v[b]?a:b)
#define down(x) if(rv[x]) swap(lc(x),rc(x)),rv[lc(x)]^=1,rv[rc(x)]^=1,rv[x]=0
using namespace std;
struct node
{
	int u,v,l;
	node(){}
	node(int a,int b,int c){u=a,v=b,l=c;}
	bool operator <(const node &p) const
	{
		return u<p.u||(u==p.u&&v<p.v);
	}
};
char *p1,*p2,buffer[10000009];
int n,m,q;
int f[1100009],ch[1100009][2],rv[1100009],v[1100009],mx[1100009],st[1100009];
node e[1000009];
int del[1000009];
pii qr[100009];
int typ[100009],ans[100009];
pni tmp[1000009];
int fn[100009];
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
bool cmp(pni a,pni b)
{
	return a.fi.l<b.fi.l;
}
void update(int x)
{
	mx[x]=getmx(mx[lc(x)],mx[rc(x)]);
	mx[x]=getmx(mx[x],x);
}
void rotate(int x)
{
	int y=f[x],z=f[y],dx=x==rc(y),dy=y==rc(z);
	if(ch[x][dx^1])
		f[ch[x][dx^1]]=y;
	if(nrt(y))
		ch[z][dy]=x;
	f[x]=z;
	f[y]=x;
	ch[y][dx]=ch[x][dx^1];
	ch[x][dx^1]=y;
	update(y);
	update(x);
}
void splay(int x)
{
	int y,z,tp=0;
	for(y=x;nrt(y);y=f[y])
		st[++tp]=y;
	st[++tp]=y;
	for(int i=tp;i>=1;i--)
		down(st[i]);
	while(nrt(x))
	{
		y=f[x],z=f[y];
		if(nrt(y))
			rotate((x==rc(y))^(y==rc(z))?x:y);
		rotate(x);
	}
}
void access(int x)
{
	for(int y=0;x;y=x,x=f[x])
	{
		splay(x);
		rc(x)=y;
		update(x);
	}
}
void makert(int x)
{
	access(x);
	splay(x);
	rv[x]^=1;
}
int findrt(int x)
{
	access(x);
	splay(x);
	while(1)
	{
		down(x);
		if(!lc(x))
			break;
		x=lc(x);
	}
	splay(x);
	return x;
}
void split(int x,int y)
{
	makert(x);
	access(y);
	splay(y);
}
void add(int a)
{
	v[a+n]=e[a].l;
	int x=e[a].u,y=e[a].v;
	makert(x);
	if(findrt(y)!=x)
	{
		makert(y);
		f[x]=f[y]=a+n;
	}
	else
	{
		int t=mx[x];
		if(v[t]>v[a+n])
		{
			makert(t);
			f[lc(t)]=f[rc(t)]=0;
			lc(t)=rc(t)=0;
			makert(x);
			makert(y);
			f[x]=f[y]=a+n;
		}
	}
}
void init()
{
	for(int i=1;i<=n+m;i++)
		mx[i]=i;
	for(int i=1;i<=n;i++)
		fn[i]=i;
	int tp=0;
	for(int i=1;i<=m;i++)
		if(!del[i])
			tmp[++tp]=pni(e[i],i);
	sort(tmp+1,tmp+tp+1,cmp);
	for(int i=1;i<=tp;i++)
	{
		int a=tmp[i].fi.u,b=tmp[i].fi.v;
		if(fnd(a)!=fnd(b))
		{
			fn[fnd(a)]=fnd(b);
			add(tmp[i].se);
		}
	}
}
void solve()
{
	// for(int i=1;i<=m;i++)
	// 	printf("i:%d u:%d v:%d\n",i,e[i].u,e[i].v);
	// for(int i=1;i<=q;i++)
	// 	printf("i:%d typ:%d fi:%d se:%d\n",i,typ[i],qr[i].fi,qr[i].se);
	// fflush(stdout);
	for(int i=q;i>=1;i--)
		if(typ[i]==1)
		{
			split(qr[i].fi,qr[i].se);
			ans[i]=v[mx[qr[i].se]];
		}
		else
			add(qr[i].fi);
	for(int i=1;i<=q;i++)
		if(typ[i]==1)
			printf("%d\n",ans[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("pipe.in","r",stdin);
	freopen("pipe.out","w",stdout);
#endif
	rd(n),rd(m),rd(q);
	// printf("n:%d m:%d q:%d\n",n,m,q);
	// fflush(stdout);
	for(int i=1;i<=m;i++)
	{
		rd(e[i].u),rd(e[i].v),rd(e[i].l);
		if(e[i].u>e[i].v)
			swap(e[i].u,e[i].v);
	}
	sort(e+1,e+m+1);
	for(int i=1,c,a,b;i<=q;i++)
	{
		rd(c),rd(a),rd(b);
		if(a>b)
			swap(a,b);
		typ[i]=c;
		qr[i]=pii(a,b);
		if(c==2)
		{
			int t=lower_bound(e+1,e+m+1,node(a,b,0))-e;
			del[t]=1;
			qr[i]=pii(t,0);
		}
	}
	init();
	solve();
	cerr<<clock();
	return 0;
}