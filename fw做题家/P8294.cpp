#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
#define MAXN 5005
#define pb push_back
#define mkpr make_pair
#define fir first
#define sec second
const LL INF=0x3f3f3f3f3f3f3f3f;
template<typename _T>
void read(_T &x){
	_T f=1;x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while('0'<=s&&s<='9'){x=(x<<3)+(x<<1)+(s^48);s=getchar();}
	x*=f;
}
template<typename _T>
_T Fabs(_T x){return x<0?-x:x;}
int add(int x,int y,int p){return x+y<p?x+y:x+y-p;}
void Add(int &x,int y,int p){x=add(x,y,p);}
int qkpow(int a,int s,int p){int t=1;while(s){if(s&1)t=1ll*a*t%p;a=1ll*a*a%p;s>>=1;}return t;}
int n,val[MAXN],fp[MAXN],mxd[MAXN],ch[MAXN][2],deg[MAXN];
int sta[MAXN][MAXN],stak[MAXN];
LL f[MAXN],g[MAXN],h[MAXN],dp[MAXN][MAXN],tmp[MAXN][MAXN];
LL F[MAXN],Gf[MAXN],Gg[MAXN],ans;
void sakura(int rt){
	sta[rt][++stak[rt]]=rt;int ls=ch[rt][0],rs=ch[rt][1];
	if(!deg[rt]){dp[rt][0]=mxd[rt]=0;return ;}
	if(ls)sakura(ls),h[rt]=max(h[rt],h[ls]+1);
	if(rs)sakura(rs),h[rt]=max(h[rt],h[rs]+1);
	for(int j=0;j<=n;j++)dp[rt][j]=INF;
	if(deg[rt]==1){
		for(int i=1;i<=stak[ls];i++){
			int x=sta[ls][i];mxd[rt]=max(mxd[rt],mxd[x]+1);
			for(int j=0;j<=mxd[x];j++)
				tmp[x][j]=dp[x][j],dp[x][j]=INF;
			for(int j=0;j<=mxd[x];j++)
				dp[rt][j+1]=min(dp[rt][j+1],tmp[x][j]+val[x]),
				dp[x][0]=min(dp[x][0],tmp[x][j]+1ll*(j+1)*val[rt]+val[x]);
			sta[rt][++stak[rt]]=x;mxd[x]=0;
		}
		return ;
	}
	for(int i=0;i<=h[ls];i++)f[i]=Gf[i]=INF;
	for(int i=0;i<=h[rs];i++)g[i]=Gg[i]=INF;
	for(int i=1;i<=stak[ls];i++){
		int x=sta[ls][i];sta[rt][++stak[rt]]=x;
		for(int j=0;j<=mxd[x];j++)
			f[j]=min(f[j],val[x]+(tmp[x][j]=dp[x][j])),dp[x][j]=INF;
	}
	for(int i=1;i<=stak[rs];i++){
		int x=sta[rs][i];sta[rt][++stak[rt]]=x;
		for(int j=0;j<=mxd[x];j++)
			g[j]=min(g[j],val[x]+(tmp[x][j]=dp[x][j])),dp[x][j]=INF;
	}
	for(int i=1;i<=stak[ls];i++){
		int x=sta[ls][i];LL minn=F[x]=INF,mn=INF;
		for(int j=0;j<=h[rs];j++)
			minn=min(minn,g[j]+1ll*val[x]*(j+2));
		for(int j=0;j<=mxd[x];j++)
			dp[rt][j+1]=min(dp[rt][j+1],minn+tmp[x][j]),
			mn=min(mn,tmp[x][j]+1ll*(j+1)*val[rt]);
		minn=INF;
		for(int j=0;j<=mxd[x];j++)
			minn=min(minn,tmp[x][j]+1ll*val[rt]*(j+1));
		for(int j=0;j<=h[rs];j++)
			dp[x][j+1]=min(dp[x][j+1],minn+g[j]+val[x]),
			Gg[j]=min(Gg[j],1ll*(j+2)*val[x]+mn);
	}
	for(int i=1;i<=stak[rs];i++){
		int x=sta[rs][i];LL minn=INF,mn=INF;
		for(int j=0;j<=h[ls];j++)
			minn=min(minn,f[j]+1ll*val[x]*(j+2));
		for(int j=0;j<=mxd[x];j++)
			dp[rt][j+1]=min(dp[rt][j+1],minn+tmp[x][j]),
			mn=min(mn,tmp[x][j]+1ll*(j+1)*val[rt]);
		minn=INF;
		for(int j=0;j<=mxd[x];j++)
			minn=min(minn,tmp[x][j]+1ll*val[rt]*(j+1));
		for(int j=0;j<=h[ls];j++)
			dp[x][j+1]=min(dp[x][j+1],minn+f[j]+val[x]),
			Gf[j]=min(Gf[j],1ll*(j+2)*val[x]+mn);
	}
	for(int i=1;i<=stak[ls];i++){
		int x=sta[ls][i];LL minn=INF;
		for(int j=0;j<=mxd[x];j++)minn=min(minn,tmp[x][j]+Gf[j]),tmp[x][j]=INF;
		dp[x][0]=min(dp[x][0],minn+val[x]);mxd[x]=h[rs]+1;
	}
	for(int i=1;i<=stak[rs];i++){
		int x=sta[rs][i];LL minn=INF;
		for(int j=0;j<=mxd[x];j++)minn=min(minn,tmp[x][j]+Gg[j]),tmp[x][j]=INF;
		dp[x][0]=min(dp[x][0],minn+val[x]);mxd[x]=h[ls]+1;
	}
	mxd[rt]=h[rt];
}
int main(){
	read(n);ans=INF;
	for(int i=1;i<=n;i++)read(val[i]);
	for(int i=2,x;i<=n;i++)
		read(x),ch[x][deg[x]++]=i;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=n;j++)
			tmp[i][j]=dp[i][j]=INF;
	sakura(1);
	for(int i=1;i<=n;i++)ans=min(ans,dp[i][0]);
	printf("%lld\n",ans);
	return 0;
}