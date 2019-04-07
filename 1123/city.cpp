#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define rg register int
using namespace std;
typedef long long ll;
int n,m,tot,t;
int head[100010],edge[1000010],next[1000010];
int dfn[100010],low[100010],cut[100010],sum[100010];
ll ans[100010];
void add(int a,int b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
void dfs(int x,int fa)
{
	int ch=0;
	vector<int> v;
	dfn[x]=low[x]=++t;
	sum[x]=1;
	for(int i=head[x];i;i=next[i])
		if(!dfn[edge[i]])
		{
			++ch;
			dfs(edge[i],x);
			sum[x]+=sum[edge[i]];
			low[x]=min(low[x],low[edge[i]]);
			if(low[edge[i]]>=dfn[x])
			{
				v.push_back(sum[edge[i]]);
				cut[x]=1;
			}
		}
		else if(edge[i]^fa)
			low[x]=min(low[x],dfn[edge[i]]);
	if(!fa&&ch<=1)
		cut[x]=0;
	int s=0;
	for(int i=0;i<v.size();i++)
		s+=v[i];
	v.push_back(n-1-s);
	ans[x]=(ll)(n-1)*(n-1);
	for(int i=0;i<v.size();i++)
		ans[x]-=(ll)v[i]*v[i];
	if(!cut[x])
		ans[x]=0;
	ans[x]+=(n-1)<<1;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("city.in","r",stdin);
	freopen("city.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	int a,b;
	for(rg i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs(1,0);
	for(rg i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
	return 0;
}