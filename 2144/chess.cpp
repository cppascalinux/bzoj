#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
using namespace std;
struct node
{
    int x,y,z;
    node(){}
    node(int a,int b,int c)
    {
        x=a;
        y=b;
        z=c;
    }
    bool operator != (const node &o) const
    {
        return x!=o.x||y!=o.y||z!=o.z;
    }
    bool operator == (const node &o) const
    {
        return !(*this!=o);
    }
};
node s[3],f[3];
int dep[3],tot;
int init(node p)
{
    int a=p.x,b=p.y,c=p.z;
    int sa=b-a,sb=c-b;
    int ans=0;
    while(sa!=sb)
    {
        int t;
        if(sa>sb)
        {
            t=(sa-1)/sb;
            b-=t*sb;
            c-=t*sb;
            sa-=t*sb;
        }
        else
        {
            t=(sb-1)/sa;
            a+=t*sa;
            b+=t*sa;
            sb-=t*sa;
        }
        ans+=t;
    }
    return ans;
}
node kth(node p,int k)
{
    int a=p.x,b=p.y,c=p.z;
    int sa=b-a,sb=c-b;
    while(sa!=sb&&k)
    {
        int t;
        if(sa>sb)
        {
            t=(sa-1)/sb;
            if(t>k)
                t=k;
            b-=t*sb;
            c-=t*sb;
            sa-=t*sb;
        }
        else
        {
            t=(sb-1)/sa;
            if(t>k)
                t=k;
            a+=t*sa;
            b+=t*sa;
            sb-=t*sa;
        }
        k-=t;
    }
    return node(a,b,c);
}
void solve()
{
    if(kth(s[1],dep[1])!=kth(s[2],dep[2]))
    {
        printf("NO");
        return;
    }
    printf("YES\n");
    node a=s[1],b=s[2];
    int da=dep[1],db=dep[2];
    if(da<db)
    {
        swap(a,b);
        swap(da,db);
    }
    int l=da-db;
    a=kth(a,l);
    if(a==b)
    {
        printf("%d",l);
        return;
    }
    for(rg i=30;i>=0;i--)
    {
        node na=kth(a,1<<i);
        node nb=kth(b,1<<i);
        if(na!=nb)
        {
            a=na;
            b=nb;
        }
    }
    a=kth(a,1);
    printf("%d",dep[1]+dep[2]-2*init(a));
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("chess.in","r",stdin);
    freopen("chess.out","w",stdout);
    #endif
    int ta[4],tb[4];
    scanf("%d%d%d%d%d%d",ta+1,ta+2,ta+3,tb+1,tb+2,tb+3);
    sort(ta+1,ta+4);
    sort(tb+1,tb+4);
    s[1].x=ta[1];
    s[1].y=ta[2];
    s[1].z=ta[3];
    s[2].x=tb[1];
    s[2].y=tb[2];
    s[2].z=tb[3];
    dep[1]=init(s[1]);
    dep[2]=init(s[2]);
    //printf("1:%d 2:%d\n",dep[1],dep[2]);
    solve();
    return 0;
}