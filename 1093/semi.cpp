#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define int long long
using namespace std;
int n,m,mod,tot1,tot2,sum;
int head1[100010],edge1[1000010],next1[1000010];
int head2[100010],edge2[1000010],next2[1000010];
int dfn[100010],low[100010],ins[100010],st[100010],top,t;
int color[100010],ans[100010],in[100010],f[100010],num[100010];
int q[100010],l,r=-1;
int used[100010];
set<int> s[100010];
void add1(int a,int b)
{
	edge1[++tot1]=b;
	next1[tot1]=head1[a];
	head1[a]=tot1;
}
void add2(int a,int b)
{
	edge2[++tot2]=b;
	next2[tot2]=head2[a];
	head2[a]=tot2;
}
void dfs(int x)
{
	dfn[x]=low[x]=++t;
	ins[x]=1;
	st[++top]=x;
	for(int i=head1[x];i;i=next1[i])
		if(!dfn[edge1[i]])
		{
			dfs(edge1[i]);
			low[x]=min(low[x],low[edge1[i]]);
		}
		else if(ins[edge1[i]])
			low[x]=min(low[x],dfn[edge1[i]]);
	if(dfn[x]==low[x])
	{
		sum++;
		for(;st[top+1]^x;top--)
		{
			ins[st[top]]=0;
			ans[sum]++;
			color[st[top]]=sum;
		}
	}
}
void rebuild()
{
	for(int i=1;i<=n;i++)
		for(int j=head1[i];j;j=next1[j])
			if(color[i]^color[edge1[j]])
			{
				add2(color[i],color[edge1[j]]);
				in[color[edge1[j]]]++;
			}
}
void solve()
{
	//for(int i=1;i<=sum;i++)
	//	printf("%lld\n",ans[i]);
	for(int i=1;i<=sum;i++)
		if(!in[i])
			q[++r]=i;
	fill(num+1,num+n+1,1);
	while(l<=r)
	{
		int x=q[l++];
		f[x]+=ans[x];
		for(int i=head2[x];i;i=next2[i])
		{
			if(f[x]>f[edge2[i]])
			{
				num[edge2[i]]=num[x];
				f[edge2[i]]=f[x];
			}
			else if(f[x]==f[edge2[i]]&&!s[edge2[i]].count(x))
				num[edge2[i]]=(num[edge2[i]]+num[x])%mod;
			in[edge2[i]]--;
			if(!in[edge2[i]])
				q[++r]=edge2[i];
			s[edge2[i]].insert(x);
		}
	}
}
#undef int
int main()
#define int long long
{
#ifndef ONLINE_JUDGE
	freopen("semi.in","r",stdin);
	freopen("semi.out","w",stdout);
#endif
	scanf("%lld%lld%lld",&n,&m,&mod);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%lld%lld",&a,&b);
		add1(a,b);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i);
	rebuild();
	solve();
	int maxx=0,out=0;
	for(int i=1;i<=sum;i++)
		maxx=max(maxx,f[i]);
	for(int i=1;i<=sum;i++)
		if(f[i]==maxx)
			out=(out+num[i])%mod;
	printf("%lld\n%lld",maxx,out);
	return 0;
}