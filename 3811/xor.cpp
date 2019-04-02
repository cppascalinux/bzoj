//bzoj3811 玛里苟斯 线性基+分类讨论+暴力
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define db long double
#define ll unsigned long long
using namespace std;
int n,k;
ll bs[69];
void ins(ll x)
{
	for(int i=63;i>=0;i--)
		if(x&(1LL<<i))
		{
			if(bs[i])
				x^=bs[i];
			else
			{
				for(int j=0;j<i;j++)
					if(x&(1LL<<j))
						x^=bs[j];
				for(int j=i+1;j<=63;j++)
					if(bs[j]&(1LL<<i))
						bs[j]^=x;
				bs[i]=x;
				break;
			}
		}
}
void solve1()
{
	ll tmp=0;
	for(int i=0;i<=63;i++)
		tmp|=bs[i];
	printf("%llu",tmp>>1);
	if(tmp&1)
		printf(".5");
}
void solve2()
{
	ll tmp=0;
	for(int i=0;i<=63;i++)
		tmp|=bs[i];
	ll ans=0;
	for(int i=0;i<=63;i++)
		for(int j=0;j<=63;j++)
		{
			int ti=tmp&(1LL<<i),tj=tmp&(1LL<<j);
			if(!ti||!tj)
				continue;
			if(i==j)
				ans+=1LL<<(i+j);
			else
				ans+=1LL<<(i+j-1);
		}
	printf("%llu",ans>>1);
	if(ans&1)
		printf(".5");
}
void solve3()
{
	int sm=0;
	int st[69];
	for(int i=0;i<=63;i++)
		if(bs[i])
			st[++sm]=i;
	ll ans1=0,ans2=0;
	int base=1LL<<(sm-1);
	for(int s=0;s<1<<sm;s++)
	{
		ll tmp=0;
		for(int i=1;i<=sm;i++)
			if(s&(1<<(i-1)))
				tmp^=bs[st[i]];
		ll nxt1=0,nxt2=1;
		for(int i=1;i<=k;i++)
		{
			nxt1*=tmp;
			nxt2*=tmp;
			nxt1+=nxt2/base;
			nxt2%=base;
		}
		ans1+=nxt1;
		ans2+=nxt2;
		ans1+=ans2/base;
		ans2%=base;
	}
	ans2/=base;
	ans2+=ans1;
	printf("%llu",ans2>>1);
	if(ans2&1)
		printf(".5");
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		ll a;
		scanf("%llu",&a);
		ins(a);
	}
	if(k==1)
		solve1();
	else if(k==2)
		solve2();
	else
		solve3();
	return 0;
}