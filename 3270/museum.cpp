//2019.05.19
//bzoj3270 博物馆 fij表示到结束前,经过(i,j)的期望次数,然后高斯消元
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define db double
using namespace std;
int n,m,sx,sy;
int deg[29];
db p[29];
int e[29][29],id[29][29];
db mat[409][409];
void gauss()
{
	int len=n*n;
	// for(int i=1;i<=len;i++)
	// {
	// 	for(int k=1;k<=len+1;k++)
	// 		printf("%.2lf ",mat[i][k]);
	// 	printf("\n");
	// }
	for(int i=1;i<=len;i++)
	{
		int t=i;
		for(int j=i+1;j<=len;j++)
			if(fabs(mat[j][i])>fabs(mat[t][i]))
				t=j;
		for(int k=i;k<=len+1;k++)
			swap(mat[i][k],mat[t][k]);
		for(int k=len+1;k>=i;k--)
			mat[i][k]/=mat[i][i];
		for(int j=i+1;j<=len;j++)
			for(int k=len+1;k>=i;k--)
				mat[j][k]-=mat[j][i]*mat[i][k];
	}
	for(int i=len;i>=1;i--)
		for(int j=i+1;j<=len;j++)
			mat[i][len+1]-=mat[i][j]*mat[j][len+1];
}
void init(int a,int b)
{
	int cur=id[a][b];
	// printf("a:%d b:%d cur:%d\n",a,b,cur);
	mat[cur][cur]=-1;
	if(a!=b)
		mat[cur][cur]+=p[a]*p[b];
	for(int i=1;i<=n;i++)
		if(i!=a&&i!=b)
		{
			if(e[b][i])
			{
				int nxt=id[a][i];
				mat[cur][nxt]=p[a]*(1-p[i])/deg[i];
			}
			if(e[a][i])
			{
				int nxt=id[i][b];
				mat[cur][nxt]=p[b]*(1-p[i])/deg[i];
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j&&e[a][i]&&e[b][j])
			{
				int nxt=id[i][j];
				mat[cur][nxt]=(1-p[i])/deg[i]*(1-p[j])/deg[j];
			}
	if(a==sx&&b==sy)
		mat[cur][n*n+1]=-1;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("museum.in","r",stdin);
	freopen("museum.out","w",stdout);
#endif
	scanf("%d%d%d%d",&n,&m,&sx,&sy);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			id[i][j]=(i-1)*n+j;
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		deg[a]++,deg[b]++;
		e[a][b]=e[b][a]=1;
	}
	for(int i=1;i<=n;i++)
		scanf("%lf",p+i);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			init(i,j);
	gauss();
	for(int i=1;i<=n;i++)
		printf("%.6lf ",mat[id[i][i]][n*n+1]);
	return 0;
}