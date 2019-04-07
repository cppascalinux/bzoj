#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define rg register int
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,1000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
typedef long long ll;
const ll inf=0x7F7F7F7F7F7F7F7FLL;
char buffer[1000000],*p1,*p2;
int n,m,tot;
int vist[1000010];
ll dist[1000010];
ll minn[4000010];
struct node
{
	int num,len;
	node(){}
	node(int a,int b)
	{
		num=a;
		len=b;
	}
	bool operator < (const node &o) const
	{
		return len>o.len;
	}
};
vector<node> v[1000010];
void read(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+ch-'0',ch=gc();
}
void set(int a,int l,int r,int x,ll num)
{
	if(x<l||x>r)
		return;
	if(l==r)
	{
		minn[a]=num;
		return;
	}
	int mid=(l+r)>>1;
	set(a<<1,l,mid,x,num);
	set(a<<1|1,mid+1,r,x,num);
	minn[a]=min(minn[a<<1],minn[a<<1|1]);
}
int find(int a,int l,int r,ll num)
{
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if(minn[a<<1]==num)
		return find(a<<1,l,mid,num);
	else
		return find(a<<1|1,mid+1,r,num);
}
int dij()
{
	int x,ttt=0,pn,pl;
	memset(dist,0x7F,sizeof(dist));
	dist[1]=0;
	set(1,1,n,1,0);
	while(minn[1]^inf)
	{
		x=find(1,1,n,minn[1]);
		set(1,1,n,x,inf);
		for(rg i=0;i<v[x].size();i++)
		{
			pn=v[x][i].num;
			pl=v[x][i].len;
			if(!vist[pn]&&dist[pn]>dist[x]+pl)
			{
				dist[pn]=dist[x]+pl;
				set(1,1,n,pn,dist[pn]);
			}
		}
		if(++ttt>=n-1)
			break;
	}
	return dist[n];
}
void add(int a,int b,int c)
{
	v[a].push_back(node(b,c));
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	#endif
	read(n);
	read(m);
	int t,rxa,rxc,rya,ryc,rp;
	read(t);
	read(rxa);
	read(rxc);
	read(rya);
	read(ryc);
	read(rp);
	int a=0,b=0,x=0,y=0;
	for(rg i=1;i<=t;i++)
	{
		x=((ll)x*rxa+rxc)%rp;
		y=((ll)y*rya+ryc)%rp;
		a=min(x%n+1,y%n+1);
		b=max(y%n+1,y%n+1);
		add(a,b,100000000-100*a);
	}
	for(rg i=1;i<=m-t;i++)
	{
		read(a);
		read(b);
		read(x);
		add(a,b,x);
	}
	memset(minn,0x7F,sizeof(minn));
	printf("%lld",dij());
	return 0;
}