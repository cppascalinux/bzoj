//2019.05.05
//bzoj4771 七彩树 可持久化线段树合并(第一棵:颜色->最小深度 第二棵:深度->颜色数量和)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define inf 0x7F7F7F7F
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,tot,cnt1,cnt2;
int col[100009];
int hd[100009],eg[100009],nxt[100009],dep[100009];
int rt1[100009],lp1[4000009],rp1[4000009],mn[4000009];
int rt2[100009],lp2[6000009],rp2[6000009],sm[6000009];
void clr()
{
	memset(hd+1,0,n<<2);
	memset(rt1+1,0,n<<2);
	memset(lp1+1,0,cnt1<<2);
	memset(rp1+1,0,cnt1<<2);
	memset(mn+1,0,cnt1<<2);
	memset(rt2+1,0,n<<2);
	memset(lp2+1,0,cnt2<<2);
	memset(rp2+1,0,cnt2<<2);
	memset(sm+1,0,cnt2<<2);
	tot=cnt1=cnt2=0;
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
void add2(int &a,int l,int r,int pos,int val)
{
	if(!a)
		a=++cnt2;
	sm[a]+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		add2(lp2[a],l,mid,pos,val);
	else
		add2(rp2[a],mid+1,r,pos,val);
}
void add1(int id,int &a,int l,int r,int pos,int val)
{
	if(!a)
		a=++cnt1,mn[a]=inf;
	if(l==r)
	{
		if(val<mn[a])
		{
			if(mn[a]<inf)
				add2(rt2[id],1,n,mn[a],-1);
			add2(rt2[id],1,n,mn[a]=val,1);
		}
		return;
	}
	mn[a]=min(mn[a],val);
	int mid=(l+r)>>1;
	if(pos<=mid)
		add1(id,lp1[a],l,mid,pos,val);
	else
		add1(id,rp1[a],mid+1,r,pos,val);
}
int merge2(int a,int b,int l,int r)
{
	if(!a||!b)
		return a|b;
	int p=++cnt2;
	sm[p]=sm[a]+sm[b];
	if(l==r)
		return p;
	int mid=(l+r)>>1;
	lp2[p]=merge2(lp2[a],lp2[b],l,mid);
	rp2[p]=merge2(rp2[a],rp2[b],mid+1,r);
	return p;
}
int merge1(int id,int a,int b,int l,int r)
{
	if(!a||!b)
		return a|b;
	int p=++cnt1;
	mn[p]=min(mn[a],mn[b]);
	if(l==r)
	{
		// if(id!=3)
		add2(rt2[id],1,n,mn[a]+mn[b]-mn[p],-1);
		// printf("id:%d l:%d mn[a]+mn[b]-mn[p]:%d\n",id,l,mn[a]+mn[b]-mn[p]);
		return p;
	}
	int mid=(l+r)>>1;
	lp1[p]=merge1(id,lp1[a],lp1[b],l,mid);
	rp1[p]=merge1(id,rp1[a],rp1[b],mid+1,r);
	return p;
}
int ask2(int a,int l,int r,int ql,int qr)
{
	if(l>qr||r<ql)
		return 0;
	if(l>=ql&&r<=qr)
		return sm[a];
	int mid=(l+r)>>1;
	return ask2(lp2[a],l,mid,ql,qr)+ask2(rp2[a],mid+1,r,ql,qr);
}
void dfs(int x,int fa)
{
	// printf("x:%d\n",x);
	dep[x]=dep[fa]+1;
	add1(x,rt1[x],1,n,col[x],dep[x]);
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs(eg[i],x);
		rt1[x]=merge1(x,rt1[x],rt1[eg[i]],1,n);
	}
	for(int i=hd[x];i;i=nxt[i])
		rt2[x]=merge2(rt2[x],rt2[eg[i]],1,n);
}
int solve(int a,int b)
{
	// printf("a:%d dep:%d b:%d\n",a,dep[a],b);
	return ask2(rt2[a],1,n,dep[a],min(n,dep[a]+b));
}
void dfs1(int id,int a,int l,int r)
{
	if(!a)
		return;
	if(l==r)
	{
		printf("id:%d col:%d mindep:%d\n",id,l,mn[a]),fflush(stdout);
		return;
	}
	int mid=(l+r)>>1;
	dfs1(id,lp1[a],l,mid);
	dfs1(id,rp1[a],mid+1,r);
}
void dfs2(int id,int a,int l,int r)
{
	if(!a)
		return;
	if(l==r)
	{
		printf("id:%d dep:%d sm:%d\n",id,l,sm[a]),fflush(stdout);
		return;
	}
	int mid=(l+r)>>1;
	dfs2(id,lp2[a],l,mid);
	dfs2(id,rp2[a],mid+1,r);
}
void dbg()
{
	for(int i=1;i<=n;i++)
	{
		printf("i:%d sm:%d\n",i,sm[rt2[i]]);
		dfs1(i,rt1[i],1,n);
		dfs2(i,rt2[i],1,n);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree2.out","w",stdout);
#endif
	int t;
	rd(t);
	while(t--)
	{
		rd(n),rd(m);
		for(int i=1;i<=n;i++)
			rd(col[i]);
		for(int i=2,a;i<=n;i++)
			rd(a),ins(a,i);
		dfs(1,0);
		// dbg();
		int ans=0;
		for(int i=1,a,b;i<=m;i++)
		{
			rd(a),rd(b);
			printf("%d\n",ans=solve(a^ans,b^ans));
		}
		clr();
	}
	return 0;
}