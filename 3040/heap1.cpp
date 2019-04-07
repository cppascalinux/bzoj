#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,1000000,stdin),p1==p2)?EOF:*p1++)
#define inf 0x7F7F7F7F7F7F7F7FLL;
#define ll long long
using namespace std;
char *p1,*p2,buffer[1000000];
int n,m,tot;
int head[1000010],edge[10000010],next[10000010],len[10000010];
ll dist[1000010];
int vist[1000010];
int h[2000010],pos[1000010],top;
void add(int a,int b,int c)
{
	edge[++tot]=b;
	len[tot]=c;
	next[tot]=head[a];
	head[a]=tot;
}
void read(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+ch-'0',ch=gc();
}
void add(int x)
{
	h[++top]=x;
	pos[x]=top;
	int now=top;
	while(now>1&&dist[h[now>>1]]>dist[x])
	{
		swap(pos[h[now>>1]],pos[x]);
		swap(h[now>>1],h[now]);
		now>>=1;
	}
}
void del(int x)
{
	if(pos[x]==0)
		return;
	int now=pos[x];
	swap(pos[x],pos[h[top]]);
	swap(h[now],h[top]);
	pos[x]=0;
	h[top--]=0;
	int t;
	while(min(dist[h[now<<1]],dist[h[now<<1|1]])<dist[h[now]])
	{
		t=dist[h[now<<1]]<=dist[h[now<<1|1]]?now<<1:now<<1|1;
		swap(pos[h[now]],pos[h[t]]);
		swap(h[now],h[t]);
		now=t;
	}
}
void dij(int s)
{
	memset(dist,0x7F,sizeof(dist));
	dist[s]=0;
	add(s);
	int x;
	while(top)
	{
		x=h[1];
		del(x);
		vist[x]=1;
		for(int i=head[x];i;i=next[i])
			if(!vist[edge[i]]&&dist[edge[i]]>dist[x]+len[i])
			{
				dist[edge[i]]=dist[x]+len[i];
				del(edge[i]);
				add(edge[i]);
			}
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	#endif
	read(n);
	read(m);
	int x=0,y=0,z=0;
	int t,rxa,rxc,rya,ryc,rp,a,b;
	read(t);
	read(rxa);
	read(rxc);
	read(rya);
	read(ryc);
	read(rp);
	for(int i=1;i<=t;i++)
	{
		x=((ll)x*rxa+rxc)%rp;
		y=((ll)y*rya+ryc)%rp;
		a=min(x%n+1,y%n+1);
		b=max(y%n+1,y%n+1);
		add(a,b,100000000-100*a);
	}
	for(int i=1;i<=m-t;i++)
	{
		read(x);
		read(y);
		read(z);
		add(x,y,z);
	}
	dij(1);
	printf("%lld",dist[n]);
	return 0;
}