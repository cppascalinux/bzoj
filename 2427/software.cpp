#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,s;
int f[110][510];
int w[110],v[110],d[110];
int ins[110],dfn[110],low[110],st[110],t,tot;
int color[110],v1[110],w1[110],sum;
int head[110],next[210],edge[210],tot0;
int head1[110],next1[210],edge1[210],tot1;
int in[110];
void add(int a,int b)
{
	edge[++tot0]=b;
	next[tot0]=head[a];
	head[a]=tot0;
}
void add1(int a,int b)
{
	edge1[++tot1]=b;
	next1[tot1]=head1[a];
	head1[a]=tot1;
}
void dfs1(int x)
{
	for(int i=w1[x];i<=m;i++)
		f[x][i]=v1[x];
	for(int i=head1[x];i;i=next1[i])
	{
		dfs1(edge1[i]);
		for(int j=m;j>=w1[x];j--)
			for(int k=w1[x];k<=j;k++)
				f[x][j]=max(f[x][j],f[edge1[i]][j-k]+f[x][k]);
	}
}
void dfs(int x)
{
	dfn[x]=low[x]=++t;
	st[++tot]=x;
	ins[x]=1;
	for(int i=head[x];i;i=next[i])
	{
		if(!dfn[edge[i]])
		{
			dfs(edge[i]);
			low[x]=min(low[x],low[edge[i]]);
		}
		else if(ins[edge[i]])
			low[x]=min(low[x],dfn[edge[i]]);
	}
	if(dfn[x]==low[x])
	{
		sum++;
		for(;st[tot+1]!=x;tot--)
		{
			color[st[tot]]=sum;
			v1[sum]+=v[st[tot]];
			w1[sum]+=w[st[tot]];
			ins[st[tot]]=0;
		}
	}
}
void rebuild()
{
	for(int i=1;i<=n;i++)
		for(int j=head[i];j;j=next[j])
			if(color[i]^color[edge[j]])
			{
				add1(color[i],color[edge[j]]);
				in[color[edge[j]]]++;
			}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("software.in","r",stdin);
	freopen("software.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",w+i);
	for(int i=1;i<=n;i++)
		scanf("%d",v+i);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",d+i);
		if(d[i])
			add(d[i],i);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i);
	//for(int i=1;i<=n;i++)
	//	printf("%d %d\n",i,color[i]);
	/*for(int i=1;i<=n;i++)
	{
		printf("i:%d\n",i);
		for(int j=head[i];j;j=next[j])
			printf("%d ",edge[j]);
		printf("\n");
	}*/
	rebuild();
	//for(int i=1;i<=sum;i++)
	//	printf("i:%d in:%d v1:%d w1:%d\n",i,in[i],v1[i],w1[i]);
	s=sum+1;
	for(int i=1;i<=sum;i++)
		if(!in[i])
			add1(s,i);
	dfs1(s);
	//for(int i=1;i<=sum;i++)
	//	printf("i:%d in:%d v1:%d w1:%d\n",i,in[i],v1[i],w1[i]);
	printf("%d",f[s][m]);
	return 0;
}