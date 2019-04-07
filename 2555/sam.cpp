#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int q,tot,n,last;
char s[3000010];
int a[1200010][2],link[1200010],len[1200010],cnt[1200010];
void add(int x)
{
	int cur=++tot,p;
	len[cur]=len[last]+1;
	cnt[cur]=1;
	for(p=last;~p&&!a[p][x];p=link[p])
		a[p][x]=cur;
	if(~p)
	{
		int q=a[p][x];
		if(len[q]==len[p]+1)
			link[cur]=q;
		else
		{
			int c=++tot;
			len[c]=len[p]+1;
			link[c]=link[q];
			memcpy(a[c],a[q],sizeof(a[c]));
			for(;~p&&a[p][x]==q;p=link[p])
				a[p][x]=c;
			link[q]=link[cur]=c;
		}
	}
	last=cur;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
	#endif
	scanf("%d%s",&q,s);
	int n=strlen(s);
	for(int i=0;i<=n-1;i++)
		add(s[i]-'A'+1);
	return 0;
}