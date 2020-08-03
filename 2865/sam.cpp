//2020.08.03
//bzoj2865 字符串识别 先建出来后缀自动机,然后就变成区间取min以及区间取等差数列min...然后分别排序再用并查集维护就行..卡nmd空间..
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x7F7F7F7F
using namespace std;
int n,tot=1,lst=1,tp1,tp2,cnt;
char s[500009];
int nxt[1000009][26];//0:buc 1:sa 2:f 3:ans
int len[1000009],lnk[1000009],pos[1000009];
char sz[1000009];
struct node
{
	int val,l,r;
}q1[500009],q2[500009];
bool cmp1(node a,node b)
{
	return a.val<b.val;
}
bool cmp2(node a,node b)
{
	return a.val+a.l<b.val+b.l;
}
void add(int ps,int c)
{
	int cur=++tot,p=lst;
	len[cur]=len[lst]+1,sz[cur]=1,pos[cur]=ps;
	lst=cur;
	for(;p&&!nxt[p][c];p=lnk[p])
		nxt[p][c]=cur;
	if(!p)
		return lnk[cur]=1,void();
	int q=nxt[p][c];
	if(len[q]==len[p]+1)
		return lnk[cur]=q,void();
	int cln=++tot;
	len[cln]=len[p]+1,lnk[cln]=lnk[q],pos[cln]=pos[q];
	memcpy(nxt[cln],nxt[q],26<<2);
	for(;p&&nxt[p][c]==q;p=lnk[p])
		nxt[p][c]=cln;
	lnk[q]=lnk[cur]=cln;
}
void recal()
{
	for(int i=1;i<=n;i++)
		nxt[i][0]=0;
	for(int i=1;i<=tot;i++)
		nxt[len[i]][0]++;
	for(int i=1;i<=n;i++)
		nxt[i][0]+=nxt[i-1][0];
	for(int i=tot;i>=1;i--)
		nxt[nxt[len[i]][0]--][1]=i;
	for(int i=tot;i>=1;i--)
	{
		sz[lnk[nxt[i][1]]]+=sz[nxt[i][1]];
		if(sz[lnk[nxt[i][1]]]>2)
			sz[lnk[nxt[i][1]]]=2;
	}
}
int fnd(int x)
{
	return x==nxt[x][2]?x:nxt[x][2]=fnd(nxt[x][2]);
}
void dbg()
{
	for(int i=1;i<=tp1;i++)
		printf("l:%d r:%d val:%d\n",q1[i].l,q1[i].r,q1[i].val);
}
void solve1()
{
	for(int i=1;i<=n;i++)
		nxt[i][3]=INF;
	for(int i=1;i<=n+1;i++)
		nxt[i][2]=i;
	sort(q1+1,q1+tp1+1,cmp1);
	for(int i=1;i<=tp1;i++)
	{
		int qv=q1[i].val,ql=q1[i].l,qr=q1[i].r;
		if(ql>qr)
			continue;
		int ptr=fnd(ql);
		while(ptr<=qr)
		{
			nxt[ptr][3]=qv;
			nxt[fnd(ptr)][2]=fnd(qr+1);
			ptr=fnd(ptr+1);
		}
	}
}
void solve2()
{
	for(int i=1;i<=n+1;i++)
		nxt[i][2]=i;
	sort(q2+1,q2+tp2+1,cmp2);
	for(int i=1;i<=tp2;i++)
	{
		int qv=q2[i].val,ql=q2[i].l,qr=q2[i].r;
		if(ql>qr)
			continue;
		int ptr=fnd(ql);
		while(ptr<=qr)
		{
			nxt[ptr][3]=min(nxt[ptr][3],qv-(ptr-ql));
			nxt[fnd(ptr)][2]=fnd(qr+1);
			ptr=fnd(ptr+1);
		}
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		add(i,s[i]-'a');
	recal();
	for(int i=1;i<=tot;i++)
		if(sz[i]==1)
		{
			int p=pos[i];
			int mnl=len[lnk[i]]+1,mxl=len[i];
			// printf("p:%d mnl:%d mxl:%d\n",p,mnl,mxl);
			q1[++tp1]=(node){mnl,p-mnl+1,p};
			q2[++tp2]=(node){mxl,p-mxl+1,p-mnl};
		}
	solve1();
	solve2();
	// dbg();
	for(int i=1;i<=n;i++)
		printf("%d\n",nxt[i][3]);
	return 0;
}