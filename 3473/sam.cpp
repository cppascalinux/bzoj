//2020.08.04
//bzoj3473 字符串 就先对所有串建出来广义后缀自动机,然后记录每个状态出现的字符串编号,map启发式合并/用线段树合并来维护就行..
//或者可以得到dfs序,然后就是求区间不同颜色种数..用树状数组维护lst数组就行,这样就能求出每个点被多少子串包含
//然后就是怎么统计答案...最开始是想直接对每个点暴力累加..以为是O(n)的..但其实是O(n*sqrt(n))的(对于100000的数据我只能卡到3000000次操作..求继续卡)
//正确方法应该是用每个串在广义sam上走,当当前状态的出现次数小于k时就不断跳fail,直到出现次数>=k..不难证明这样做一定是对的
//总时间复杂度O(nlogn)或O(nlog^2n)..但懒得写了..这份代码就是O(n*sqrt(n)*log(n))的..但跑的挺快
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#define LL long long
#define PII pair<int,int>
#define FI first
#define SE second
using namespace std;
int n,k,tot=1;
char s[100009];
int nxt[200009][27];
int len[200009],lnk[200009];
int sz[200009],sn[200009];
LL ans[100009];
vector<int> e[200009],bl[200009];
map<int,int> sp[30];
void ins(int num)
{
	int cur=1,l=strlen(s+1);
	for(int i=1;i<=l;i++)
	{
		int c=s[i]-'a'+1;
		if(!nxt[cur][c])
			nxt[cur][c]=++tot;
		cur=nxt[cur][c];
		bl[cur].push_back(num);
		sz[cur]++;
	}
}
void add(int lst,int c)
{
	int cur=nxt[lst][c],p=lnk[lst];
	len[cur]=len[lst]+1;
	for(;p&&!nxt[p][c];p=lnk[p])
		nxt[p][c]=cur;
	if(!p)
		return lnk[cur]=1,void();
	int q=nxt[p][c];
	if(len[q]==len[p]+1)
		return lnk[cur]=q,void();
	int cln=++tot;
	len[cln]=len[p]+1,lnk[cln]=lnk[q];
	for(int i=1;i<=26;i++)
		if(len[nxt[q][i]])
			nxt[cln][i]=nxt[q][i];
	for(;p&&nxt[p][c]==q;p=lnk[p])
		nxt[p][c]=cln;
	lnk[cur]=lnk[q]=cln;
}
void build()
{
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=1;i<=26;i++)
			if(nxt[x][i])
				add(x,i),q.push(nxt[x][i]);
	}
}
void dfs1(int x)
{
	int mx=-1;
	for(int t:e[x])
	{
		dfs1(t);
		if(sz[t]>mx)
			sn[x]=t,mx=sz[t];
		sz[x]+=sz[t];
	}
}
void dfs2(int x,int id)
{
	if(sn[x])
		dfs2(sn[x],id);
	for(int t:e[x])
		if(t!=sn[x])
		{
			dfs2(t,id+1);
			for(auto v:sp[id+1])
				sp[id][v.FI]+=v.SE;
			sp[id+1].clear();
		}
	for(auto v:bl[x])
		sp[id][v]++;
	if(x!=1&&(int)sp[id].size()>=k)
		for(auto t:sp[id])
			ans[t.FI]+=(LL)(len[x]-len[lnk[x]])*t.SE;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%s",s+1),ins(i);
	build();
	for(int i=2;i<=tot;i++)
		e[lnk[i]].push_back(i);
	dfs1(1);
	dfs2(1,1);
	for(int i=1;i<=n;i++)
		printf("%lld ",ans[i]);
	return 0;
}