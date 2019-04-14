//2019.04.14
//bzoj4310: 跳蚤 后缀自动机+后缀数组lcp+二分答案+贪心
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
#define mod1 1000000007
#define mod2 1000000009
#define bse 619
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,lst=1,cnt=1,tpout;
char s[100009];
int o[200009][27],len[200009],lnk[200009];
ll sz[200009];
int seq[200009],deg[200009];
char out[100009];
pii mul[100009];
pii hsout[100009],hss[100009];
void add(int c)
{
	int cur=++cnt,p;
	len[cur]=len[lst]+1;
	for(p=lst;p&&!o[p][c];p=lnk[p])
		o[p][c]=cur;
	if(!p)
		lnk[cur]=1;
	else
	{
		int q=o[p][c];
		if(len[q]==len[p]+1)
			lnk[cur]=q;
		else
		{
			int cln=++cnt;
			len[cln]=len[p]+1;
			lnk[cln]=lnk[q];
			memcpy(o[cln],o[q],27<<2);
			for(;p&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[q]=lnk[cur]=cln;
		}
	}
	lst=cur;
}
void getsz()
{
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<=26;j++)
			if(o[i][j])
				deg[o[i][j]]++;
	queue<int> q;
	q.push(1);
	int tp=0;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		seq[++tp]=x;
		for(int i=1;i<=26;i++)
			if(o[x][i])
				if(!--deg[o[x][i]])
					q.push(o[x][i]);
	}
	for(int i=tp;i>=1;i--)
	{
		int p=seq[i];
		sz[p]=1;
		for(int j=1;j<=26;j++)
			if(o[p][j])
				sz[p]+=sz[o[p][j]];
	}
}
void inithss()
{
	mul[0]=pii(1,1);
	for(int i=1;i<=n;i++)
	{
		mul[i].fi=(ll)mul[i-1].fi*bse%mod1;
		mul[i].se=(ll)mul[i-1].se*bse%mod2;
	}
	for(int i=1;i<=n;i++)
	{
		hss[i].fi=((ll)hss[i-1].fi*bse+s[i])%mod1;
		hss[i].se=((ll)hss[i-1].se*bse+s[i])%mod2;
	}
}
void inithsout()
{
	for(int i=1;i<=tpout;i++)
	{
		hsout[i].fi=((ll)hsout[i-1].fi*bse+out[i])%mod1;
		hsout[i].se=((ll)hsout[i-1].se*bse+out[i])%mod2;
	}
}
pii geths(pii *hs,int l,int r)//get the hash value from l to r
{
	pii ans(0,0);
	ans.fi=(hs[r].fi-(ll)hs[l-1].fi*mul[r-l+1].fi%mod1+mod1)%mod1;
	ans.se=(hs[r].se-(ll)hs[l-1].se*mul[r-l+1].se%mod2+mod2)%mod2;
	return ans;
}
void kth(ll k)
{
	int p=1;
	tpout=0;
	while(k)
	{
		if(k==1&&p!=1)
			break;
		if(p!=1)
			k--;
		for(int i=1;i<=26;i++)
			if(k<=sz[o[p][i]])
			{
				out[++tpout]=i;
				p=o[p][i];
				break;
			}
			else
				k-=sz[o[p][i]];
	}
	out[tpout+1]=0;
}
int cmp(int ls,int rs)//if sl~sr>out
{
	int l=0,r=min(rs-ls+1,tpout);
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(geths(hss,ls,ls+mid-1)==geths(hsout,1,mid))
			l=mid;
		else
			r=mid-1;
	}
	char snxt=l+ls==rs+1?0:s[ls+l];
	return snxt>out[l+1];
}
int judge(ll k)
{
	kth(k);
	inithsout();
	int lst=n+1,sm=1;
	for(int i=n;i>=1;i--)
		if(cmp(i,lst-1))
		{
			lst=i+1;
			if(++sm>m)
				return 0;
			if(s[i]>out[1])	
				return 0;
		}
	if(sm<=m)
		return 1;
	return 0;
}
void bin()
{
	ll l=1,r=sz[1]-1;
	while(l<r)
	{
		ll mid=(l+r)>>1;
		if(judge(mid))
			r=mid;
		else
			l=mid+1;
	}
	kth(l);
}
void dbg()
{
	for(int i=1;i<=sz[1]-1;i++)
	{
		kth(i);
		printf("i:%d ",i);
		for(int j=1;j<=tpout;j++)
			printf("%c",(char)(out[j]+'a'-1));
		printf("\n");
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%d%s",&m,s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	for(int i=1;i<=n;i++)
		add(s[i]);
	inithss();
	getsz();
	bin();
	// dbg();
	for(int i=1;i<=tpout;i++)
		printf("%c",(char)(out[i]+'a'-1));
	return 0;
}