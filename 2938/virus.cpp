#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,tot;
char s[30010];
int a[30010][3];
int last[30010],f[30010];
int q[30010],l,r=-1;
int vist[30010],ins[30010];
void add()
{
	int len=strlen(s),now=0;
	for(int i=len;i>=1;--i)
		s[i]=s[i-1]-'0'+1;
	for(int i=1;i<=len;++i)
	{
		if(!a[now][s[i]])
			a[now][s[i]]=++tot;
		now=a[now][s[i]];
	}
	last[now]=1;
}
void get()
{
	int x;
	q[++r]=0;
	while(l<=r)
	{
		x=q[l++];
		for(int i=1;i<=2;++i)
			if(a[x][i])
			{
				q[++r]=a[x][i];
				if(x)
					f[a[x][i]]=a[f[x]][i];
				last[a[x][i]]|=last[f[a[x][i]]];
			}
			else
				a[x][i]=a[f[x]][i];
	}
}
int dfs(int x)
{
	int ans=0;
	if(ins[x])
		return 1;
	if(vist[x]||last[x])
		return 0;
	ins[x]=vist[x]=1;
	for(int i=1;i<=2;++i)
		ans|=dfs(a[x][i]);
	ins[x]=0;
	return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("virus.in","r",stdin);
	freopen("virus.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%s",s);
		add();
	}
	get();
	if(dfs(0))
		printf("TAK");
	else
		printf("NIE");
	return 0;
}
	