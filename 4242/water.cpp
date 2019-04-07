#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define inf 4000001
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000010];
int n,m,p,qt,tot,tote;
int mat[2010][2010];
int f[200010],d[200010];
int edge[400010],nxt[400010],len[400010],head[200010];
int used[200010];
int minn[200010],minx[200010];
int fx[200010][20],fm[200010][20];
int dr[5][2]={{},{1,0},{-1,0},{0,1},{0,-1}};
struct node
{
	int x,y,id,sp;
	node(){}
	node(int a,int b,int c,int d)
	{
		x=a;
		y=b;
		id=c;
		sp=d;
	}
}vist[2010][2010];
queue<node> q;
struct edg
{
	int a,b,ln;
	edg(){}
	edg(int x,int y,int z)
	{
		a=x;
		b=y;
		ln=z;
	}
	bool operator < (const edg &o) const
	{
		return ln<o.ln;
	}
}e[16000010];
void read(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch&15),ch=gc();
}
void readc(char &ch)
{
	ch=0;
	while(ch!='.'&&ch!='#')
		ch=gc();
}
void ins(int a,int b,int c)
{
	edge[++tot]=b;
	len[tot]=c;
	nxt[tot]=head[a];
	head[a]=tot;
}
int find(int x)
{
	if(x==f[x])
		return x;
	return f[x]=find(f[x]);
}
void bfs()
{
	node t;
	for(int i=1;i<=n;i++)
		minn[i]=inf;
	int xx,yy,fa,fb;
	while(!q.empty())
	{
		t=q.front();
		q.pop();
		for(rg i=1;i<=4;i++)
		{
			xx=t.x+dr[i][0];
			yy=t.y+dr[i][1];
			if(xx<1||xx>n||yy<1||yy>m||mat[xx][yy])
				continue;
			if(vist[xx][yy].id)
			{
				if(vist[xx][yy].id!=t.id)
					e[++tote]=edg(t.id,vist[xx][yy].id,t.sp+vist[xx][yy].sp);
			}
			else
			{
				vist[xx][yy]=node(xx,yy,t.id,t.sp+1);
				q.push(vist[xx][yy]);
			}
		}
	}
}
void init()
{
	rg fa,fb;
	sort(e+1,e+tote+1);
	for(rg i=1;i<=tote;i++)
	{
		fa=find(e[i].a);
		fb=find(e[i].b);
		if(fa^fb)
		{
			f[fa]=fb;
			ins(e[i].a,e[i].b,e[i].ln);
			ins(e[i].b,e[i].a,e[i].ln);
		}
	}
}
void dfs(int x,int fa,int le)
{
	used[x]=1;
	d[x]=d[fa]+1;
	fx[x][0]=fa;
	fm[x][0]=le;
	used[x]=1;
	for(rg i=1;i<=18;i++)
	{
		fx[x][i]=fx[fx[x][i-1]][i-1];
		fm[x][i]=max(fm[x][i-1],fm[fx[x][i-1]][i-1]);
	}
	for(int i=head[x];i;i=nxt[i])
		if(edge[i]^fa)
			dfs(edge[i],x,len[i]);
}
int lca(rg a,rg b)
{
	if(d[a]<d[b])
		swap(a,b);
	rg len=d[a]-d[b],ans=0;
	for(rg i=0;i<=18;i++)
		if(len&(1<<i))
		{
			ans=max(ans,fm[a][i]);
			a=fx[a][i];
		}
	if(a==b)
		return ans;
	for(rg i=18;i>=0;i--)
		if(fx[a][i]^fx[b][i])
		{
			ans=max(ans,fm[a][i]);
			ans=max(ans,fm[b][i]);
			a=fx[a][i];
			b=fx[b][i];
		}
	ans=max(ans,fm[a][0]);
	ans=max(ans,fm[b][0]);
	return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
	#endif
	read(n);
	read(m);
	read(p);
	read(qt);
	rc ch;
	for(rg i=1;i<=n;i++)
		for(rg j=1;j<=m;j++)
		{
			readc(ch);
			if(ch=='#')
				mat[i][j]=1;
			vist[i][j].sp=inf;
		}
	rg a,b;
	for(rg i=1;i<=p;i++)
	{
		f[i]=i;
		read(a);
		read(b);
		vist[a][b]=node(a,b,i,0);
		q.push(vist[a][b]);
	}
	bfs();
	init();
	for(rg i=1;i<=p;i++)
		if(!used[i])
			dfs(i,0,0);
	// for(int i=1;i<=p;i++)
	// 	for(int j=0;j<=1;j++)
	// 		printf("i:%d j:%d fx:%d fm:%d\n",i,j,fx[i][j],fm[i][j]);
	for(rg i=1;i<=qt;i++)
	{
		read(a);
		read(b);
		if(find(a)^find(b))
			printf("-1\n");
		else
			printf("%d\n",lca(a,b));
	}
	return 0;
}