#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int n,m,s,p,sum;
int head1[500010],edge1[500010],next1[500010],tot1;
int head2[500010],edge2[500010],next2[500010],tot2;
int sum1[500010],sum2[500010];
int bar1[500010],bar2[500010];
int dfn[500010],low[500010],ins[500010],st[500010],tot,t;
int color[500010];
int q[500010],l,r=-1;
int f[500010],in[500010];
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
	st[++tot]=x;
	ins[x]=1;
	for(int i=head1[x];i;i=next1[i])
	{
		if(!dfn[edge1[i]])
		{
			dfs(edge1[i]);
			low[x]=min(low[x],low[edge1[i]]);
		}
		else if(ins[edge1[i]])
			low[x]=min(low[x],low[edge1[i]]);
	}
	if(low[x]==dfn[x])
	{
		sum++;
		for(;st[tot+1]^x;tot--)
		{
			color[st[tot]]=sum;
			sum2[sum]+=sum1[st[tot]];
			bar2[sum]|=bar1[st[tot]];
			ins[st[tot]]=0;
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
void dfs1(int x)
{
	if(dfn[x])
		return;
	dfn[x]=1;
	for(int i=head2[x];i;i=next2[i])
		dfs1(edge2[i]);
}
void solve()
{
	memset(dfn,0,sizeof(dfn));
	dfs1(color[s]);
	for(int i=1;i<=sum;i++)
		if(!dfn[i])
			for(int j=head2[i];j;j=next2[j])
				in[edge2[j]]--;
	q[++r]=color[s];
	while(l<=r)
	{
		int x=q[l++];
		f[x]+=sum2[x];
		for(int i=head2[x];i;i=next2[i])
		{
			f[edge2[i]]=max(f[edge2[i]],f[x]);
			in[edge2[i]]--;
			if(!in[edge2[i]])
				q[++r]=edge2[i];
		}
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("atm.in","r",stdin);
	freopen("atm.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add1(a,b);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",sum1+i);
	scanf("%d%d",&s,&p);
	for(int i=1;i<=p;i++)
	{
		int a;
		scanf("%d",&a);
		bar1[a]=1;
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i);
	rebuild();
	solve();
	int ans=0;
	for(int i=1;i<=sum;i++)
		if(bar2[i])
			ans=max(ans,f[i]);
	printf("%d",ans);
	//for(int i=1;i<=n;i++)
	//	printf("i:%d color:%d\n",i,color[i]);
	return 0;
}