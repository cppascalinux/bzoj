//2018.12.16
//bzoj3513 [MUTC2013]idiots 生成函数+fft+容斥
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define rg register int
#define db double
#define ll long long
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define pi 3.14159265358979323846
using namespace std;
struct cp
{
	db x,y;
	cp(){}
	cp(db a,db b){x=a,y=b;}
	cp operator +(cp p){return cp(x+p.x,y+p.y);}
	cp operator -(cp p){return cp(x-p.x,y-p.y);}
	cp operator *(cp p){return cp(x*p.x-y*p.y,x*p.y+y*p.x);}
	cp operator /(db v){return cp(x/v,y/v);}
};
char *p1,*p2,buffer[10000009];
int n,bit,len;
int v[100009];
int inv[270009];
cp rt[2][270009];
cp f[270009];
ll g[270009];
void clr()
{
	memset(v,0,sizeof(v));
	memset(f,0,sizeof(f));
}
void rd(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void init()
{
	bit=18;
	len=1<<bit;
	for(rg i=0;i<len;i++)
		inv[i]=(inv[i>>1]>>1)|((i&1)<<(bit-1));
	for(rg i=0;i<len;i++)
		rt[0][i]=cp(cos(2*pi*i/len),sin(2*pi*i/len));
	rt[1][0]=rt[0][0];
	for(rg i=1;i<len;i++)
		rt[1][i]=rt[0][len-i];
}
void fft(int c,cp *s)
{
	for(rg i=0;i<len;i++)
		if(i<inv[i])
			swap(s[i],s[inv[i]]);
	for(rg l=2;l<=len;l<<=1)
	{
		int p=l>>1,st=len/l;
		for(rg j=0;j<len;j+=l)
			for(rg i=0;i<p;i++)
			{
				cp t=rt[c][st*i]*s[i+j+p];
				s[i+j+p]=s[i+j]-t;
				s[i+j]=s[i+j]+t;
			}
	}
	if(c)
		for(rg i=0;i<len;i++)
			s[i]=s[i]/len;
}
void solve()
{
	// for(rg i=0;i<=10;i++)
	// 	printf("i:%d v:%d\n",i,v[i]);
	for(rg i=0;i<=100000;i++)
		f[i].x=v[i];
	fft(0,f);
	for(rg i=0;i<len;i++)
		f[i]=f[i]*f[i];
	fft(1,f);
	for(rg i=0;i<=100000;i++)
	{
		db t=f[i].x;
		if(!(i&1))
			t-=v[i>>1];
		g[i]=t/2+0.1;
	}
	// for(rg i=0;i<=10;i++)
	// 	printf("i:%d fx:%.3lf fy:%.3lf g:%lld\n",i,f[i].x,f[i].y,g[i]);
	ll ans=0,tot=0,sm=0;
	for(rg i=0;i<=100000;i++)
	{
		sm+=g[i];
		ans+=v[i]*sm;
	}
	tot=(ll)n*(n-1)/2*(n-2)/3;
	printf("%.7lf\n",(db)(tot-ans)/tot);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("idiots.in","r",stdin);
	freopen("idiots.out","w",stdout);
	#endif
	int t;
	rd(t);
	init();
	while(t--)
	{
		rd(n);
		int a;
		for(rg i=1;i<=n;i++)
		{
			rd(a);
			v[a]++;
		}
		solve();
		clr();
	}
	return 0;
}