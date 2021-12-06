#include<bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define cl(x,y) memset(x,y,sizeof(x))
#define ct cerr<<"Time elapsed:"<<1.0*clock()/CLOCKS_PER_SEC<<"s.\n";
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
#define INF 1e18
const int N=2e6+10;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
const double eps=1e-8;
const double pi=acos(-1);
using namespace std;
int a[N],sum[N];
struct edge
{
	int v,id;
};
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n,i,ans=0,j=0;
	cin>>n;
	sum[0]=0;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		a[n+i]=a[i];
		sum[i]=sum[i-1]+a[i];
	}
	for(i=n+1;i<2*n;i++)
		sum[i]=sum[i-1]+a[i];
	deque<edge> q;
	for(i=1;i<2*n;i++)
	{
		while(!q.empty() && sum[i]<=q.back().v)
			q.pop_back();
		while(!q.empty() && i-n>q.front().id)
			q.pop_front();
		q.push_back({sum[i],i});
		if(i>=n)
		{
			if(q.front().v-sum[j]>=0)
				ans++;
			j++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
