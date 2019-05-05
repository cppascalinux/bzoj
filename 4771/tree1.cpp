//2019.05.05
//bzoj4771 七彩树 dfs序+树链的并+主席树+set
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define pii pair<int,int>
#define fi first
#define se second
#define si set<pii>::iterator
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,tot,tme,cnt;
int col[100009];
int hd[100009],eg[100009],nxt[100009];
int dep[100009],dfn[100009],ed[100009],f[100009][19];
vector<int> v[100009];
set<pii> s[100009];
int rt[100009],lp[8000009],rp[8000009],sm[8000009];
void clrv(vector<int> &p)
{
	vector<int> tmp;
	tmp.swap(p);
}
void clr()
{
	memset(hd+1,0,n<<2);
	for(int i=1;i<=n;i++)
		clrv(v[i]),s[i].clear();
	memset(lp+1,0,cnt<<2);
	memset(rp+1,0,cnt<<2);
	memset(sm+1,0,cnt<<2);
	cnt=tot=tme=0;
}
void rd(int &x)
{
	char c=0;
	x=0;
	while(c<'0'||c>'9')
		c=gc();
	while(c>='0'&&c<='9')
		x=x*10+(c&15),c=gc();
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs1(int x,int fa)
{
	v[dep[x]=dep[fa]+1].push_back(x);
	ed[x]=dfn[x]=++tme;
	f[x][0]=fa;
	for(int i=1;i<=18;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs1(eg[i],x);
		ed[x]=max(ed[x],ed[eg[i]]);
	}
}
void add(int lst,int &a,int l,int r,int pos,int val)
{
	if(a<=lst)
	{
		int p=++cnt;
		sm[p]=sm[a];
		lp[p]=lp[a];
		rp[p]=rp[a];
		a=p;
	}
	sm[a]+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		add(lst,lp[a],l,mid,pos,val);
	else
		add(lst,rp[a],mid+1,r,pos,val);
}
int ask(int a,int l,int r,int ql,int qr)
{
	if(l>qr||r<ql)
		return 0;
	if(l>=ql&&r<=qr)
		return sm[a];
	int mid=(l+r)>>1;
	return ask(lp[a],l,mid,ql,qr)+ask(rp[a],mid+1,r,ql,qr);
}
int getlca(int a,int b)
{
	if(dep[a]<dep[b])
		swap(a,b);
	int l=dep[a]-dep[b];
	for(int i=0;i<=18;i++)
		if(l&(1<<i))
			a=f[a][i];
	if(a==b)
		return a;
	for(int i=18;i>=0;i--)
		if(f[a][i]!=f[b][i])
			a=f[a][i],b=f[b][i];
	return f[a][0];
}
void init()
{
	for(int i=1;i<=n;i++)
	{
		int lst=cnt;
		rt[i]=rt[i-1];
		// printf("i:%d cnt:%d\n",i,cnt);
		// printf("i:%d size:%d\n",i,v[i].size());
		for(int j=0;j<(int)v[i].size();j++)
		{
			si it1,it2;
			int e1=0,e2=0;
			int x=v[i][j];
			it1=it2=s[col[x]].insert(pii(dfn[x],x)).fi;
			if(it1!=s[col[x]].begin())
			{
				it1--;
				e1=1;
			}
			it2++;
			if(it2!=s[col[x]].end())
				e2=1;
			if(e1&&e2)
			{
				int lca=getlca(it1->se,it2->se);
				add(lst,rt[i],1,n,dfn[lca],1);
			}
			if(e1)
			{
				int lca=getlca(it1->se,x);
				add(lst,rt[i],1,n,dfn[lca],-1);
			}
			if(e2)
			{
				int lca=getlca(it2->se,x);
				add(lst,rt[i],1,n,dfn[lca],-1);
			}
			add(lst,rt[i],1,n,dfn[x],1);
		}
	}
}
int solve(int x,int d)
{
	int nd=dep[x]+d;
	return ask(rt[nd],1,n,dfn[x],ed[x]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree1.out","w",stdout);
#endif
	int t;
	rd(t);
	while(t--)
	{
		rd(n),rd(m);
		for(int i=1;i<=n;i++)
			rd(col[i]);
		for(int i=2,a;i<=n;i++)
		{
			rd(a);
			ins(a,i);
		}
		dfs1(1,0);
		init();
		int ans=0;
		for(int i=1,a,b;i<=m;i++)
		{
			rd(a),rd(b);
			printf("%d\n",ans=solve(ans^a,ans^b));
		}
		clr();
	}
	return 0;
}