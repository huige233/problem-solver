#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int maxn=100010;
int n,m,k,p;
int dis[maxn],f[maxn][60];
int T;
bool pd[maxn][60];//判断'0'环的情况 

struct edge{
	int to;
	int len;
};

vector<edge> head1[maxn];
vector<edge> head2[maxn];
//这里用两个vector来存图，初始化的时候非常方便

int dp(int root,int l){ //root表示到哪个点了，l表当前的k还有多少剩余
	int ans=0;
	if(l<0||l>k) return 0;
	if(pd[root][l]){
		//当其已经为1时代表它已经跑过了，就可以跳出来了
		pd[root][l]=false;
		return -1;
	}
	if(f[root][l]!=-1) return f[root][l];//f有值了代表求出答案了
	pd[root][l]=true;
	for(int i=0;i<head2[root].size();i++){
		edge e=head2[root][i];
		int val=dp(e.to,dis[root]+l-dis[e.to]-e.len);
		//这个表达式，表示用尝试当前这条边替换其中最短路径里的一条边来求一个合法的解
		if(val==-1){
			pd[root][l]=false;
			return -1;
		}
		ans=(val+ans)%p;
	}
	pd[root][l]=false;
	if(root==1&&l==0) ans++;//跑到这里是证明这是一个解ans就+1
	f[root][l]=ans;
	return ans;
}

int spfa(){
	cin>>n>>m>>k>>p;
	for(int i=1;i<=n;i++){
		head1[i].clear();
		head2[i].clear();
	}
	int a,b,c;
	for(int i=1;i<=m;i++){
		cin>>a>>b>>c;
		edge e;
		e.to=b;
		e.len=c;
		head1[a].push_back(e);
		e.to=a;//反图 
		head2[b].push_back(e);
	}
	memset(dis,0x3f,sizeof(dis));
	memset(f,-1,sizeof(f));//注意这里是-1 
	queue<int>q;
	q.push(1);
	dis[1]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=0;i<head1[x].size();i++){
			if(dis[head1[x][i].to]>dis[x]+head1[x][i].len){
				dis[head1[x][i].to]=dis[x]+head1[x][i].len;
				q.push(head1[x][i].to);
			}
		}
	}
	int ans=0;
	for(int i=0;i<=k;i++){
		int val=dp(n,i);
		if(val==-1) return -1;
		ans=(ans+val)%p;
	}
	return ans;
}

int main(){
	cin>>T;
	while(T--) cout<<spfa()<<'\n';
	return 0;
}