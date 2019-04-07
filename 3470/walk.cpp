#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define rg register int
#define db long double
using namespace std;
int n,m,tot;
int sum[10009];
int hd[10009],eg[100009],nxt[100009],len[100009];
int in[10009],s[10009],top;
db f[10009],g[10009];
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void topo()
{
	queue<int> q;
	for(rg i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	rg x;
	while(!q.empty())
	{
		x=q.front();
		q.pop();
		s[++top]=x;
	//	printf("\nx:%d\n",x);
		for(rg i=hd[x];i;i=nxt[i])
		{
		//	printf("x:%d eg:%d\n",x,eg[i]);
			in[eg[i]]--;
			if(!in[eg[i]])
				q.push(eg[i]);
		}
	}
}
void dp()
{
//	for(rg i=1;i<=top;i++)
//		printf("%d ",s[i]);
	for(rg i=n;i>=1;i--)
		for(rg j=hd[s[i]];j;j=nxt[j])
			f[s[i]]+=(db)len[j]/sum[s[i]]*(f[eg[j]]+1);
	g[1]=1.0;
	for(rg i=1;i<=n;i++)
		for(rg j=hd[s[i]];j;j=nxt[j])
			g[eg[j]]+=(db)len[j]/sum[s[i]]*g[s[i]];
}
db solve()
{
	db ans=f[1];
	for(rg i=1;i<=n;i++)
	{
		int t=0;
		db nf=0.0;
		for(rg j=hd[i];j;j=nxt[j])
			t++;
		for(rg j=hd[i];j;j=nxt[j])
		{
			if(t==1)
				nf=0.0;
			else
			{
				nf=(f[i]*sum[i]-(db)len[j]*(f[eg[j]]+1))/(sum[i]-len[j]);
				ans=max(ans,f[1]+g[i]*(nf-f[i]));
			}
		}
	}
	return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("walk.in","r",stdin);
	freopen("walk.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	int a,b,c;
	for(rg i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		a++;
		b++;
	//	printf("a:%d b:%d c:%d\n",a,b,c);
		ins(a,b,c);
		in[b]++;
		sum[a]+=c;
	}
	topo();
	dp();
	printf("%.6Lf",solve());
	return 0;
}