#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &FF,T &X){
	FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())/*cout<<CH<<" ",*/X=CH=='m'?1:X,X=CH=='h'?0:X;//,cout<<X<<endl;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	// cout<<X<<" "<<FF<<endl;
}
template<typename T>inline void read1(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
const int MAXN=3e6+10;
int n,m,a,b,a1,b1,dfn[MAXN],low[MAXN],tot,s[MAXN],sp,sccnum[MAXN],scccnt,T;
vector<int>E[MAXN];
void tarjan(int u){
	s[sp++]=u;
	dfn[u]=low[u]=++tot;
	for(auto v:E[u])
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(!sccnum[v]){
			low[u]=min(low[u],dfn[v]);
		}
	if(dfn[u]==low[u]){
		scccnt++;
		do{
			sccnum[s[--sp]]=scccnt;
		}while(s[sp]!=u);
	}
}
void solve(){
	sp=0;tot=0;
	read1(n);read1(m);
	// memset(sccnum,0,sizeof())
	for(int i=1;i<=(n<<1);i++){
		E[i].clear();
		dfn[i]=0;
		sccnum[i]=0;
		low[i]=0;
	}
	for(int i=1;i<=m;i++){
		read(a,a1);read(b,b1);
        E[a+(a1^1)*n].push_back(b+b1*n);
    	E[b+(b1^1)*n].push_back(a+a1*n);
	}
	for(int i=1;i<=(n<<1);i++)
		if(!dfn[i])tarjan(i);
	for(int i=1;i<=(n<<1);i++)
		if(sccnum[i]==sccnum[i+n])return (void)puts("BAD");
	puts("GOOD");
}
int main(){
	read1(T);
	while(T--)solve();
	return 0;
}
/*
3 1
1 1 3 0
*/