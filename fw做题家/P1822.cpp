#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull; 
const int N=1e3+5,M=2e4+5,inf=0x3f3f3f3f,mod=1e9+7;
const int hashmod[4] = {402653189,805306457,1610612741,998244353};
#define mst(a,b) memset(a,b,sizeof a)
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define x first
#define y second
#define pb emplace_back
#define SZ(a) (int)a.size()
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=a;i>=b;--i)
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr) 
void Print(int *a,int n){
	for(int i=1;i<n;i++)
		printf("%d ",a[i]);
	printf("%d\n",a[n]); 
}
int ans,l,r;
queue<int>q;
void dfs(int x,ll y,int w){
	if(y>r) return;
	if(!x){
		ll h=y/pow(10,w);
		if(!h) return;
		dfs(x,y+h*pow(10,w+1),w+1);
		if(y>=l&&y<=r) ans++;
		if(pow(10,w+1)<=r) q.push(y);
		return;
	}
	ll h=y/pow(10,w),l=x%10;x/=10;
	if(h-l>=0) dfs(x,y+pow(10,w+1)*(h-l),w+1);
	if(l&&h+l<10) dfs(x,y+pow(10,w+1)*(h+l),w+1);
}
int main(){
	scanf("%d%d",&l,&r);
	q.push(7);
	if(7>=l&&7<=r) ans++;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<10;i++)	dfs(u,i,0);
	}
	printf("%d\n",ans);
	return 0;
}