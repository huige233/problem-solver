#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
int n,a[N],b[N];
ll sa[N],sb[N];
struct nd{
	ll num;int id1,id2;
	nd(ll x=0,int y=0,int z=0){num=x;id1=y;id2=z;}
}f[N];
bool operator<(const nd x,const nd y){return x.num<y.num;}
int main()
{
	bool ft=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sa[i]=sa[i-1]+a[i];
	for(int i=1;i<=n;i++)scanf("%d",&b[i]),sb[i]=sb[i-1]+b[i];
	if(sa[n]<sb[n])swap(sa,sb),swap(a,b),ft=1;
	int p=0;
	for(int i=0;i<=n;i++)
	{
		while(p<n&&sb[p+1]<=sa[i])p++;
		f[i]=nd(sa[i]-sb[p],i,p);
	}
	sort(f,f+n+1);
	for(int i=0;i<n;i++)
	{
		if(f[i].num==f[i+1].num)
		{
			if(f[i].id1>f[i+1].id1)swap(f[i],f[i+1]);
			if(ft)swap(f[i].id1,f[i].id2),swap(f[i+1].id1,f[i+1].id2);
			printf(  "%d\n",f[i+1].id1-f[i].id1);
			for(int j=f[i].id1+1;j<=f[i+1].id1;j++)
			printf("%d ",j);
			printf("\n%d\n",f[i+1].id2-f[i].id2);
			for(int j=f[i].id2+1;j<=f[i+1].id2;j++)
			printf("%d ",j);
			return 0;
		}
	}
}