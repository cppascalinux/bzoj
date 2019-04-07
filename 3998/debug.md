# 这题时限卡的好紧啊。。

## 限时10000ms,O(n)的后缀自动机跑了9216ms...

### O(nlogn)的后缀数组肯定直接T飞。。
---

第一次交还~~TLE~~

然后才发现是存反图的数组开小导致的

直接开到26倍。。又MLE

上网查了一下，后缀自动机的转移数量不超过3*n-4

~~然而懒得看证明~~

把数组的大小改一改，就~~很愉快的~~AC了这道题QwQ

(第一次用markdown写debug。。。qwq)

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
#define rg register int
using namespace std;
int n,tot,last,t,tote,tota;
char s[500010],ans[500010];
int len[1000010],lnk[1000010],a[1000010][30],cnt[1000010];
ll sum[1000010],k;
int edge[3000010],next[3000010],head[1000010],in[1000010];
void add(int x)
{
	int cur=++tot,p;
	cnt[cur]=1;
	len[cur]=len[last]+1;
	for(p=last;~p&&!a[p][x];p=lnk[p])
		a[p][x]=cur;
	if(~p)
	{
		int q=a[p][x];
		if(len[q]==len[p]+1)
			lnk[cur]=q;
		else
		{
			int c=++tot;
			len[c]=len[p]+1;
			lnk[c]=lnk[q];
			memcpy(a[c],a[q],sizeof(a[c]));
			for(;~p&&a[p][x]==q;p=lnk[p])
				a[p][x]=c;
			lnk[q]=lnk[cur]=c;
		}
	}
	last=cur;
}
void ins(int a,int b)
{
	edge[++tote]=b;
	next[tote]=head[a];
	head[a]=tote;
}
void dfs(int x)
{
	for(int i=head[x];i;i=next[i])
	{
		dfs(edge[i]);
		cnt[x]+=cnt[edge[i]];
	}
}
void init()
{
	tote=0;
	memset(head,0,sizeof(head));
	for(rg i=0;i<=tot;i++)
		for(rg j=1;j<=26;j++)
			if(a[i][j])
			{
				ins(a[i][j],i);
				in[i]++;
			}
	for(rg i=1;i<=tot;i++)
		sum[i]=cnt[i];
	queue<int> q;
	for(rg i=0;i<=tot;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(rg i=head[x];i;i=next[i])
		{
			sum[edge[i]]+=sum[x];
			in[edge[i]]--;
			if(!in[edge[i]])
				q.push(edge[i]);
		}
	}
}
void solve()
{
	int p=0;
	if(k>sum[0])
	{
		printf("-1");
		return;
	}
	while(1)
	{
		if(k<=0)
			return;
		for(rg i=1;i<=26;i++)
			if(a[p][i])
			{
				if(k>sum[a[p][i]])
					k-=sum[a[p][i]];
				else
				{
					p=a[p][i];
					k-=cnt[p];
					printf("%c",i+'a'-1);
					if(k<=0)
						return;
					break;
				}
			}
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
	#endif
	scanf("%s",s);
	n=strlen(s);
	lnk[0]=-1;
	for(rg i=0;i<=n-1;i++)
		add(s[i]-'a'+1);
	scanf("%d%lld",&t,&k);
	if(t)
	{
		for(rg i=1;i<=tot;i++)
			ins(lnk[i],i);
		dfs(0);
	}
	else
		for(rg i=1;i<=tot;i++)
			cnt[i]=1;
	init();
	solve();
	return 0;
}
```