//2019.01.31
//bzoj3625 小朋友和二叉树
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define ll long long
#define mod 998244353
using namespace std;
int n,m,len;
int rt[2][2100000],mp[2100000];
int iv[2100000];
int f[2100000],g[2100000],h[2100000];
int t1[2100000],t2[2100000],t3[2100000];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
void initiv()
{
	iv[1]=1;
	for(int i=2;i<2100000;i++)
		iv[i]=(ll)(mod-mod/i)*iv[mod%i]%mod;
	// for(int i=1;i<1050000;i++)
	// 	printf("i:%d iv:%d\n",i,iv[i]);
}
void init(int bit)
{
	len=1<<bit;
	for(int i=0;i<len;i++)
		mp[i]=(mp[i>>1]>>1)|((i&1)<<(bit-1));
	rt[0][0]=rt[1][0]=1;
	rt[0][1]=qpow(3,119*(1<<(23-bit)));
	for(int i=2;i<len;i++)
		rt[0][i]=(ll)rt[0][i-1]*rt[0][1]%mod;
	for(int i=1;i<len;i++)
		rt[1][i]=rt[0][len-i];
}
void fft(int *s,int c)
{
	for(int i=0;i<len;i++)
		if(i<mp[i])
			swap(s[i],s[mp[i]]);
	for(int l=2;l<=len;l<<=1)
	{
		int d=l>>1,sp=len/l;
		for(int j=0;j<len;j+=l)
			for(int i=0;i<d;i++)
			{
				int t=(ll)rt[c][sp*i]*s[i+j+d]%mod;
				s[i+j+d]=(s[i+j]-t+mod)%mod;
				s[i+j]=(s[i+j]+t)%mod;
			}
	}
	if(c)
		for(int i=0;i<len;i++)
			s[i]=(ll)s[i]*iv[len]%mod;
}
void getinv(int *f,int *g,int l)
{
	memset(g,0,l<<4);
	g[0]=qpow(f[0],mod-2);
	// printf("g0:%d\n",g[0]);
	// int *t=t1;
	int *t=(int*)calloc(l<<2,4);
	// memset(t,0,l<<4);
	for(int i=1;(1<<i)<2*l;i++)
	{
		// printf("i:%d\n",i);
		init(i+1);
		memcpy(t,f,len<<1);
		fft(t,0);
		fft(g,0);
		for(int j=0;j<len;j++)
			g[j]=g[j]*(2-(ll)g[j]*t[j]%mod+mod)%mod;
		// for(int j=0;j<len;j++)
		// 	printf("j:%d t:%d g:%d\n",j,t[j],g[j]);
		fft(g,1);
		for(int j=len>>1;j<len;j++)
			g[j]=0;
		// for(int j=0;j<len;j++)
		// 	printf("j:%d g:%d\n",j,g[j]);
	}
	for(int i=l;i<len;i++)
		g[i]=0;
}
void getsqrt(int *f,int *g,int l)
{
	memset(g,0,l<<4);
	g[0]=1;
	// int *tf=t2;
	// int *tg=t3;
	int *tf=(int*)calloc(l<<3,4);
	int *tg=(int*)calloc(l<<3,4);
	// memset(tf,0,l<<4);
	// memset(tg,0,l<<4);
	for(int i=1;(1<<i)<2*l;i++)
	{
		int tl=1<<(i+1);
		getinv(g,tg,tl>>1);
		memcpy(tf,f,tl<<1);
		init(i+1);
		fft(tf,0);
		fft(tg,0);
		for(int j=0;j<len;j++)
			tg[j]=(ll)tg[j]*tf[j]%mod;
		fft(tg,1);
		for(int j=0;j<len>>1;j++)
			g[j]=(ll)(g[j]+tg[j])*iv[2]%mod;
	}
	for(int i=l;i<len;i++)
		g[i]=0;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	initiv();
	scanf("%d%d",&n,&m);
	m++;
	for(int i=1,a;i<=n;i++)
	{
		scanf("%d",&a);
		f[a]=1;
	}
	f[0]=1;
	for(int i=1;i<m;i++)
		f[i]=(mod-4*f[i]%mod)%mod;
	getsqrt(f,g,m);
	g[0]++;
	for(int i=0;i<m;i++)
		g[i]=(ll)g[i]*iv[2]%mod;
	getinv(g,f,m);
	for(int i=1;i<m;i++)
		printf("%d\n",f[i]);
	// f[0]=1;
	// f[1]=mod-1;
	// f[2]=mod-1;
	// getinv(f,g,100);
	// for(int i=0;i<100;i++)
	// 	printf("i:%d g:%d\n",i,g[i]);
	return 0;
}