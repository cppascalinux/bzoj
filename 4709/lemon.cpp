//2019.07.07
//bzoj4709  [Jsoi2011]柠檬 不难发现,划分的每一个区间的首尾颜色一定相同,否则将区间向内缩小,答案一定不会变劣,于是就可以对于每种颜色分别dp,不难发现转移具有决策单调性
//同时也可以写成斜率优化的形式,这里使用的是决策单调性优化,对于每种颜色维护一个栈,保存最优决策点,然后二分每一个决策点超过上一个的时间即可时间复杂度O(nlogn)
//斜率优化貌似可以做到O(n),因为凸包上的斜率单调减,而询问的斜率单调增,所以可以直接把最优决策点维护在栈顶
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cassert>
#define pii pair<int,int>
#define fi first
#define se second
#define li long long
#define pb push_back
using namespace std;
int n;
int s[100009],pos[100009];
vector<int> v[10009];
vector<pii> st[10009];
li f[100009];
li check(int cl,int x,int t)
{
	// assert(x<v[cl].size());
	return f[v[cl][x]-1]+(li)cl*(t-x+1)*(t-x+1);
}
int gett(int cl,int a,int b)//a<b,the minimum time for a to better than b
{
	int l=0,r=v[cl].size();
	// assert(a<r&&b<r);
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(cl,a,mid)>=check(cl,b,mid))
			r=mid;
		else
			l=mid+1;
	}
	return l;
}
void dp()
{
	for(int i=1;i<=n;i++)
	{
		int cl=s[i],p=pos[i];
		while(st[cl].size()>1&&st[cl].back().se<=gett(cl,st[cl].back().fi,p))
			st[cl].pop_back();
		int t=st[cl].empty()?n+1:gett(cl,st[cl].back().fi,p);
		st[cl].pb(pii(p,t));
		while(st[cl].size()>1&&st[cl].back().se<=p)
			st[cl].pop_back();
		// assert(st[cl].size());
		f[i]=check(cl,st[cl].back().fi,p);
	}
	printf("%lld",f[n]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("lemon.in","r",stdin);
	freopen("lemon.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",s+i);
		// printf("i:%d s:%d\n",i,s[i]);
		v[s[i]].pb(i),pos[i]=(int)v[s[i]].size()-1;
	}
	dp();
	return 0;
}