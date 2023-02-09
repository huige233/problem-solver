#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#define MAXN 500005
using namespace std;
inline int read()
{
	int ans=0;
	char c=getchar();
	while (!isdigit(c)) c=getchar();
	while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
	return ans;
}
typedef long long ll;
const int MOD=998244353;
inline int add(const int& x,const int& y){return x+y>=MOD? x+y-MOD:x+y;}
int n;
int ch[MAXN<<5][2],sum[MAXN<<5],mul[MAXN<<5],cnt;
inline void update(int x){sum[x]=add(sum[ch[x][0]],sum[ch[x][1]]);}
inline void pushlzy(int x,ll v){sum[x]=sum[x]*v%MOD,mul[x]=mul[x]*v%MOD;}
inline void pushdown(int x)
{
	if (mul[x]!=1)
	{
		if (ch[x][0]) pushlzy(ch[x][0],mul[x]);
		if (ch[x][1]) pushlzy(ch[x][1],mul[x]);
		mul[x]=1;
	}
}
void modify(int& x,int l,int r,int k)
{
	if (!x) mul[x=++cnt]=1;
	if (l==r) return (void)(++sum[x]);
	int mid=(l+r)>>1;
	if (k<=mid) modify(ch[x][0],l,mid,k);
	else modify(ch[x][1],mid+1,r,k);
	update(x);
}
int query(int x,int l,int r,int ql,int qr)
{
	if (!x) return 0;
	if (ql<=l&&r<=qr) return sum[x];
	if (qr<l||r<ql) return 0;
	pushdown(x);
	int mid=(l+r)>>1;
	return add(query(ch[x][0],l,mid,ql,qr),query(ch[x][1],mid+1,r,ql,qr));
}
int merge(int x,int y,int l,int r,int& xsum,int& ysum)
{
	if (!x&&!y) return 0;
	if (!x) return ysum=add(ysum,sum[y]),pushlzy(y,xsum),y;
	if (!y) return xsum=add(xsum,sum[x]),pushlzy(x,ysum),x;
	if (l==r)
	{
		ysum=add(ysum,sum[y]);
		int t=sum[x];
		sum[x]=((ll)sum[x]*ysum+(ll)xsum*sum[y])%MOD;
		xsum=add(xsum,t);
		return x;	
	} 
	pushdown(x),pushdown(y);
	int mid=(l+r)>>1;
	ch[x][0]=merge(ch[x][0],ch[y][0],l,mid,xsum,ysum);
	ch[x][1]=merge(ch[x][1],ch[y][1],mid+1,r,xsum,ysum);
	update(x);
	return x;
}
vector<int> e[MAXN],lis[MAXN];
int dep[MAXN],rt[MAXN];
void dfs(int u)
{
	int mx=0;
	for (int i=0;i<(int)lis[u].size();i++) 
		mx=max(mx,dep[lis[u][i]]);
	modify(rt[u],0,n,mx);
	for (int i=0;i<(int)e[u].size();i++)
		if (!dep[e[u][i]])
		{
			dep[e[u][i]]=dep[u]+1;
			dfs(e[u][i]);
			int xsum=0,ysum=query(rt[e[u][i]],0,n,0,dep[u]);
			rt[u]=merge(rt[u],rt[e[u][i]],0,n,xsum,ysum);
		}
}
int main()
{
	n=read();
	for (int i=1;i<n;i++)
	{
		int u,v;
		u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
	}
	int m=read();
	while (m--)
	{
		int u,v;
		u=read(),v=read();
		lis[v].push_back(u);
	}
	dfs(dep[1]=1);
	printf("%d\n",query(rt[1],0,n,0,0));
	return 0;
}