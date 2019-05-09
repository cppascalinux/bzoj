#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;
int main()
{
	freopen("tree.in","w",stdout);
	random_device rsed;
	mt19937 rnd(rsed());
	int t=1;
	printf("%d\n",t);
	int n=100000,m=100000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d ",rnd()%n+1);
	printf("\n");
	for(int i=2;i<=n;i++)
		printf("%d ",rnd()%(i-1)+1);
	printf("\n");
	for(int i=1;i<=m;i++)
		printf("%d %d\n",rnd()%n+1,rnd()%n+1);
	return 0;
}