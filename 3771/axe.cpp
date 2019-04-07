//2018.12.15
//bzoj3771 triple 生成函数+fft(ntt)+容斥
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define rc register char
#define mod 998244353
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define ll long long
using namespace std;
char *p1,*p2,buffer[10000009];
int n,bit,len,mx;
int inv[140009],rt[2][140009];
int f[3][140009],g[140009],h[140009],q[140009];
int ans[140009];
void rd(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
int qpow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)
			ans=(ll)ans*a%mod;
		b>>=1;
		a=(ll)a*a%mod;
	}
	return ans;
}
void init()
{
	while((1<<bit)<3*mx+1)
		bit++;
	len=1<<bit;
	for(rg i=0;i<len;i++)
		inv[i]=(inv[i>>1]>>1)|((i&1)<<(bit-1));
	rt[0][0]=1;
	rt[0][1]=qpow(3,119*(1<<(23-bit)));
	for(rg i=2;i<len;i++)
		rt[0][i]=(ll)rt[0][i-1]*rt[0][1]%mod;
	rt[1][0]=rt[0][0];
	for(rg i=1;i<len;i++)
		rt[1][i]=rt[0][len-i];
	// for(rg i=0;i<len;i++)
	// 	printf("i:%d rt0:%d rt1:%d inv:%d\n",i,rt[0][i],rt[1][i],inv[i]);
}
void fft(int c,int *s)
{
	for(rg i=0;i<len;i++)
		if(i<inv[i])
			swap(s[i],s[inv[i]]);
	for(rg l=2;l<=len;l<<=1)
	{
		int p=l>>1;
		for(rg j=0;j<len;j+=l)
			for(rg i=0;i<p;i++)
			{
				int t=(ll)rt[c][len/l*i]*s[i+j+p]%mod;
				s[i+j+p]=(s[i+j]+(mod-t))%mod;
				s[i+j]=(s[i+j]+t)%mod;
			}
	}
	if(c)
	{
		const int ti=qpow(len,mod-2);
		for(rg i=0;i<len;i++)
			s[i]=(ll)s[i]*ti%mod;
	}
}
void solve()
{
	for(rg i=0;i<=mx;i++)
	{
		g[i*2]=(ll)f[0][i]*f[0][i]%mod;
		h[i*3]=(ll)g[i*2]*f[0][i]%mod;
	}
	memcpy(f[1],f[0],sizeof(f[0]));
	fft(0,f[1]);
	memcpy(f[2],f[1],sizeof(f[1]));
	memcpy(q,g,sizeof(q));
	fft(0,q);
	for(rg i=0;i<len;i++)
	{
		q[i]=(ll)q[i]*f[1][i]%mod;
		f[1][i]=(ll)f[1][i]*f[1][i]%mod;
		f[2][i]=(ll)f[2][i]*f[1][i]%mod;
	}
	fft(1,f[1]);
	fft(1,f[2]);
	fft(1,q);
	const int inv2=qpow(2,mod-2),inv6=qpow(6,mod-2);
	for(rg i=0;i<len;i++)
	{
		int t1=f[0][i];
		int t2=((ll)f[1][i]-g[i]+mod)*inv2%mod;
		int t3=((ll)f[2][i]+3LL*(mod-q[i])+2LL*h[i])%mod*inv6%mod;
		ans[i]=((ll)t1+t2+t3)%mod;
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("axe.in","r",stdin);
	freopen("axe.out","w",stdout);
	#endif
	rd(n);
	int a;
	for(rg i=1;i<=n;i++)
	{
		rd(a);
		f[0][a]++;
		mx=max(mx,a);
	}
	init();
	solve();
	for(rg i=0;i<len;i++)
		if(ans[i])
			printf("%d %d\n",i,ans[i]);
	// for(rg i=0;i<len;i++)
	// 	printf("i:%d g:%d h:%d q:%d f0:%d f1:%d f2:%d\n",i,g[i],h[i],q[i],f[0][i],f[1][i],f[2][i]);
	return 0;
}