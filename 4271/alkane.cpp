#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define rg register int
#define ll long long
#define base 1000000
#define width 6
using namespace std;
int n;
struct big
{
	vector<int> v;
	big()
	{
		v.clear();
	}
	big(const int &x)
	{
		v.clear();
		int t=x;
		while(t)
		{
			v.push_back(t%base);
			t/=base;
		}
	}
	void clean()
	{
		while(!v.back()&&v.size())
			v.pop_back();
	}
	void output()
	{
		if(!v.size())
		{
			printf("0");
			return;
		}
		clean();
		printf("%d",v[v.size()-1]);
		for(rg i=v.size()-2;i>=0;i--)
		{
			rg t=v[i],sum=0;
			while(t)
			{
				t/=10;
				sum++;
			}
			for(rg j=1;j<=width-sum;j++)
				printf("0");
			printf("%d",v[i]);
		}
	}
	bool operator <= (const big &p) const
	{
		if(v.size()!=p.v.size())
			return v.size()<p.v.size();
		for(rg i=0;i<v.size();i++)
			if(v[i]!=p.v[i])
				return v[i]<p.v[i];
		return 1;
	}
	big operator + (const big &p) const
	{
		big t;
		rg l=0,x=0;
		for(rg i=0;i<max(v.size(),p.v.size())||l;i++)
		{
			x=l;
			i<v.size()?x+=v[i]:0;
			i<p.v.size()?x+=p.v[i]:0;
			t.v.push_back(x%base);
			l=x/base;
		}
		return t;
	}
	big operator + (const int &p) const
	{
		return *this+big(p);
	}
	void operator += (const big &p)
	{
		*this=*this+p;
	}
	void operator += (const int &p)
	{
		*this=*this+p;
	}
	big operator - (const big &p) const
	{
		big t;
		if(!(p<=*this))
			return t;
		rg l=0,x=0;
		for(rg i=0;i<max(v.size(),p.v.size())||l;i++)
		{
			x=l;
			i<v.size()?x+=v[i]:0;
			i<p.v.size()?x-=p.v[i]:0;
			if(x<0)
			{
				l=-1;
				x+=base;
			}
			else
				l=0;
			t.v.push_back(x);
		}
		t.clean();
		return t;
	}
	big operator - (const int &p) const
	{
		return *this-big(p);
	}
	big operator * (const big &p) const
	{
		vector<ll> t(v.size()+p.v.size(),0);
		for(rg i=0;i<v.size();i++)
			for(rg j=0;j<p.v.size();j++)
				t[i+j]+=(ll)v[i]*p.v[j];
		ll x=0,g=0;
		big c;
		for(rg i=0;i<t.size()||g;i++)
		{
			x=g;
			i<t.size()?x+=t[i]:0;
			c.v.push_back(x%base);
			g=x/base;
		}
		c.clean();
		return c;
	}
	big operator * (const int &p) const
	{
		return *this*big(p);
	}
	void operator *= (const big &p)
	{
		*this=*this*p;
	}
	big operator / (const int &p) const
	{
		big t;
		t.v.resize(v.size(),0);
		ll x=0,l=0;
		for(rg i=v.size()-1;i>=0;i--)
		{
			t.v[i]=(v[i]+l*base)/p;
			l=(v[i]+l*base)%p;
		} 
		t.clean();
		return t;
	}
	void operator /= (const int &p)
	{
		*this=*this/p;
	}
};
big f[10011][11];
big c(big a,int b)
{
	if(b==0)
		return big(1);
	big ans=1;
	for(big i=a-b+1;i<=a;i+=1)
		ans*=i;
	for(rg i=1;i<=b;i++)
		ans/=i;
	return ans;
}
void dp()
{
	f[1][0]=big(1);
	for(rg mx=1;mx<=(n-1)>>1;mx++)
	{
		cerr<<mx<<endl;
		big tmp=0;
		for(rg j=0;j<=3;j++)
			tmp+=f[mx][j];
		for(rg i=n;i>=1;i--)
		{
			int t=(i-1)/mx;
			for(rg j=1;j<=4;j++)
				for(rg k=1;k<=min(j,t);k++)
					f[i][j]+=f[i-k*mx][j-k]*c(tmp+k-1,k);
		}
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("alkane.in","r",stdin);
	freopen("alkane.out","w",stdout);
	#endif
	scanf("%d",&n);
	dp();
	big ans;
	for(rg i=0;i<=4;i++)
		ans+=f[n][i];
	if(!(n&1))
	{
		big tmp;
		for(rg i=0;i<=3;i++)
			tmp+=f[n>>1][i];
		ans+=c(tmp+1,2);
	}
	ans.output();
	// big a,b;
	// a=big(100000000);
	// b=big(1);
	// a/=5;
	// a.output();
	return 0;
}