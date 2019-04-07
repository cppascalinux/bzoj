//2018.12.15
//bzoj3771 triple 生成函数+fft(ntt)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define db double
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
int n,bit,len,mx;
int inv[140009];
cp rt[2][140009];
cp f[3][140009],g[140009],h[140009],q[140009];
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
void init()
{
	while((1<<bit)<3*mx+1)
		bit++;
	len=1<<bit;
	for(rg i=0;i<len;i++)
		inv[i]=(inv[i>>1]>>1)|((i&1)<<(bit-1));
	for(rg i=0;i<len;i++)
		rt[0][i]=cp(cos(2*pi/len*i),sin(2*pi/len*i));
	rt[1][0]=rt[0][0];
	for(rg i=1;i<len;i++)
		rt[1][i]=rt[0][len-i];
	// for(rg i=0;i<len;i++)
	// 	printf("i:%d rt0:%d rt1:%d inv:%d\n",i,rt[0][i],rt[1][i],inv[i]);
}
void fft(int c,cp *s)
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
				cp t=rt[c][len/l*i]*s[i+j+p];
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
	for(rg i=0;i<=mx;i++)
	{
		g[i*2]=f[0][i]*f[0][i];
		h[i*3]=g[i*2]*f[0][i];
	}
	memcpy(f[1],f[0],sizeof(f[0]));
	fft(0,f[1]);
	memcpy(f[2],f[1],sizeof(f[1]));
	memcpy(q,g,sizeof(q));
	fft(0,q);
	for(rg i=0;i<len;i++)
	{
		q[i]=q[i]*f[1][i];
		f[1][i]=f[1][i]*f[1][i];
		f[2][i]=f[2][i]*f[1][i];
	}
	fft(1,f[1]);
	fft(1,f[2]);
	fft(1,q);
	for(rg i=0;i<len;i++)
	{
		int t1=f[0][i].x+0.1;
		int t2=(f[1][i]-g[i]).x/2+0.1;
		int t3=(f[2][i]-cp(3,0)*q[i]+cp(2,0)*h[i]).x/6+0.1;
		ans[i]=t1+t2+t3;
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("axe.in","r",stdin);
	freopen("fft.out","w",stdout);
	#endif
	rd(n);
	int a;
	for(rg i=1;i<=n;i++)
	{
		rd(a);
		f[0][a].x+=1;
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