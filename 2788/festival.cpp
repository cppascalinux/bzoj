#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int inf=0x7F7F7F7F;
int n,m1,m2,sum,ans,err;
int head[610],next[200010],edge[200010],len[200010],tot;
int color[200010];
int dfn[610],low[610],st[610],ins[610],top,t;
int vist[610],dist[610];
int used[610];
vector<int> p[610];
queue<int> q;
void add(int a,int b,int c)
{
	edge[++tot]=b;
	len[tot]=c;
	next[tot]=head[a];
	head[a]=tot;
}
void dfs(int x)
{
	low[x]=dfn[x]=++t;
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
			p[sum].push_back(st[top]);
			ins[st[top]]=0;
		}
	}
}
void spfa(int s)
{
	memset(vist,0,sizeof(vist));
	memset(dist,inf,sizeof(dist));
	memset(used,0,sizeof(used));
	while(!q.empty())
		q.pop();
	vist[s]=1;
	dist[s]=0;
	q.push(s);
	while(!q.empty()&&!err)
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(color[edge[i]]==color[s])
				if(dist[edge[i]]>dist[x]+len[i])
				{
					dist[edge[i]]=dist[x]+len[i];
					if(!vist[edge[i]])
					{
						vist[edge[i]]=1;
						if(++used[edge[i]]>n+5)
							err=1;
						q.push(edge[i]);
					}
				}
		vist[x]=0;
	}
}
void solve(int c)
{
	int ans1=0;
	for(int i=0;i<p[c].size();i++)
	{
		spfa(p[c][i]);
		if(err)
			return;
		for(int j=0;j<p[c].size();j++)
			ans1=max(ans1,dist[p[c][j]]);
		/*printf("i:%d\n",p[c][i]);
		for(int j=0;j<p[c].size();j++)
		{
			ans1=max(ans1,dist[p[c][j]]);
			printf("j:%d dist:%d\n",p[c][j],dist[p[c][j]]);
		}*/
	}
	ans+=ans1+1;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("festival.in","r",stdin);
	freopen("festival.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m1,&m2);
	for(int i=1;i<=m1;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b,1);
		add(b,a,-1);
	}
	for(int i=1;i<=m2;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(b,a,0);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i);
	/*for(int i=1;i<=sum;i++)
	{
		printf("color:%d\n",i);
		for(int j=0;j<p[i].size();j++)
			printf("%d ",p[i][j]);
		printf("\n");
	}*/
	for(int i=1;i<=sum&&(!err);i++)
		solve(i);
	if(err)
		printf("NIE");
	else
		printf("%d\n",ans);
	return 0;
}