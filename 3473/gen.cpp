#include<random>
#include<cstdio>
using namespace std;
int main()
{
	freopen("sam.in","w",stdout);
	random_device rnd;
	int n=316,m=316;
	printf("%d %d\n",n,1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			printf("%c",'a'+(rnd()%100==0?1:0));
		printf("\n");
	}
	return 0;
}