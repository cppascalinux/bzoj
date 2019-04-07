//2019.02.08
//bzoj2959 长跑 LCT
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) x==lc(f[x])||x==rc(f[x])
#define update(x) sz[x]=sz[lc(x)]+sz[rc(x)]+v[x]
#define down(x) if(rv[x]) swap(lc(x),rc(x)),rv[lc(x)]^=1,rv[rc(x)]^=1,rv[x]=0
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
int f[150009],ch[150009][2],sz[150009],rv[150009],v[150009],st[150009];
int fn[150009];
int v0[150009];
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
	for(int y=0;x;y=x,x=fnd(f[x]))
	{
		splay(x);
		rc(x)=y;
		update(x);
		if(y)
			f[y]=x;
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
int link(int x,int y)
{
	makert(x);
	if(findrt(y)==x)
		return 0;
	f[x]=y;
	return 1;
}
void merge(int x,int y)
{
	queue<int> q;
	split(x,y);
	if(lc(y))
		q.push(lc(y));
	if(rc(y))
		q.push(rc(y));
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		fn[t]=y;
		v[y]+=v[t];
		if(lc(t))
			q.push(lc(t));
		if(rc(t))
			q.push(rc(t));
	}
	lc(y)=rc(y)=0;
	update(y);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("run.in","r",stdin);
	freopen("lct.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
	{
		rd(v0[i]);
		sz[i]=v[i]=v0[i];
		fn[i]=i;
	}
	for(int i=1,a,b,c;i<=m;i++)
	{
		rd(a),rd(b),rd(c);
		if(a==1)
		{
			b=fnd(b),c=fnd(c);
			if(!link(b,c))
				merge(b,c);
		}
		else if(a==2)
		{
			int d=c-v0[b];
			v0[b]=c;
			b=fnd(b);
			splay(b);
			v[b]+=d;
			sz[b]+=d;
		}
		else if(a==3)
		{
			b=fnd(b),c=fnd(c);
			makert(b);
			if(findrt(c)!=b)
				printf("-1\n");
			else
				printf("%d\n",sz[b]);
		}
	}
	return 0;
}