#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dfn[1000010],low[1000010],st[1000010],ins[1000010],top,t;
int in[1000010];
int head[1000010],edge[1000010],next[1000010];
int color[1000010];
int n,sum,tot;
void add(int a,int b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
void dfs(int x)
{
	dfn[x]=low[x]=++t;
	ins[x]=1;
	st[++top]=x;
	for(int i=head[x];i;i=next[i])
		if(!dfn[edge[i]])
		{
			dfs(edge[i]);
			low[x]=min(low[x],low[edge[i]]);
		}
		else if(ins[edge[i]])
			low[x]=min(low[x],dfn[edge[i]]);
	if(dfn[x]==low[x])
	{
		sum++;
		for(;st[top+1]^x;top--)
		{
			color[st[top]]=sum;
			ins[st[top]]=0;
		}
	}
}
void rebuild()
{
	for(int i=1;i<=n;i++)
		for(int j=head[i];j;j=next[j])
			if(color[i]^color[edge[j]])
				in[color[edge[j]]]++;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("bank.in","r",stdin);
	freopen("bank.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int a;
		scanf("%d",&a);
		if(a^i)
			add(a,i);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i);
	rebuild();
	int ans=0;
	//for(int i=1;i<=n;i++)
	//	printf("i:%d color:%d\n",i,color[i]);
	for(int i=1;i<=sum;i++)
		if(!in[i])
			ans++;
	printf("%d",ans);
	return 0;
}