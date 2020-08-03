#include<iostream>
#include<random>
#include<cstdio>
using namespace std;
int main()
{
	freopen("sam.in","w",stdout);
	random_device rnd;
	int n=500000;
	for(int i=1;i<=n;i++)
		printf("%c",rnd()%26+'a');
	return 0;
}